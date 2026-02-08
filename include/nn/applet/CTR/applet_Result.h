/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     applet_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_APPLET_CTR_APPLET_RESULT_H_
#define NN_APPLET_CTR_APPLET_RESULT_H_

#include <nn/Result.h>

/* Please see man pages for details 
    
*/
/* Please see man pages for details 
    
    
               
*/

namespace nn {
namespace applet {
namespace CTR {

/* Please see man pages for details 
    
*/
enum ResultDescription
{
    DESCRIPTION_APPLET_NO_AREA_TO_REGISTER          = 1,     //
    DESCRIPTION_APPLET_PARAMETER_BUFFER_NOT_EMPTY   = 2,     //
    DESCRIPTION_APPLET_CALLER_NOT_FOUND             = 3,     //
    DESCRIPTION_APPLET_NOT_ALLOWED                  = 4,     //
    DESCRIPTION_APPLET_DIFFERENT_MODE               = 5,     //
    DESCRIPTION_APPLET_DIFFERENT_VERSION            = 6,     //
    DESCRIPTION_APPLET_SHUTDOWN_PROCESSING          = 7,     //
    DESCRIPTION_APPLET_TRANSITION_BUSY              = 8,     //
    DESCRIPTION_APPLET_VERSION_MUST_LAUNCH_DIRECTLY = 9      //
};
// Since 0 is reserved in SUCCESS, start from 1.

/* Please see man pages for details 
  
  
*/
/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNotFound,
       Result::LEVEL_STATUS, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_NOT_FOUND );

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultAlreadyExist,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_ALREADY_EXISTS );

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNoArea,
       Result::LEVEL_STATUS, Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_NO_AREA_TO_REGISTER );

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNotEmpty,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_PARAMETER_BUFFER_NOT_EMPTY );

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNoData,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_NO_DATA);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNoCaller,
       Result::LEVEL_PERMANENT, Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_CALLER_NOT_FOUND);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultNotAllowed,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_NOT_ALLOWED);

/* Please see man pages for details 
    
    
                
*/
 NN_DEFINE_RESULT_CONST
     ( ResultBusy,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_BUSY);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultAlreadyInit,
       Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_ALREADY_INITIALIZED);

/* Please see man pages for details 
    
    
 */
 NN_DEFINE_RESULT_CONST
     ( ResultNotInitialized,
       Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  Result::DESCRIPTION_NOT_INITIALIZED);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultDifferentMode,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_DIFFERENT_MODE);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultDifferentVersion,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_DIFFERENT_VERSION);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultTransitionBusy,
       Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_TRANSITION_BUSY);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultShutdownProcessing,
       Result::LEVEL_USAGE, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_SHUTDOWN_PROCESSING);

/* Please see man pages for details 
    
    
*/
 NN_DEFINE_RESULT_CONST
     ( ResultVersionMustLaunchDirectly,
       Result::LEVEL_STATUS, Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_APPLET,  DESCRIPTION_APPLET_VERSION_MUST_LAUNCH_DIRECTLY);
/*  

*/

} // namespace CTR
} // namespace applet
} // namespace nn


#define NN_APPLET_RESULT_NOT_FOUND                      (nn::applet::CTR::ResultNotFound())
#define NN_APPLET_RESULT_ALREADY_EXIST                  (nn::applet::CTR::ResultAlreadyExist())
#define NN_APPLET_RESULT_NO_AREA                        (nn::applet::CTR::ResultNoArea())
#define NN_APPLET_RESULT_NOT_EMPTY                      (nn::applet::CTR::ResultNotEmpty())
#define NN_APPLET_RESULT_NO_DATA                        (nn::applet::CTR::ResultNoData())
#define NN_APPLET_RESULT_NO_CALLER                      (nn::applet::CTR::ResultNoCaller())
#define NN_APPLET_RESULT_NOT_ALLOWED                    (nn::applet::CTR::ResultNotAllowed())
#define NN_APPLET_RESULT_BUSY                           (nn::applet::CTR::ResultBusy())
#define NN_APPLET_RESULT_ALREADY_INIT                   (nn::applet::CTR::ResultAlreadyInit())
#define NN_APPLET_RESULT_DIFFERENT_MODE                 (nn::applet::CTR::ResultDifferentMode())
#define NN_APPLET_RESULT_DIFFERENT_VERSION              (nn::applet::CTR::ResultDifferentVersion())
#define NN_APPLET_RESULT_TRANSITION_BUSY                (nn::applet::CTR::ResultTransitionBusy())
#define NN_APPLET_RESULT_SHUTDOWN_PROCESSING            (nn::applet::CTR::ResultShutdownProcessing())
#define NN_APPLET_RESULT_VERSION_MUST_LAUNCH_DIRECTLY   (nn::applet::CTR::ResultVersionMustLaunchDirectly())

#endif //NN_APPLET_CTR_APPLET_RESULT_H_
