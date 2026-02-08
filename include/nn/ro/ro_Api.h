/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ro_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47385 $
 *---------------------------------------------------------------------------*/

#ifndef NN_RO_RO_API_H_
#define NN_RO_RO_API_H_

#include <nn/config.h>
#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/ro/ro_Types.h>

namespace nn {
namespace ro {

    class Module;
    class RegistrationList;

    namespace detail
    {
        const char PORT_NAME_DYNAMIC_LOADER[] = "ldr:ro";
        const s32 ENTRY_NOT_FOUND = -1;

        uptr    GetOriginalAddress(const void* p);
        void    UpdateRegistrationListNode(RegistrationList* p);
        s32     FindRegistrationListEntry(const RegistrationList** pp, const void* p);
        void*   GetRoot();

        NN_WEAK_SYMBOL bool IsCodeAddress(uptr addr);
    }


    //
    //
    const size_t REQUIRED_SIZE_FOR_GET_SIZE_INFO = 0x100;



    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    Result      Initialize(void* pRs, size_t rsSize);

    //---------------------------------------------------------------------------
    //
    //
    //
    //---------------------------------------------------------------------------
    Result      Finalize();

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    RegistrationList*   RegisterList(void* pRr, size_t rrSize);

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    Result      GetSizeInfo(SizeInfo* pInfo, const void* pRo);

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    uptr    GetAddress(const char* name);

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    template<typename T>
    T       GetPointer(const char* name)
    { return reinterpret_cast<T>(GetAddress(name)); }

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    Module*     FindModule(const char* pName);

    //---------------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //---------------------------------------------------------------------------
    Module*     LoadModule(void* pRo, size_t roSize, void* pBuffer, size_t bufferSize,
                    bool doRegister = true,
                    FixLevel fixLevel = FIX_LEVEL_1,
                    const RegistrationList* pRr = NULL );


} // end of namespace ro
} // end of namespace nn





/* Please see man pages for details 
  
  

                

  
*/

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
extern "C" NN_DLL_EXPORT void nnroProlog();


//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
extern "C" NN_DLL_EXPORT void nnroEpilog();


//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
extern "C" NN_DLL_EXPORT void nnroUnresolved();

/*  

*/


#endif  // ifndef NN_RO_RO_API_H_
