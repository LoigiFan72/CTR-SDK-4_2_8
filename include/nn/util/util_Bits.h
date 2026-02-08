/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Bits.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus

#ifndef NN_UTIL_UTIL_BITS_H_
#define NN_UTIL_UTIL_BITS_H_

namespace nn { namespace util {

struct Bit32Set
{
    bit32 n;
    bool Get(int i) const { return n & (1 << i); }
    void Set0(int i) { n &= ~(1 << i); }
    void Set1(int i) { n |= (1 << i); }
};

class Bit32Allocator
{
private:

    Bit32Set m_N;
    
public:

    Bit32Allocator() {}

    Bit32Allocator(int size)
    {
        this->Initialize(size);
    }
    
    void Initialize(int size)
    {
        this->m_N.n = ~(~0 << size);
    }
    
    int Allocate()
    {
        int clz = __clz(m_N.n);
        if (clz < 32)
        {
            int i = 31 - clz;
            m_N.Set0(i);
            return i;
        }
        return -1;
    }
    
    void Deallocate(int i)
    {
        if (m_N.Get(i))
        {
            NN_TPANIC_("");
        }
        m_N.Set1(i);
    }
    
};

namespace detail {

    class BitsAllocatorBase
    {
    protected:
    
        BitsAllocatorBase(Bit32Allocator* bits, int size, int n)
        {
            for (int i = 0; i < n; ++i)
            {
                if (size <= 32)
                {
                    bits[i].Initialize(size);
                    return;
                }
                else
                {
                    bits[i].Initialize(32);
                    size -= 32;
                }
            }
            NN_TPANIC_("");
        }
        
        int AllocateImpl(Bit32Allocator* bits, int n)
        {
            for (int i = 0; i < n; ++i)
            {
                int j = bits[i].Allocate();
                if (j >= 0)
                {
                    return i * 32 + j;
                }
            }
            return -1;
        }
        
        void DeallocateImpl(Bit32Allocator* bits, int i)
        {
            bits[i / 32].Deallocate(i % 32);
        }
        
    };
    
    template <int N>
    class BitsAllocatorTemplate : private BitsAllocatorBase
    {
    private:
        Bit32Allocator m_Bits[N];
    public:
        BitsAllocatorTemplate(int size) : BitsAllocatorBase(m_Bits, size, N) {}
        int Allocate() { return BitsAllocatorBase::AllocateImpl(m_Bits, N); }
        void Deallocate(int i) { BitsAllocatorBase::DeallocateImpl(m_Bits, i); }
    };
    
}

template <int N>
class BitsAllocator : public detail::BitsAllocatorTemplate<(N - 1) / 32 + 1>
{
public:
    BitsAllocator() : detail::BitsAllocatorTemplate<(N - 1) / 32 + 1>(N) {}
};

}}


#endif

#endif
