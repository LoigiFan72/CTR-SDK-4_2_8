/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     osl_Mbuf.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NET_OSL_OSL_MBUF_H_
#define NN_NET_OSL_OSL_MBUF_H_

#include <nn/os.h>
#include <nn/util/util_StaticAssert.h>
#include <string.h>

#define NN_NET_MAC_ADDRESS_SIZE     6

#define NN_NET_OSL_PAGE_SIZE        NN_OS_MEMORY_PAGE_SIZE
/* Use pagesize(=4096) / n to avoid crossing page-boundary for DMA. */
#define NN_NET_OSL_MBUF_UNIT_SIZE   (NN_OS_MEMORY_PAGE_SIZE / 2)
#define NN_NET_OSL_MBUF_HEADER_SIZE 40
#define NN_NET_OSL_MBUF_DATA_SIZE   ((NN_NET_OSL_MBUF_UNIT_SIZE) - (NN_NET_OSL_MBUF_HEADER_SIZE))
#define NN_NET_OSL_MBUF_DATA_MIN_SIZE ((NN_NET_OSL_MBUF_UNIT_SIZE) - (NN_NET_OSL_MBUF_HEADER_SIZE))

#define NN_NET_OSL_M_DONTWAIT       0       
#define NN_NET_OSL_M_WAIT           1       
#define NN_NET_OSL_M_FREELIST       0x8000              /* Please see man pages for details */

#define NN_NET_OSL_M_BCAST          0x0200              /* Please see man pages for details */
#define NN_NET_OSL_M_MCAST          0x0400              /* Please see man pages for details */
#define NN_NET_OSL_M_LOOPBACK       0x0800              /* Please see man pages for details */

#define NN_NET_OSL_M_COPYALL        1000000000

#define NN_NET_OSL_MT_DATA          1                   /* Please see man pages for details */
#define NN_NET_OSL_MT_ATH_WMI       2                   /* Please see man pages for details */

#define NN_NET_OSL_CAT_DRIVER       1
#define NN_NET_OSL_CAT_ATH          NN_NET_OSL_CAT_DRIVER /* Please see man pages for details */

struct nnnetOslMbuf;
typedef struct nnnetOslMbuf nnnetOslMbuf;

/* mbuf data structure */
typedef struct nnnetOslMbuf
{
    nnnetOslMbuf*       m_next;                         /* Please see man pages for details */
    nnnetOslMbuf*       m_prev;                         /* Please see man pages for details */
    nnnetOslMbuf*       m_nextpkt;                      /* Please see man pages for details */
    s16                 m_len;                          /* Please see man pages for details */
    s16                 m_capacity;
    s16                 m_top;                          /* Please see man pages for details */
    u16                 m_flags;                        /* Please see man pages for details */
    u16                 m_protocol;                     /* Please see man pages for details */
    u16                 m_owner;                        /* Owner module. NN_NET_OSL_M_OWN_XXXX */
    u16                 m_name;                         /* Please see man pages for details */
    u16                 m_pool;
    u8                  m_dst[NN_NET_MAC_ADDRESS_SIZE]; /* Please see man pages for details */
    u8                  m_src[NN_NET_MAC_ADDRESS_SIZE]; /* Please see man pages for details */
    u8                  m_data[NN_NET_OSL_MBUF_DATA_MIN_SIZE]; /* Please see man pages for details */
} nnnetOslMbuf;

/* mbuf in free pool */
typedef struct nnnetOslMbufFree
{
    s32                 m_nextFree;                     /* Please see man pages for details */
} nnnetOslMbufFree;

/* size validation */
NN_STATIC_ASSERT(sizeof(nnnetOslMbuf) == NN_NET_OSL_MBUF_UNIT_SIZE);
NN_STATIC_ASSERT(offsetof(nnnetOslMbuf, m_data) == NN_NET_OSL_MBUF_HEADER_SIZE);


// C declarations follow

#include <nn/util/detail/util_CLibImpl.h>

NN_EXTERN_C nnnetOslMbuf*   nnnetOslMbuf_getm       (u32 name, nnnetOslMbuf *orig, s32 len, s32 how, u8 type);
NN_EXTERN_C void            nnnetOslMbuf_freem      (nnnetOslMbuf* pMbuf_);
NN_EXTERN_C s32             nnnetOslMbuf_adj        (nnnetOslMbuf* pMbuf_, s32 len);
NN_EXTERN_C s32             nnnetOslMbuf_append     (nnnetOslMbuf* pMbuf_, s32 len, const u8 *cp);
NN_EXTERN_C nnnetOslMbuf*   nnnetOslMbuf_prepend_a  (nnnetOslMbuf* pMbuf_, s32 len, int how);
NN_EXTERN_C nnnetOslMbuf*   nnnetOslMbuf_pullup     (nnnetOslMbuf* pMbuf_, s32 len);
NN_EXTERN_C nnnetOslMbuf*   nnnetOslMbuf_dup        (nnnetOslMbuf* pMbuf_, int how);
NN_EXTERN_C s32             nnnetOslMbuf_copydata   (const nnnetOslMbuf* pMbuf_, s32 offset, s32 len, u8 *buf);
NN_EXTERN_C s32             nnnetOslMbuf_copyback   (nnnetOslMbuf* pMbuf_, s32 offset, s32 len, const u8 *buf);
NN_EXTERN_C s32             nnnetOslMbuf_cat        (nnnetOslMbuf* pMbuf_, nnnetOslMbuf *n);
NN_EXTERN_C nnnetOslMbuf*   nnnetOslMbuf_split      (nnnetOslMbuf* pMbuf_, s32 len, int how);
NN_EXTERN_C s32             nnnetOslMbuf_length     (nnnetOslMbuf* pMbuf_, nnnetOslMbuf **last);
NN_EXTERN_C s32             nnnetOslMbuf_apply      (nnnetOslMbuf* pMbuf_, s32 offset, s32 len, s32 (* f)(void* arg, void* data, s32 len), void* arg);
NN_EXTERN_C void            nnnetOslMbuf_dump       (nnnetOslMbuf* pMbuf_);
NN_EXTERN_C bool            nnnetOslMbuf_align      (nnnetOslMbuf* pMbuf_, u8 align, s8 offset);

NN_EXTERN_C inline s32      nnnetOslMbuf_leadingspace(const nnnetOslMbuf* pMbuf_)
{
    return pMbuf_->m_top;
}

NN_EXTERN_C inline s32      nnnetOslMbuf_trailingspace(const nnnetOslMbuf* pMbuf_)
{
    return pMbuf_->m_capacity - (pMbuf_->m_top + pMbuf_->m_len);
}

NN_EXTERN_C inline nnnetOslMbuf* nnnetOslMbuf_prepend(nnnetOslMbuf* pMbuf_, s32 len, int how)
{
    if (pMbuf_->m_top >= len)
    {
        pMbuf_->m_top -= len;
        pMbuf_->m_len += len;
        return pMbuf_;
    }
    else
    {
        return nnnetOslMbuf_prepend_a(pMbuf_, len, how);
    }
}

NN_EXTERN_C inline void*     nnnetOslMbuf_tod        (nnnetOslMbuf* pMbuf_)
{
    //TODO: Check consistency here.
    return &(pMbuf_->m_data[pMbuf_->m_top]);
}

NN_EXTERN_C inline void      nnnetOslMbuf_setUserPointer(nnnetOslMbuf* pMbuf_, void* p)
{
    pMbuf_->m_nextpkt = (nnnetOslMbuf*)p;
}

NN_EXTERN_C inline void*     nnnetOslMbuf_getUserPointer(nnnetOslMbuf* pMbuf_)
{
    return pMbuf_->m_nextpkt;
}

NN_EXTERN_C inline bool     nnnetOslMbuf_expand(nnnetOslMbuf* pMbuf_, s32 len, int how)
{
    NN_UNUSED_VAR(how);
    if (pMbuf_->m_top + pMbuf_->m_len + len > pMbuf_->m_capacity)
    {
        NN_LOG("nnnetOslMbuf_expand: out of capacity.(len = %d)\n", len);
        return false;
    }

    pMbuf_->m_len += len;
    return true;
}

NN_EXTERN_C inline void     nnnetOslMbuf_reserve(nnnetOslMbuf* pMbuf_, s32 len)
{
    NN_TASSERT_(pMbuf_->m_len == 0 && pMbuf_->m_top + len <= pMbuf_->m_capacity);
    pMbuf_->m_top += len;
}

#ifdef __cplusplus

#include <new>

namespace nn { namespace net { namespace osl {

class MbufPool;

class Mbuf : public nnnetOslMbuf
{
public:
    typedef s32 FreeIndex;
    static const size_t HEADER_SIZE = NN_NET_OSL_MBUF_HEADER_SIZE;

    void Initialize(size_t unitSize, u16 poolId)
    {
        std::memset(static_cast<nnnetOslMbuf*>(this), 0x00, HEADER_SIZE);
        m_capacity = unitSize - HEADER_SIZE;
        m_pool = poolId;
    }

    Mbuf(FreeIndex nextFree)
    {
        Initialize(0, 0xffff);
        reinterpret_cast<nnnetOslMbufFree*>(this)->m_nextFree = nextFree;
    }

    FreeIndex* GetNextFreeIndexPtr(void)
        { return &reinterpret_cast<nnnetOslMbufFree*>(this)->m_nextFree; }

    void SetNextFreeIndex(FreeIndex freeIndex)
        { reinterpret_cast<nnnetOslMbufFree*>(this)->m_nextFree = freeIndex; }

    FreeIndex GetNextFreeIndex(void) const
        { return reinterpret_cast<const nnnetOslMbufFree*>(this)->m_nextFree; }

    operator nnnetOslMbuf*()
        { return reinterpret_cast<nnnetOslMbuf*>(this); }

    Mbuf* GetNext(void)
    { 
        return reinterpret_cast<Mbuf*>(m_next);
    }

    const Mbuf* GetNext(void) const
    { 
        return reinterpret_cast<const Mbuf*>(m_next);
    }

    Mbuf* GetPrevious(void)
    { 
        return reinterpret_cast<Mbuf*>(m_prev);
    }

    const Mbuf* GetPrevious(void) const
    { 
        return reinterpret_cast<const Mbuf*>(m_prev);
    }

    void SetNext(Mbuf* pMbuf)
    {
        m_next = reinterpret_cast<nnnetOslMbuf*>(pMbuf);
    }

    void SetPrevious(Mbuf* pMbuf)
    {
        m_prev = reinterpret_cast<nnnetOslMbuf*>(pMbuf);
    }

    bool IsLinking(void) const
        { return m_prev != NULL || m_next != NULL; }

    Mbuf* Unlink(void)
    {
        Mbuf* pNext = GetNext();
        if (pNext)
        {
            SetNext(NULL);
            pNext->SetPrevious(NULL);
            return pNext;
        }
        else
        {
            return NULL;
        }
    }

    void CopyFrom(const Mbuf* pSource);

    Mbuf* GetTail(void);
    const Mbuf* GetHead(void) const;

    size_t SetLengthTrimed(size_t len)
    {
        m_len = (len > m_capacity) ? m_capacity : len;
        return m_len;
    }

    size_t GetLength(void) const
    {
        NN_TASSERT_(m_len <= m_capacity);
        return m_len;
    }

    size_t SetLength(size_t len)
    { 
        NN_TASSERT_(len <= m_capacity);
        return m_len = len;
    }

    s16& Length(void)
        { return m_len; }

    u16 GetFlags(void) const
        { return m_flags; }

    void SetFlags(u16 flags)
        { m_flags = flags; }

    void SetName(u32 name)
        { m_name = name; }

    u32 GetName(void) const
        { return m_name; }

    void SetProtocol(u32 protocol)
        { m_protocol = protocol; }

    u32 GetProtocol(void) const
        { return m_protocol; }

    void SetTop(s32 top)
    { 
        NN_TASSERT_(top < m_capacity);
        m_top = top;
    }

    size_t GetWritableLength(void) const
    {
        NN_TASSERT_(m_top < m_capacity);
        return m_capacity - m_top;
    }

    s32 GetTop(void) const
    { 
        return m_top;
    }

    s32 GetLeadingSpace(void) const
    {
        return m_top;
    }

    s32 GetTrailingSpace(void) const
    {
        return m_capacity - (m_top + m_len);
    }

    u8* GetTopPtr(s32 offset = 0)
    { 
        NN_TASSERT_(m_top + offset < m_capacity);
        return &m_data[m_top + offset]; 
    }

    const u8* GetTopPtr(s32 offset = 0) const
    { 
        NN_TASSERT_(m_top + offset < m_capacity);
        return &m_data[m_top + offset];
    }

    bool IsDataAligned(u8 align, s8 offset = 0) const
    {
        return IsAligned(reinterpret_cast<uptr>(GetTopPtr()), align, offset);
    }

    s16 GetCapacity(void) const
    {
        return m_capacity;
    }

    s16 GetUnitSize(void) const
    {
        return m_capacity + HEADER_SIZE;
    }

    u16 GetPoolId(void) const
    {
        return m_pool;
    }

    static bool IsAligned(uptr address, u8 align, s8 offset)
    {
        NN_TASSERT_(align != 0 && (align & (align - 1)) == 0);
        return ((address + offset) & (align - 1)) == 0;
    }

    // TORIAEZU:
    s32 GetTotalLength(void) const
    {
        const nnnetOslMbuf* p = reinterpret_cast<const nnnetOslMbuf*>(this);
        return nnnetOslMbuf_length(const_cast<nnnetOslMbuf*>(p), NULL);
    }

    bool CopyChainTo(u8* pDst, s32 offset = 0, s32 len = NN_NET_OSL_M_COPYALL) const
    {
        return nnnetOslMbuf_copydata(reinterpret_cast<const nnnetOslMbuf*>(this), offset, len, pDst) == 0;
    }

   // Also emphasize speed in the C version
    bool AlignData(u8 align, s8 offset)
    {
        return nnnetOslMbuf_align(reinterpret_cast<nnnetOslMbuf*>(this), align, offset);
    }

    void Link(Mbuf* pNext)
    {
        SetNext(pNext);
        pNext->SetPrevious(this);
    }

    void Dump(void) const;
    void DumpAll(void) const;
    void DumpChain(void) const;

protected:
};

}}} // namespace nn::net::osl

#endif // __cplusplus


#endif // NN_NET_OSL_OSL_MBUF_H_
