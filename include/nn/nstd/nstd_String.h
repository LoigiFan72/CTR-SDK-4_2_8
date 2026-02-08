/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nstd_String.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_NSTD_STRING_H_
#define NN_NSTD_STRING_H_

#include <nn/types.h>
#include <nn/util/detail/util_CLibImpl.h>


// TODO: ARMv4/ARMv5 not included in the C version symbol name
NN_EXTERN_C void nnnstdMemCpy(void *dstp, const void *srcp, size_t size);
NN_EXTERN_C void nnnstdMemMove(void *dstp, const void *srcp, size_t size);

#if     defined(NN_PROCESSOR_ARM_V4) || defined(NN_PROCESSOR_ARM_V5)
    #define NN_NSTD_ARM_NS ARMv4
#elif   defined(NN_PROCESSOR_ARM_V6)
    #define NN_NSTD_ARM_NS ARMv6
#else
    #error processor not selected
#endif


#ifdef __cplusplus

namespace nn { namespace nstd {

    /* Please see man pages for details 
        
    */
    namespace ARMv6
    {
        /* Please see man pages for details 
            
            
                            
                            
                            
                            
                            
            
            
            
            
        */
        inline void MemCpy(void *dstp, const void *srcp, size_t size)
        {
            nnnstdMemCpy(dstp, srcp, size);
        }

        /* Please see man pages for details 
            
            
                            
                            
                            
            
            
            
            
        */
        inline void MemMove(void *dstp, const void *srcp, size_t size)
        {
            nnnstdMemMove(dstp, srcp, size);
        }
    }

    namespace ARMv4
    {
        /* Please see man pages for details 
            
            
                            
                            
                            
                            
                            
            
            
            
            
        */
        inline void MemCpy(void *dstp, const void *srcp, size_t size)
        {
            nnnstdMemCpy(dstp, srcp, size);
        }

        /* Please see man pages for details 
            
            
                            
                            
                            
            
            
            
            
        */
        inline void MemMove(void *dstp, const void *srcp, size_t size)
        {
            nnnstdMemMove(dstp, srcp, size);
        }
    }

    using namespace NN_NSTD_ARM_NS;
}}

#endif

#endif /* NN_NSTD_STRING_H_ */
