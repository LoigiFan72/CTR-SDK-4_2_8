/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_SafeHandle.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47340 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FSLOW_FSLOW_SAFEHANDLE_H_
#define NN_FSLOW_FSLOW_SAFEHANDLE_H_

#include <nn/types.h>
#include <nn/os/os_WaitableCounter.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/WithInitialize.h>
#include <nn/os/os_CriticalSection.h>

namespace nn { namespace fslow {

/*---------------------------------------------------------------------------*
 * Use as ReaderWriterLock
 * Pre-initialization   : 0
 * - After-initialization   : 1
 *    - ReaderLock   : (positive) increment, (negative) do not unlock
 *    - ReaderUnlock : Absolute value decrement
 *    - WriterLock   : (positive) reverse sign and wait until -1
 *---------------------------------------------------------------------------*/
class SafeReferenceCounter : private nn::util::NonCopyable<SafeReferenceCounter>
{
private:
    nn::os::WaitableCounter m_Counter;

    struct IncrementIfNonPositive
    {
        bool operator()(s32& x) const
        {
            if(x < 0)
            {
                return false;
            }
            else
            {
                ++x;
                return true;
            }
        }
    };

    struct AbsDecrement
    {
        bool operator()(s32& x) const
        {
            if(x >= 0)
            {
                --x;
            }
            else
            {
                ++x;
            }
            return true;
        }
    };
    
    struct Negate
    {
        bool operator()(s32& x) const
        {
            NN_TASSERT_(x > 0);
            x = -x;
            return true;
        }
    };

public:

    SafeReferenceCounter()
    {
        *m_Counter = 0;
    }

    SafeReferenceCounter(nn::WithInitialize)
    {
        *m_Counter = 1;
    }

    void Initialize()
    {
        NN_TASSERT_(!IsInitialized());
        *m_Counter = 1;
    }

    bool Increment()
    {
        // Remove ReaderLock
        NN_TASSERT_(IsInitialized());
        IncrementIfNonPositive f;
        return m_Counter->AtomicUpdateConditional(f);
    }

    void Decrement()
    {
        // Do ReaderUnlock
        NN_TASSERT_(IsInitialized());
        AbsDecrement f;
        m_Counter->AtomicUpdateConditional(f);
        if (*m_Counter == -1)
        {
            m_Counter.SignalAll();
        }
    }

    bool IsInitialized() const
    {
        return *m_Counter != 0;
    }

    bool IsValid() const
    {
        NN_TASSERT_(IsInitialized());
        return *m_Counter > 0;
    }

    bool IsLocked() const
    {
        NN_TASSERT_(IsInitialized());
        return (*m_Counter < -1) || (1 < *m_Counter);
    }

    void PrepareFinalization()
    {
        // Prepare WriterLock (Disables removal of ReaderLock)
        NN_TASSERT_(IsValid());
        Negate f;
        m_Counter->AtomicUpdateConditional(f);
    }

    bool IsFinalizationPrepared() const
    {
        NN_TASSERT_(IsInitialized());
        return *m_Counter < 0;
    }

    bool TryFinalize()
    {
        return m_Counter->CompareAndSwap(-1, 0) == 0;
    }

    void Finalize()
    {
        // Wait until WriterLock is removed, and then terminate
        if(IsInitialized())
        {
            if(IsValid())
            {
                Negate f;
                m_Counter->AtomicUpdateConditional(f);
            }
            m_Counter.WaitIfLessThan(-1);
            *m_Counter = 0;
        }
    }
};


/*---------------------------------------------------------------------------*
 *  Handle
 *---------------------------------------------------------------------------*/
class SafeHandleBase
{
protected:
    bit32   m_Data[2];

public:
    SafeHandleBase() { Invalidate(); }

    void    Invalidate() { m_Data[0] = m_Data[1] = 0; }

    bool    IsValid() const { return (m_Data[0] != 0) || (m_Data[1] != 0); }

    operator bool() const { return IsValid(); }
    bool    operator!() const { return !IsValid(); }
    bool    operator==(const SafeHandleBase& rhs) const { return (m_Data[0] == rhs.m_Data[0]) && (m_Data[1] == rhs.m_Data[1]); }
    bool    operator!=(const SafeHandleBase& rhs) const { return (m_Data[0] != rhs.m_Data[0]) || (m_Data[1] != rhs.m_Data[1]); }
};

/*---------------------------------------------------------------------------*
 *  Archive handle
 *    - Permanent handle: <w0> object address, <w1> always 0
 *    - Non-permanent handle: <w0[0:7]> fixed value, <w0[8:31] w1[0:31]> incrementable unique value
 *---------------------------------------------------------------------------*/
class SafeHandle : public SafeHandleBase
{
public:
    SafeHandle() {}
    SafeHandle(bit8 index) { Initialize(index); }
    SafeHandle(void* pObject) { Initialize(pObject); }

    // Initialization as permanent handle
    void Initialize(void* pObject)
    {
        NN_TASSERT_(!IsValid());
        m_Data[0] = reinterpret_cast<bit32>(pObject);
    }

    // Initialization as non-permanent handle
    void Initialize(bit8 fixedValue)
    {
        NN_TASSERT_(!IsValid());
        m_Data[0] = fixedValue;
        m_Data[1] = 1;      // Distinguish from permanent handle
    }

    void Finalize() { Invalidate(); }

    bool    IsPermanent() const { return m_Data[1] == 0; }

    void* GetObject() const
    {
        NN_TASSERT_(IsPermanent());
        return reinterpret_cast<void*>(m_Data[0]);
    }

    bit8 GetFixedValue() const
    {
        NN_TASSERT_(!IsPermanent());
        return static_cast<bit8>(m_Data[0] & 0xFF);
    }

    SafeHandle& operator++();
};

// invalid handle
typedef const SafeHandle  InvalidSafeHandle;


/*---------------------------------------------------------------------------*
 *  Archive entry
 *---------------------------------------------------------------------------*/
class SafeHandleTableEntry
{
public:
    static const s32    INVALID_INDEX   = -1;
    static const s32    MAX_INDEX       = 255;

    SafeHandleTableEntry() :
        m_pObject(0),
        m_DependencyIndex(0) {}
    ~SafeHandleTableEntry() {}

    void        Initialize(s32 index);
    void        Finalize();
    SafeHandle  Activate(void* pObject, s32 dependencyIndex=INVALID_INDEX);
    void        Deactivate();

    bool        Lock();
    void        Unlock();
    void        LockForUnregister();
    void*       GetObject() { NN_TASSERT_(IsLocked()); return m_pObject; }

    bool        IsInitialized() const { return m_Handle.IsValid(); }
    bool        IsActivated() const { return m_AccessLockCounter.IsInitialized(); }
    bool        HasHandle(const SafeHandle& handle) const { return IsInitialized() && (handle == m_Handle); }
    bool        IsLocked() const { return m_AccessLockCounter.IsValid(); }

    SafeHandle  GetHandle() const { return IsActivated() ? m_Handle : InvalidSafeHandle(); }
    bool        HasDependencyIndex() const { return m_DependencyIndex != m_Handle.GetFixedValue(); }
    s32         GetDependencyIndex() const { return HasDependencyIndex() ? m_DependencyIndex : INVALID_INDEX; }

private:
    SafeHandle              m_Handle;
    void*                   m_pObject;
    SafeReferenceCounter    m_AccessLockCounter;
    bit8                    m_DependencyIndex;  // Own index value == no dependency
    NN_PADDING3;
};

/*---------------------------------------------------------------------------*
 *  Archive handle table
 *---------------------------------------------------------------------------*/
class SafeHandleTable
{
public:
    SafeHandleTable() : m_NumEntry(0), m_pEntryBuffer(0) {}
    ~SafeHandleTable() {}

    void        Initialize(SafeHandleTableEntry* pEntryBuffer, s32 NumEntry);
    void        Finalize();

    bool        IsInitialized() const { return m_pEntryBuffer != 0; }

    SafeHandle  Register(void* pObject, SafeHandle dependencyHandle=InvalidSafeHandle());
    void        Unregister(SafeHandle handle);
    
    void* LockHandle(SafeHandle handle)
    {
        SafeHandleTableEntry* entry = FindEntry(handle);
        return LockEntry(entry, handle) ? entry->GetObject() : 0;
    }
    
    void UnlockHandle(SafeHandle handle) { return UnlockEntry(FindEntry(handle)); }
    
    friend class Accessor;
    class Accessor
    {
    private:
        SafeHandleTableEntry* m_pEntry;

    protected:
    
        void* GetPointer() const { return m_pEntry ? m_pEntry->GetObject() : 0; }

    public:
        Accessor(SafeHandleTable& table, SafeHandle handle)
        {
            SafeHandleTableEntry* entry = table.FindEntry(handle);
            this->m_pEntry = LockEntry(entry, handle) ? entry : 0;
        }

        ~Accessor()
        {
            if (m_pEntry)
            {
                UnlockEntry(m_pEntry);
            }
        }

        operator bool() const { return GetPointer() != 0; }
        bool operator!() const { return GetPointer() == 0; }
    };

private:

    static bool LockEntry(SafeHandleTableEntry* pEntry, SafeHandle handle);
    static void UnlockEntry(SafeHandleTableEntry* pEntry);
    SafeHandleTableEntry* FindEntry(SafeHandle handle) const;

    SafeHandleTableEntry* GetEntry(s32 index) const
    {
        return (index < m_NumEntry) ? (m_pEntryBuffer + index) : 0;
    }
    
    s32                     m_NumEntry;
    SafeHandleTableEntry*   m_pEntryBuffer;
    mutable nn::os::CriticalSection m_CriticalSection;

    SafeHandleTableEntry*   FindFreeEntry() const;
    void                    UnregisterRecursive(s32 index);
};

//--- Template
template <class TObject, s32 TNumEntry>
class SafeArchiveHandleTable
{
public:
    typedef SafeHandle              Handle;
    typedef SafeHandleTableEntry    Entry;
    typedef SafeHandleTable         Table;

    SafeArchiveHandleTable() { m_Table.Initialize(m_Entry, TNumEntry); }
    
    ~SafeArchiveHandleTable() { m_Table.Finalize(); }

    Handle Register(TObject* pObject, Handle dependencyHandle=InvalidSafeHandle())
    {
        return m_Table.Register(pObject, dependencyHandle);
    }

    void Unregister(SafeHandle handle)
    {
        m_Table.Unregister(handle);
    }

    TObject* LockHandle(SafeHandle handle)
    {
        return reinterpret_cast<TObject*>(m_Table.LockHandle(handle));
    }

    void UnlockHandle(SafeHandle handle)
    {
        m_Table.UnlockHandle(handle);
    }

    bool HasHandle(SafeHandle handle)
    {
        return (m_Table.FindEntry(handle) != 0);
    }

private:
    Entry   m_Entry[TNumEntry];   // May end up allocating separately
    Table   m_Table;

    Entry*  FindEntry(Handle handle) const { return m_Table.FindEntry(handle); }

public:

    class Accessor : public SafeHandleTable::Accessor
    {
    public:
        Accessor(SafeArchiveHandleTable& table, Handle handle) : SafeHandleTable::Accessor(table.m_Table, handle) {}

        TObject* GetPointer() { return static_cast<TObject*>(SafeHandleTable::Accessor::GetPointer()); }

        TObject* operator->() { return GetPointer(); }
        TObject& operator*() { return *GetPointer(); }
    };

};


}}

#endif
