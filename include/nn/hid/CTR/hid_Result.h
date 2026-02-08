/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_HID_RESULT_H_
#define NN_HID_CTR_HID_RESULT_H_

#include <nn/Result.h>

namespace nn {
namespace hid {
namespace CTR {

/* Please see man pages for details 
    
    
*/
    inline Result MakeResultAlreadyInitialized()
    {
        return MakeUsageResult( Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_HID, Result::DESCRIPTION_ALREADY_INITIALIZED );
    }
/* Please see man pages for details 
    
    
*/
    inline Result MakeResultInvalidCombination()
    {
        return MakeUsageResult( Result::SUMMARY_INVALID_ARGUMENT, Result::MODULE_NN_HID, Result::DESCRIPTION_INVALID_COMBINATION );
    }

    inline Result MakeResultOutOfMemory()
    {
        return MakePermanentResult( Result::SUMMARY_OUT_OF_RESOURCE, Result::MODULE_NN_HID, Result::DESCRIPTION_OUT_OF_MEMORY );
    }

    /* Please see man pages for details 
        
        
    */
    inline Result MakeResultNotInitialized()
    {
        return MakeUsageResult(Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_HID, Result::DESCRIPTION_NOT_INITIALIZED);
    }

    /* Please see man pages for details 
     
     
     */
    inline Result MakeResultNoConnection()
    {
        return MakeUsageResult(Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_HID, Result::DESCRIPTION_NOT_FOUND);
    }


    // For internal use
    // Indicates that no saved value was specified as the touch panel CAL value.
    inline Result MakeResultNoData()
    {
        return MakePermanentResult( Result::SUMMARY_NOT_FOUND, Result::MODULE_NN_HID, Result::DESCRIPTION_NO_DATA );
    }

    // For internal use
    // Indicates that the value attempted to be saved as the analog stick CAL value was invalid.
    inline Result MakeResultOutOfRange()
    {
        return MakeUsageResult( Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_HID, Result::DESCRIPTION_OUT_OF_RANGE );
    }

    // For internal use
    // Indicates that a function without rights to the connection port was called.
    inline Result MakeResultNotAuthorized()
    {
        return MakeUsageResult( Result::SUMMARY_INVALID_STATE, Result::MODULE_NN_HID, Result::DESCRIPTION_NOT_AUTHORIZED );
    }

} // namespace CTR
} // namespace hid
} // namespace nn

#endif //NN_HID_CTR_HID_RESULT_H_
