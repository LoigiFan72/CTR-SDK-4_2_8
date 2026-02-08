/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl_SharedFont.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_CTR_PL_SHAREDFONT_H_
#define NN_PL_CTR_PL_SHAREDFONT_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/fnd.h>

namespace nn {
namespace pl {
namespace CTR {

/* Please see man pages for details 
    
    
 */
/* Please see man pages for details 
    
 */
enum SharedFontType
{
    SHARED_FONT_TYPE_NULL,
    SHARED_FONT_TYPE_STD,     //
    SHARED_FONT_TYPE_CN,      //
    SHARED_FONT_TYPE_KR,      //
    SHARED_FONT_TYPE_TW       //
};

/* Please see man pages for details 
    
 */
enum SharedFontLoadState
{
    SHARED_FONT_LOAD_STATE_NULL,
    SHARED_FONT_LOAD_STATE_LOADING,     //
    SHARED_FONT_LOAD_STATE_LOADED,      //
    SHARED_FONT_LOAD_STATE_FAILED,      //

    SHARED_FONT_LOAD_STATE_MAX_BIT = (1u << 31)
};

namespace detail
{
    // Shared memory size for shared fonts: 3,272 KB
    const size_t  SHAREDFONT_MEMORY_SIZE = 1024 * 4 * 818;

    struct SharedFontBufferHeader
    {
        util::SizedEnum4<SharedFontLoadState>   state;
        util::SizedEnum4<SharedFontType>        type;
        size_t                                  size;
        bit8                                    padding[116];
    };

    struct SharedFontBuffer
    {
        SharedFontBufferHeader  header;
        // 128-byte alignment necessary
        bit8    font[SHAREDFONT_MEMORY_SIZE - sizeof(SharedFontBufferHeader)];
    };
}

/* Please see man pages for details 
    
    
 */
nn::Result          InitializeSharedFont();

/* Please see man pages for details 
    
    
 */
void*               GetSharedFontAddress();

/* Please see man pages for details 
    
    
 */
size_t              GetSharedFontSize();

/* Please see man pages for details 
    
    
 */
SharedFontType      GetSharedFontType();

/* Please see man pages for details 
    
    
 */
SharedFontLoadState GetSharedFontLoadState();

/* Please see man pages for details 
    
                
                
    
    






*/
nn::Result MountSharedFont(const char* archiveName, SharedFontType sharedFontType, size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize);

/* Please see man pages for details 
    
    
    


*/
nn::Result UnmountSharedFont(const char* archiveName);

/* Please see man pages for details 
    
    

*/
inline void Initialize();

inline void Initialize() {}

/* Please see man pages for details 
    
    

*/
inline void Finalize();

inline void Finalize() {}

/*  

*/

} // end of namespace CTR
} // end of namespace pl
} // end of namespace nn


#endif  // ifndef NN_PL_CTR_PL_SHAREDFONT_H_
