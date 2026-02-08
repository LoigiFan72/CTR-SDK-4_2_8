/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cx_Util.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47707 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CX_UTIL_H_
#define NN_CX_UTIL_H_

#include <nn/types.h>

#define NN_CX_CHECK_ALIGN(exp, align)                                         \
    NN_TWARNING_((reinterpret_cast<uptr>(exp)) % (align) == 0,                \
                 "%s(=0x%08x) should be %d byte aligned.", #exp, (exp), align)

namespace nn {
namespace cx {
namespace internal {

inline u32 ConvertEndian( u32 x )
{
#if ( NN_ENDIAN == NN_ENDIAN_VALUE_BIG )
    // Reflect the endianness on a big-endian platform
    return ((x & 0xFF000000) >> 24) |
           ((x & 0x00FF0000) >>  8) |
           ((x & 0x0000FF00) <<  8) |
           ((x & 0x000000FF) << 24);
#else
    return x;
#endif
}

inline u32 ForceConvertEndian( u32 x )
{
    return ((x & 0xFF000000) >> 24) |
           ((x & 0x00FF0000) >>  8) |
           ((x & 0x0000FF00) <<  8) |
           ((x & 0x000000FF) << 24);
}

inline u16 ConvertEndian16( u16 x )
{
#if ( NN_ENDIAN == NN_ENDIAN_VALUE_BIG )
    // Reflect the endianness on a big-endian platform
    return (u16)( ((x & 0xFF00) >> 8) |
                  ((x & 0x00FF) << 8) );
#else
    return x;
#endif
}

inline u16 ForceConvertEndian16( u16 x )
{
    return (u16)( ((x & 0xFF00) >> 8) |
                  ((x & 0x00FF) << 8) );
}

// LittleEndian 32bit Read
inline u32 Read32Le(const u8* p)
{
    return (p[0] <<  0) | (p[1] <<  8) | (p[2] << 16) | (p[3] << 24);
}

}   // namespace internal

    namespace detail
    {
        class ZlibAllocator
        {
        public:
            ZlibAllocator(void* p, size_t size)
            : m_pHead(reinterpret_cast<bit8*>(p))
            , m_pEnd (reinterpret_cast<bit8*>(p) + size)
            {
            }

            static void* Allocate(void* pObj, unsigned numItems, size_t size)
            {
                return reinterpret_cast<ZlibAllocator*>(pObj)->Allocate(numItems * size);
            }

            static void Free(void* pObj, void* pMemory)
            {
                // Depending on the zlib implementation, after deallocation, does nothing, assuming there will be no allocation after freeing memory
                // 
                // 
                NN_UNUSED_VAR(pObj);
                NN_UNUSED_VAR(pMemory);
            }

        private:
            void* Allocate(size_t size)
            {
                if( m_pHead + size <= m_pEnd )
                {
                    void* pRet = m_pHead;
                    m_pHead += size;
                    return pRet;
                }
                else
                {
                    return NULL;
                }
            }

        private:
            bit8*   m_pHead;
            bit8*   m_pEnd;
        };

        s32 ConvertZlibReturnCode(int zlibReturnCode);
    }

}   // namespace cx
}   // namespace nn

/* NN_CX_UTIL_H_ */
#endif
