/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_SafeHandle.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/fslow/fslow_SafeHandle.h>


namespace nn { namespace fslow {


/*===========================================================================*
 *  SafeHandle
 *===========================================================================*/

/*---------------------------------------------------------------------------*
 *  operator++
 *    Not changed because the lower 8 bits of w0 are a fixed value
 *---------------------------------------------------------------------------*/
SafeHandle& SafeHandle::operator++()
{
    NN_TASSERT_(IsValid());
    NN_TASSERT_(!IsPermanent());

    m_Data[0] += 0x100;

    if (((m_Data[0] & 0xFFFFFF00) == 0) && (++m_Data[1] == 0))
    {
        NN_TPANIC_("No more archive handle.");
    }
    return *this;
}



/*===========================================================================*
 *  SafeHandleTableEntry
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Initialize
  Description:  Initialization
  Arguments:    index   Index of this entry
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTableEntry::Initialize(s32 index)
{
    NN_TASSERT_(!IsInitialized());
    NN_TASSERT_(index <= MAX_INDEX);

    m_DependencyIndex = static_cast<bit8>(index);
    m_Handle.Initialize(index);
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Finalize
  Description:  Clean up
  Arguments:    None.
  Returns:      None.
  Note:         Because the handle value is also reset, called when the handle table itself is deleted.
                
 *---------------------------------------------------------------------------



*/
void SafeHandleTableEntry::Finalize()
{
    NN_TASSERT_(IsInitialized());

    if(IsActivated())
    {
        Deactivate();
    }

    m_DependencyIndex = 0;
    m_Handle.Invalidate();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Activate
  Description:  Enables this entry
  Arguments:    pObject: Archive object to register
                Index of the entry dependent on dependencyIndex
  Returns:      Returns a handle
 *---------------------------------------------------------------------------


*/
SafeHandle SafeHandleTableEntry::Activate(void* pObject, s32 dependencyIndex/*=INVALID_INDEX*/)
{
    NN_TASSERT_(IsInitialized() && !IsActivated());
    NN_TASSERT_(pObject);

    m_pObject = pObject;

    if(dependencyIndex != INVALID_INDEX)
    {
        m_DependencyIndex = static_cast<bit8>(dependencyIndex);
    }

    ++m_Handle; // Updates the handle-specific value

    m_AccessLockCounter.Initialize();
    return m_Handle;
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Deactivate
  Description:  Disables this entry
  Arguments:    None.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTableEntry::Deactivate()
{
    NN_TASSERT_(IsActivated());
    NN_TASSERT_(m_AccessLockCounter.IsFinalizationPrepared());

    m_pObject           = 0;
    m_DependencyIndex   = m_Handle.GetFixedValue();

    m_AccessLockCounter.Finalize();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Lock
  Description:  Locks this entry
                - Remove ReaderLock
  Arguments:    None.
  Returns:      Returns whether lock was done
 *---------------------------------------------------------------------------


*/
bool SafeHandleTableEntry::Lock()
{
    NN_TASSERT_(IsActivated());
    return m_AccessLockCounter.Increment();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::Unlock
  Description:  Unlocks this entry
                - Releases ReaderLock
  Arguments:    None.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTableEntry::Unlock()
{
    NN_TASSERT_(IsActivated());
    m_AccessLockCounter.Decrement();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTableEntry::LockForUnregister
  Description:  Unlocks for registration deletion
                - Prepares WriterLock
  Arguments:    None.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTableEntry::LockForUnregister()
{
    NN_TASSERT_(IsActivated());
    m_AccessLockCounter.PrepareFinalization();
}



/*===========================================================================*
 *  SafeHandleTable
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::Initialize
  Description:  Initialization
  Arguments:    pEntryBiffer: Buffer for entry table
                NumEntry: Number of entries that can be stored in the buffer
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTable::Initialize(SafeHandleTableEntry* pEntryBuffer, s32 NumEntry)
{
    NN_TASSERT_(!IsInitialized());
    NN_TASSERT_(pEntryBuffer);
    NN_TASSERT_(NumEntry <= SafeHandleTableEntry::MAX_INDEX);

    for(s32 i = 0; i < NumEntry; ++i)
    {
        // CHECK: Is placement new received with void* better?
        pEntryBuffer[i].Initialize(i);
    }

    m_NumEntry      = NumEntry;
    m_pEntryBuffer  = pEntryBuffer;
    m_CriticalSection.Initialize();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::Finalize
  Description:  Clean up
  Arguments:    None.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTable::Finalize()
{
    if(!IsInitialized())
    {
        return;
    }

    for(s32 i = 0; i < m_NumEntry; ++i)
    {
        m_pEntryBuffer[i].Finalize();
    }

    m_NumEntry      = 0;
    m_pEntryBuffer  = 0;
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::Register
  Description:  Registers archive objects
  Arguments:    pObject: Archive object to register
                dependencyHandle: Handle of the dependent archive
  Returns:      Returns a handle
  Note:         Be sure to call after locking the dependent archive.
 *---------------------------------------------------------------------------



*/
SafeHandle SafeHandleTable::Register(void* pObject, SafeHandle dependencyHandle/*=InvalidSafeHandle()*/)
{
    NN_TASSERT_(IsInitialized());
    
    nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);

    s32 dependencyIndex;

    if(dependencyHandle.IsValid())
    {
        // Lock the dependent
        dependencyIndex = dependencyHandle.GetFixedValue();
        if(!GetEntry(dependencyIndex)->Lock())
        {
            return InvalidSafeHandle();
        }
    }
    else
    {
        dependencyIndex = SafeHandleTableEntry::INVALID_INDEX;
    }

    SafeHandleTableEntry*   pEntry = FindFreeEntry();
    if(pEntry)
    {
        return pEntry->Activate(pObject, dependencyIndex);
    }

    return InvalidSafeHandle();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::Unregister
  Description:  Releases the registration for a archive object
  Arguments:    handle: Handle of the archive to release registration
  Returns:      None.
  Note:         Also recursively removes archives dependent on oneself
 *---------------------------------------------------------------------------



*/
void SafeHandleTable::Unregister(SafeHandle handle)
{
    NN_TASSERT_(IsInitialized());
    
    nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);

    if(handle.IsValid())
    {
        UnregisterRecursive(handle.GetFixedValue());
    }
}

void SafeHandleTable::UnregisterRecursive(s32 index)
{
    SafeHandleTableEntry* pEntry = GetEntry(index);
    if(!pEntry || !pEntry->IsActivated())
    {
        return;
    }

    // Do not lock more than this externally
    pEntry->LockForUnregister();

    // There is an entry dependent on oneself
    SafeHandleTableEntry* pEntryDependOn;
    for(s32 i = 0; i < m_NumEntry; ++i)
    {
        pEntryDependOn = GetEntry(i);
        if(pEntryDependOn->IsActivated() && (pEntryDependOn->GetDependencyIndex() == index))
        {
            UnregisterRecursive(i);
        }
    }

    // Remove lock on dependent
    if(pEntry->HasDependencyIndex())
    {
        GetEntry(pEntry->GetDependencyIndex())->Unlock();
    }

    // Disable self
    pEntry->Deactivate();
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::LockEntry
  Description:  Lock entry
  Arguments:    handle: Archive entry
  Returns:      Returns whether lock was done.
 *---------------------------------------------------------------------------


*/
bool SafeHandleTable::LockEntry(SafeHandleTableEntry* pEntry, SafeHandle handle)
{
    if(pEntry && pEntry->IsActivated())
    {
        if (pEntry->Lock())
        {
            // Even if lock was done, it does not mean that the anticipated handle was locked.
            // Verifies that the corresponding entry was anticipated.
            if (pEntry->HasHandle(handle))
            {
                return true;
            }
            // When the corresponding entry does not have the expected handle, the entry lock is released because this function fails to lock.
            // 
            pEntry->Unlock();
        }
    }

    return false;
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::UnlockEntry
  Description:  Release the entry lock
  Arguments:    handle: Archive object entry
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void SafeHandleTable::UnlockEntry(SafeHandleTableEntry* pEntry)
{
    if(pEntry && pEntry->IsActivated())
    {
        pEntry->Unlock();
    }
    else
    {
        NN_TPANIC_("unknown handle");
    }
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::FindEntry
  Description:  Searches for entries from handles
  Arguments:    handle: Archive handle
  Returns:      Returns the entry
 *---------------------------------------------------------------------------


*/
SafeHandleTableEntry* SafeHandleTable::FindEntry(SafeHandle handle) const
{
    NN_TASSERT_(IsInitialized());
    
    nn::os::CriticalSection::ScopedLock lk(m_CriticalSection);

    if(handle.IsValid())
    {
        // Uses the index information since it is in the handle
        SafeHandleTableEntry* pEntry = GetEntry(handle.GetFixedValue());
        if(pEntry && pEntry->HasHandle(handle))
        {
            return pEntry;
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------*
  Name:         SafeHandleTable::FindFreeEntry
  Description:  Search for empty entries
  Arguments:    None.
  Returns:      Returns the entry
 *---------------------------------------------------------------------------


*/
SafeHandleTableEntry* SafeHandleTable::FindFreeEntry() const
{
    for (s32 i = 0; i < m_NumEntry; ++i)
    {
        if (!m_pEntryBuffer[i].IsActivated())
        {
            return m_pEntryBuffer + i;
        }
    }
    return 0;
}


}}

