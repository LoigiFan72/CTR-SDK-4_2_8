/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dbg_ExceptionScreen.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49370 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

    
*/

#ifndef NN_DBG_CTR_DBG_EXCEPTIONSCREEN_H_
#define NN_DBG_CTR_DBG_EXCEPTIONSCREEN_H_

#ifdef  __cplusplus

#include <nn/dbg/CTR/dbg_DirectPrint.h>
#include <nn/os/os_ExceptionHandlerSelect.h>
#include <nn/os.h>
#include <nn/math.h>
#include <nn/util/util_FlagsEnum.h>
#include <gles2/gl2.h>

namespace nn { namespace fnd {
    class IAllocator;
}}

namespace nn { namespace dbg { namespace CTR {

//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
class ExceptionScreen
{
private:
    static const size_t EXCEPTION_STACK_SIZE = 0xa00;   //

public:
    static const int MAX_BUILD_INFO_CHARS = 32;

    //----------------------------------------------------------------------
    //
    //
    //----------------------------------------------------------------------
    enum Option
    {
        //----------------------------------------------------------------------
        //
        //----------------------------------------------------------------------
        OPTION_WRITE_TO_SD,

        //----------------------------------------------------------------------
        //
        //----------------------------------------------------------------------
        OPTION_DIRECT_PRINT,

        //----------------------------------------------------------------------
        //
        //
        //----------------------------------------------------------------------
        OPTION_WAIT_KEY,

        NUM_OF_OPTION,

        //----------------------------------------------------------------------
        //
        //
        //
        //----------------------------------------------------------------------
        OPTION_DEFAULT = (OPTION_WRITE_TO_SD|OPTION_DIRECT_PRINT)
    };

public:
    ~ExceptionScreen();

public:
    //----------------------------------------------------------------------
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
    //----------------------------------------------------------------------
    static void Create( nn::fnd::IAllocator* allocator, bit32 option = OPTION_DEFAULT );

    //----------------------------------------------------------------------
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
    //----------------------------------------------------------------------
    static DirectPrint* GetDirectPrint() { return &(s_ExceptionScreen->m_DirectPrint); };

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    static void SetBuildInfo( const wchar_t* pBuildInfo ) { s_ExceptionScreen->SetBuildInfoImpl( pBuildInfo ); }

    //----------------------------------------------------------------------
    //
    //
    //
    //
    //
    //
    //
    //----------------------------------------------------------------------
    static void SetSuffix( const wchar_t* pSuffix ) { s_ExceptionScreen->SetSuffixImpl( pSuffix ); }

    //----------------------------------------------------------------------
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
    //----------------------------------------------------------------------
    static void HandleException(nn::os::ExceptionInfo* pei, nn::os::ExceptionContext* pec);

    //----------------------------------------------------------------------
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
    //----------------------------------------------------------------------
    static s32 PutBackTraceString(char* pOut, size_t size, uptr stackPtr, bit32 lr);

    static void PrepareDisplaybuffer() { s_ExceptionScreen->PrepareDisplaybufferImpl(); }

private:
    DirectPrint                 m_DirectPrint;
    GLuint                      m_Display[ 1 ];
    wchar_t                     m_BuildInfo[ MAX_BUILD_INFO_CHARS ];
    wchar_t                     m_Suffix[ 16 ];
    util::FlagsEnum4<Option>    m_Option;
    NN_PADDING4;
    os::StackBuffer<EXCEPTION_STACK_SIZE>   m_Stack;

    static ExceptionScreen* s_ExceptionScreen;

private:
    ExceptionScreen(bit32 option);
    void OnHalt( const char* msg );
    void RegisterHandler();
    void ExceptionHandlerBody(nn::os::ExceptionInfo* pei, nn::os::ExceptionContext* pec);
    void SetBuildInfoImpl( const wchar_t* pBuildInfo );
    void SetSuffixImpl( const wchar_t* pSuffix );
    void PrepareDisplaybufferImpl();

    void AssignNewDisplaybuffer();

    static void ExceptionHandler(nn::os::ExceptionInfo* pei, nn::os::ExceptionContext* pec);
};
    
    
    
}}}
#endif

#endif  // NN_DBG_CTR_DBG_EXCEPTIONSCREEN_H_
