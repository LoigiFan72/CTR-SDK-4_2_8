/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     os_ExceptionHandler.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47500 $
 *---------------------------------------------------------------------------*/

#ifndef NN_OS_ARM_OS_EXCEPTIONHANDLER_H_
#define NN_OS_ARM_OS_EXCEPTIONHANDLER_H_

#ifdef __cplusplus

#include <nn/types.h>
#include <nn/util/util_SizedEnum.h>

namespace nn {
namespace os {
namespace ARM {

    /*
      

     */
    enum ExceptionType
    {
        EXCEPTION_TYPE_PABT,        //
        EXCEPTION_TYPE_DABT,        //
        EXCEPTION_TYPE_UNDEF,       //
        EXCEPTION_TYPE_VFP,         //

        EXCEPTION_TYPE_MAX_BIT = (1u << 7)
    };


    /*
      

     */
    struct ExceptionContext
    {
        bit32   r[16];      //
        bit32   cpsr;       //
    };


    /*
      

     */
    struct ExceptionInfo
    {
        util::SizedEnum1<ExceptionType>   type;     //
        NN_PADDING3;
        bit32       fsr;            //
        bit32       far;            //
        bit32       fpexc;          //
        bit32       fpinst;         //
        bit32       fpinst2;        //
    };


    /*
      

     */
    struct ExceptionBuffer
    {
        ExceptionInfo       info;       //
        ExceptionContext    context;    //
    };


    /*
      

            

            

            
            
            

      
      

     */
    typedef void (*UserExceptionHandler)(ExceptionInfo* pei, ExceptionContext* pec);



    /*
      
                    

     */
    ExceptionBuffer* const EXCEPTION_BUFFER_USE_HANDLER_STACK = NULL;


    /*
      
                    

     */
    ExceptionBuffer* const EXCEPTION_BUFFER_USE_THREAD_STACK  = reinterpret_cast<ExceptionBuffer*>(1);


    /*
      
                    

     */
    const uptr HANDLER_STACK_USE_THREAD_STACK = 1;





    /*
      

      

      
      
                                        
      
     */
    void SetUserExceptionHandler(
        UserExceptionHandler pHandler, uptr stackBottom, ExceptionBuffer* pExceptionBuffer );


    /*
      

      

                    
                    

                    
                    
                    

      

      
      
      

     */
    template <typename T>
    void SetUserExceptionHandler(
        UserExceptionHandler pHandler, T* pStack, ExceptionBuffer* pExceptionBuffer)
    {
        SetUserExceptionHandler(pHandler, pStack->GetStackBottom(), pExceptionBuffer);
    }


    /*
      

      

                    
                    
                    
                    
                    

                    
                    
                    

                    
                    

                    
                    

      
      
                                        
      

      
     */
    void SetUserExceptionHandlerLocal(
        UserExceptionHandler pHandler, uptr stackBottom, ExceptionBuffer* pExceptionBuffer);


    /*
      

      

                    
                    

                    
                    
                    

                    
                    

      

      
      
      

      
     */
    template <typename T>
    void SetUserExceptionHandlerLocal(
        UserExceptionHandler pHandler, T* pStack, ExceptionBuffer* pExceptionBuffer)
    {
        SetUserExceptionHandlerLocal(pHandler, pStack->GetStackBottom(), pExceptionBuffer);
    }


    /*
      

      

                    
                        
                    

                    
                    
                    

      
      
                                

     */
    void SetUserExceptionHandler(UserExceptionHandler pHandler, uptr stackBottom);


    /*
      

      

                    
                        
                    

                    
                    
                    

      

      
      

     */
    template <typename T>
    void SetUserExceptionHandler(UserExceptionHandler pHandler, T* pStack)
    {
        SetUserExceptionHandler(pHandler, pStack->GetStackBottom());
    }


}   // end of namespace ARM
}   // end of namespace os
}   // end of namespace nn

#endif // __cplusplus

#endif /* NN_OS_ARM_OS_EXCEPTIONHANDLER_H_ */
