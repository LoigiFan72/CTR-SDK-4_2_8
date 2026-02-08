/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fslow_HandleTable.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FSLOW_FSLOW_HANDLETABLE_H_
#define NN_FSLOW_FSLOW_HANDLETABLE_H_

#include <nn.h>
#include <nn/util/util_Int64.h>


namespace nn { namespace fslow {

typedef nn::util::Int64<bit64>  HandleValue;

/*---------------------------------------------------------------------------*
 * File handle
 *    - <w0[0:7]>fixed value, <w0[8]> enable flag, <w0[9:31],w1[0:31]> incrementable
 *---------------------------------------------------------------------------*/
class Handle
{
protected:
    HandleValue m_Data;

    static const bit32  FIXED_VALUE_MASK    = 0x0FF;
    static const bit32  VALID_FLAG_MASK     = 0x100;
    static const bit32  INCREMENT_VALUE     = 0x200;

public:
    Handle()
    {
        m_Data.lo = 0;
        m_Data.hi = 0;
    }

    Handle(bit8 fixedValue)
    {
        m_Data.lo = fixedValue + INCREMENT_VALUE;
        m_Data.hi = 0;
    }

    Handle(const HandleValue& value)
    {
        m_Data.lo = value.lo;
        m_Data.hi = value.hi;
    }

    void Initialize(bit8 fixedValue)
    {
        NN_TASSERT_(!IsInitialized());
        m_Data.lo = fixedValue + INCREMENT_VALUE;
    }

    void Finalize()
    {
        m_Data.lo = 0;
        m_Data.hi = 0;
    }

    void Validate()
    {
        NN_TASSERT_(IsInitialized());
        m_Data.lo |= VALID_FLAG_MASK;
    }

    void Invalidate()
    {
        NN_TASSERT_(IsInitialized());
        m_Data.lo &= ~VALID_FLAG_MASK;
        Increment();
    }

    bit8    GetFixedValue() const { return static_cast<bit8>(m_Data.lo & FIXED_VALUE_MASK); }
    bool    IsInitialized() const { return (m_Data.lo != 0) || (m_Data.hi != 0); }
    bool    IsValid() const { return (m_Data.lo & VALID_FLAG_MASK) != 0; }

    operator HandleValue() const        { return m_Data; }
    operator const HandleValue&() const { return m_Data; }
    operator bool() const               { return IsValid(); }

    bool    operator!() const                        { return !IsValid(); }
    bool    operator==(const HandleValue& rhs) const { return (m_Data.lo == rhs.lo) && (m_Data.hi == rhs.hi); }
    bool    operator!=(const HandleValue& rhs) const { return (m_Data.lo != rhs.lo) || (m_Data.hi != rhs.hi); }

protected:
    void Increment()
    {
        m_Data.lo += INCREMENT_VALUE;
        if (((m_Data.lo & ~FIXED_VALUE_MASK) == 0) && (++m_Data.hi == 0))
        {
            m_Data.lo += INCREMENT_VALUE;
        }
    }
};

/*---------------------------------------------------------------------------*
 * Handle table entry
 *---------------------------------------------------------------------------*/
template<class T>
class HandleTableEntry
{
public:
    HandleTableEntry() {}
    HandleTableEntry(bit8 fixedValue) { Initialize(fixedValue); }
    ~HandleTableEntry() {}

    // Initialization
    void Initialize(bit8 fixedValue)
    {
        NN_TASSERT_(!IsInitialized());
        m_Handle.Initialize(fixedValue);
    }

    // Register an object that is tied to this entry
    const HandleValue& Register(const T& object)
    {
        NN_TASSERT_(!m_Handle.IsValid());
        m_Object = object;
        m_Handle.Validate();
        return m_Handle;
    }

    // Unregister (invalidate the handle)
    void Unregister()
    {
        NN_TASSERT_(m_Handle.IsValid());
        m_Handle.Invalidate();
    }

    const HandleValue&  GetHandle() const { return m_Handle; }
    const T&            GetObject() const { return m_Object; }
    bool                IsInitialized() const { return m_Handle.IsInitialized(); }
    bool                IsValid() const { return m_Handle.IsValid(); }
    bool                HasHandle(HandleValue value) const { return IsValid() && (m_Handle == value); }

private:
    Handle  m_Handle;
    T       m_Object;
};

/*---------------------------------------------------------------------------*
 * Handle table
 *---------------------------------------------------------------------------*/
template<class T, size_t TNumEntry>
class HandleTable
{
    typedef HandleTableEntry<T>     TEntry;

public:
    HandleTable() {}
    HandleTable(nn::WithInitialize) { Initialize(); }
    ~HandleTable() {}

    // Initialization
    //   - Pass index as unique handle value
    void Initialize()
    {
        for(s32 i = 0; i < TNumEntry; ++i)
        {
            m_Entry[i].Initialize(i);
        }
    }

    // Register object
    const HandleValue& Register(const T& object)
    {
        TEntry* pEntry = FindFreeEntry();
        NN_TASSERT_(pEntry);
        return pEntry->Register(object);
    }

    // Delete object
    void Unregister(const HandleValue& value)
    {
        TEntry* pEntry = const_cast<TEntry*>(FindEntryFromHandle(value));
        NN_TASSERT_(pEntry);
        pEntry->Unregister();
    }

    // Return the object that is tied to the specified handle
    const T& GetObject(const HandleValue& value) const
    {
        const TEntry* pEntry = FindEntryFromHandle(value);
        NN_TASSERT_(pEntry);
        return pEntry->GetObject();
    }

    bool TryGetObject(T* pObject, const HandleValue& value) const
    {
        const TEntry* pEntry = FindEntryFromHandle(value);
        if(pEntry)
        {
            *pObject = pEntry->GetObject();
            return true;
        }
        return false;
    }

private:
    TEntry  m_Entry[TNumEntry];

    // Search for unused entry
    TEntry* FindFreeEntry()
    {
        for(s32 i = 0; i < TNumEntry; ++i)
        {
            if(!m_Entry[i].IsValid())
            {
                return m_Entry + i;
            }
        }
        return 0;
    }

    // Search for entries that were registered to the specified handle
    const TEntry* FindEntryFromHandle(const HandleValue& value) const
    {
        // Index is inserted into the fixed portion, so use it
        Handle  handle(value);
        s32     index = handle.GetFixedValue();

        if(index < TNumEntry)
        {
            return m_Entry[index].HasHandle(value) ? (m_Entry + index) : 0;
        }
        return 0;
    }
};

}}

#endif // #ifndef NN_FSLOW_FSLOW_HANDLETABLE_H_
