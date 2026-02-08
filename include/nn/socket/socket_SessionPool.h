/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     socket_SessionPool.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SOCKET_SOCKET_SOCKET_SESSIONPOOL_H_
#define NN_SOCKET_SOCKET_SOCKET_SESSIONPOOL_H_

#include <nn/os/os_CriticalSection.h>
#include <nn/os/os_LightEvent.h>
#include <nn/svc.h>
#include <nn/srv.h>
#include <nn/os/os_Thread.h>
#include <nn/os/ipc/os_Session.h>
#include <nn/fnd/fnd_LinkedList.h>
#include <nn/fnd/fnd_Allocator.h>
#include <nn/socket/socket_Result.h>
#include <cstring>
#include <new>

namespace nn {
namespace socket{
namespace detail{

class SessionItem:
    public fnd::IntrusiveLinkedList<SessionItem>::Item,
    public os::ipc::Session
{
};

class SessionPool
{
public:
    typedef fnd::IntrusiveLinkedList<SessionItem> SessionList;
    class ScopedAllocator
    {
    public:
        ScopedAllocator(SessionPool& sessionPool)
            : m_sessionPool(sessionPool), m_pSessionItem(NULL)
        {
        }
        ~ScopedAllocator()
        {
            if (m_pSessionItem)
            {
                m_sessionPool.Free(m_pSessionItem);
                m_pSessionItem = NULL;
            }
        }

        Result Allocate(SessionItem*& pSessionItem)
        {
            NN_TASSERT_(m_pSessionItem == NULL);
            Result result = m_sessionPool.Allocate(pSessionItem);
            NN_UTIL_RETURN_IF_FAILED(result);
            m_pSessionItem = pSessionItem;
            return result;
        }

        Result TryAllocate(SessionItem*& pSessionItem)
        {
            NN_TASSERT_(m_pSessionItem == NULL);
            Result result = m_sessionPool.TryAllocate(pSessionItem);
            NN_UTIL_RETURN_IF_FAILED(result);
            m_pSessionItem = pSessionItem;
            return result;
        }

    private:
        SessionPool&    m_sessionPool;
        SessionItem*    m_pSessionItem;
    };

    SessionPool()
        : m_lock(nn::WithInitialize())
        , m_event(false)
        , m_numActiveSession(0)
        , m_numFreeSession(0)
        , m_numInactiveSession(0)
        , m_numMaxSession(0)
        , m_bInitialized(false)
        , m_bFinalizing(false)

    {
    }

    ~SessionPool()
    {
        Finalize();
    }

    Result TryInitialize(const char8* pName, size_t nameLen, SessionItem pSessions[], s32 count, s32 initial = 0)
    {
        os::CriticalSection::ScopedLock lock(m_lock);
        Result result;

        NN_TASSERT_(initial <= count);
        NN_TASSERT_(m_numActiveSession == 0);
        NN_TASSERT_(m_listActive.IsEmpty()
                  && m_listInactive.IsEmpty()
                  && m_listFree.IsEmpty());

        if (m_bInitialized)
        {
            return ResultAlreadyInitialized();
        }

        // Save service name
        std::strlcpy(m_name, pName, sizeof(m_name));
        m_nameLength = nameLen;

        // Store session on free list
        for (s32 i = 0; i < count; ++i)
        {
            m_listFree.PushBack(&pSessions[i]);
            ++m_numFreeSession;
        }

        // Get sessions from the free list. The number of sessions obtained is equal the number of initial sessions.
        for (s32 i = 0; i < initial; ++i)
        {
            // Get sessions
            result = AddNewSession();
            if (result.IsFailure())
            {
                m_lock.Leave();
                // An error occurs if the number of initial sessions cannot be allocated
                Finalize();
                m_lock.Enter();
                return result;
            }
        }
        m_bInitialized = true;
        m_bFinalizing = false;
        return ResultSuccess();
    }

    void SemiFinalize(void)
    {
        os::CriticalSection::ScopedLock lock(m_lock);
        m_bFinalizing = true;
        m_event.Pulse();
        while(!m_listInactive.IsEmpty())    // Can be used
        {
            m_listInactive.PopFront()->Close();
            --m_numInactiveSession;
            //NN_LOG("Finalize f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
        }
        while(!m_listFree.IsEmpty())        // Not connected
        {
            --m_numFreeSession;
            m_listFree.PopFront()->Close();
            //NN_LOG("Finalize f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
        }
    }

    void Finalize(void)
    {
        SemiFinalize();
        {
            os::CriticalSection::ScopedLock lock(m_lock);

            for(SessionItem* pSessionItem = m_listActive.GetFront();
                pSessionItem != NULL;
                pSessionItem = m_listActive.GetNext(pSessionItem))
            {

                pSessionItem->Close();
            }
            //NN_LOG_DEBUG("Finalize f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
            while(true)
            {
                NN_TASSERT_(m_numActiveSession >= 0);
                if (m_numActiveSession == 0)
                {
                    m_bInitialized = false;
                    break;
                }
                m_lock.Leave();
                nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromMilliSeconds(100));
                m_lock.Enter();
            }
        }
        SemiFinalize();
        NN_TASSERT_(m_listActive.IsEmpty()
                  && m_listInactive.IsEmpty()
                  && m_listFree.IsEmpty());
        NN_TASSERT_(m_numActiveSession == 0);
    }

    Result Allocate(SessionItem*& pSessionItem)
    {
        Result result;
        while(true)
        {
            result = TryAllocate(pSessionItem);
            if (result.IsSuccess() || result.GetDescription() != DESCRIPTION_REQUEST_SESSION_FULL)
            {
                break;
            }
            m_event.Wait();
        }
        return result;
    }

    Result TryAllocate(SessionItem*& pSessionItem)
    {
        os::CriticalSection::ScopedLock lock(m_lock);
        //NN_LOG("Allocate enter f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);

        if (!m_bInitialized || m_bFinalizing)
        {
            return ResultNotInitialized();
        }
        // If there is no usable session, add a new usable session
         // 
        if (m_listInactive.IsEmpty())
        {
            Result result = AddNewSession();
            if (result.IsFailure())
            {
                //NN_LOG("Allocate no more session\n");
                return result;
            }
        }
        NN_TASSERT_(!m_listInactive.IsEmpty());

        // Move from usable session list to session list in use
        pSessionItem = m_listInactive.PopFront();
        --m_numInactiveSession;
        m_listActive.PushBack(pSessionItem);
        ++m_numActiveSession;
        //NN_LOG("Allocate leave f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
        return ResultSuccess();
    }

    void Free(SessionItem* pSessionItem)
    {
        os::CriticalSection::ScopedLock lock(m_lock);
        NN_TASSERT_(pSessionItem);
        NN_TASSERT_(m_bInitialized);
        NN_TASSERT_(!m_listActive.IsEmpty());

        //NN_LOG("Free enter f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
        if (!m_bInitialized)
        {
            return;
        }

        // Move from the session list in use to the usable session list and then make usable again (reuse the handle without closing it)
        // 
        m_listActive.Erase(pSessionItem);
        --m_numActiveSession;

        if (pSessionItem->IsValid())
        {
            m_listInactive.PushBack(pSessionItem);
            ++m_numInactiveSession;
        }
        else
        {
            pSessionItem->Close();
            m_listFree.PushBack(pSessionItem);
            ++m_numFreeSession;
        }
        m_event.Signal();
        //NN_LOG("Free leave f=%d i=%d a=%d\n", m_numFreeSession, m_numInactiveSession, m_numActiveSession);
    }

protected:
    virtual Result InitializingSession(nn::os::ipc::Session&)
    {
        return ResultSuccess();
    }

private:
    Result AddNewSession(void)
    {
        // If the free list is empty, then the maximum number has been reached. Accordingly, a new session cannot be established
        //
        if (m_listFree.IsEmpty())
        {
            return ResultRequestSessionFull();
        }

        SessionItem* pSessionItem = m_listFree.GetFront();
        NN_TASSERT_(!pSessionItem->IsValid());
        Result result = srv::GetServiceHandle(pSessionItem, m_name, m_nameLength);
        if (result.IsFailure())
        {
            return result;
        }

        result = InitializingSession(*pSessionItem);
        if (result.IsFailure())
        {
            pSessionItem->Close();
            return result;
        }

        NN_TASSERT_(!m_listFree.IsEmpty());

        m_listFree.PopFront();
        --m_numFreeSession;
        m_listInactive.PushBack(pSessionItem);
        ++m_numInactiveSession;
        return ResultSuccess();
    }
    
    SessionList         m_listActive;
    SessionList         m_listInactive;
    SessionList         m_listFree;
    os::CriticalSection m_lock;
    os::LightEvent      m_event;

    s32                 m_numActiveSession;
    s32                 m_numFreeSession;
    s32                 m_numInactiveSession;


    s32                 m_numMaxSession;
    size_t              m_nameLength;
    char8               m_name[srv::MAX_SERVICE_NAME_LEN + 1];
    bool                m_bInitialized;
    bool                m_bFinalizing;
    u8                  padding[1];
};

template<size_t maxSessions>
class SessionPoolFixed : public SessionPool
{
public:
    Result TryInitialize(const char8* pName, size_t nameLen, s32 initial = 0)
    {
        return SessionPool::TryInitialize(pName, nameLen, m_Sessions, maxSessions, initial);
    }

private:
    SessionItem     m_Sessions[maxSessions];
};

class SessionPoolAuto : public SessionPool
{
public:
    SessionPoolAuto()
        : m_pSessionItemArray(NULL), m_pAllocator(NULL)
    {
    }

    Result TryInitialize(const char8* pName, size_t nameLen, nn::fnd::IAllocator& allocator, s32 count, s32 initial = 0)
    {
        const size_t arraySize = GetRequiredMemorySize(count);
        m_pSessionItemArray = reinterpret_cast<SessionItem*>(allocator.Allocate(arraySize, 4));
        if (!m_pSessionItemArray)
        {
            return ResultOutOfMemory();
        }

        new (m_pSessionItemArray) SessionItem[count];
        m_pAllocator = &allocator;
        
        Result result;
        result = SessionPool::TryInitialize(pName, nameLen, m_pSessionItemArray, count, initial);
        if (result.IsFailure())
        {
            allocator.Free(m_pSessionItemArray);
            m_pSessionItemArray = NULL;
        }
        return result;
    }

    void Finalize(void)
    {
        NN_TASSERT_(m_pSessionItemArray && m_pAllocator);
        SessionPool::Finalize();
        m_pAllocator->Free(m_pSessionItemArray);
        m_pSessionItemArray = NULL;
        m_pAllocator = NULL;
    }

    static size_t GetRequiredMemorySize(s32 count)
    {
        return sizeof(SessionItem) * count;
    }

protected:
    Result TryInitialize(const char8* pName, size_t nameLen, SessionItem pSessions[], s32 count, s32 initial = 0);

private:
    SessionItem*            m_pSessionItemArray;
    nn::fnd::IAllocator*    m_pAllocator;
};

#if 0
class SocketSessionPool : public SessionPool
{
protected:
    virtual Result InitializingSession(nn::os::ipc::Session& session);
};
#endif

} // end of namespace detail
} // end of namespace socket
} // end of namespace nn

#endif // NN_SOCKET_SOCKET_SOCKET_SESSIONPOOL_H_
