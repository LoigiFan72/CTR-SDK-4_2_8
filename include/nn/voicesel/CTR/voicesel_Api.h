/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     voicesel_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_VOICESEL_CTR_VOICESEL_API_H_
#define NN_VOICESEL_CTR_VOICESEL_API_H_

/* Please see man pages for details 
  
  
*/

#include <nn/types.h>
#include <nn/fs.h>
#include <nn/applet.h>

#ifdef  __cplusplus

namespace nn {
namespace voicesel {
namespace CTR { 


/* Please see man pages for details 
    
*/
static const u32  VERSION  = 0;


/* Please see man pages for details 
    

            
*/
enum ReturnCode
{
    //
    RETURN_CODE_UNKNOWN                         = -1,

    //
    RETURN_CODE_INVALID_CONFIG                  = -2,

    //
    RETURN_CODE_OUT_OF_MEMORY                   = -3,

    //
    RETURN_CODE_NONE                            = 0,

    //
    RETURN_CODE_SUCCESS                         = 1,

    //
    RETURN_CODE_HOME_BUTTON                     = 10,

    //
    RETURN_CODE_SOFTWARE_RESET                  = 11,

    //
    RETURN_CODE_POWER_BUTTON                    = 12,

    //
    RETURN_CODE_MAX_BIT = static_cast<s32>(1u << 31)
};


/* Please see man pages for details 
    

            
            
            
*/
enum FilterFillType
{
    //
    FILTER_FILL_TYPE_ALL                        = 0,

    //
    FILTER_FILL_TYPE_100_LT                     = 1,

    //
    FILTER_FILL_TYPE_75_LT                      = 2,

    //
    FILTER_FILL_TYPE_50_LT                      = 3,

    //
    FILTER_FILL_TYPE_25_LT                      = 4
};


/* Please see man pages for details 
    
    
    
*/
struct Config
{
    //----------------------------------------
    //
    //

    /* Please see man pages for details 
        
    */
    bool                homeButton;

    /* Please see man pages for details 
        
    */
    bool                softwareReset;

    u8                  padding1[6];

    /* Please see man pages for details 
        
        
        
    */
    u8                  reserved[32 - 8];

    //
};


/* Please see man pages for details 
    

    
*/
struct Input
{
    //
    static const size_t MAX_TITLE_LENGTH  = 63;

    //----------------------------------------
    //
    //

    /* Please see man pages for details 
        
    */
    wchar_t             titleText[MAX_TITLE_LENGTH + 1];

    /* Please see man pages for details 
        
    */
    FilterFillType      filterFillType;

    /* Please see man pages for details 
        

        
    */
    u8                  reserved[256 - sizeof(wchar_t) * (MAX_TITLE_LENGTH + 1) - 1];

    //
};


/* Please see man pages for details 
    
    
    
*/
struct Output
{
    //
    static const size_t MAX_FILE_PATH_LENGTH  = nn::fs::MAX_FILE_PATH_LENGTH;

    //----------------------------------------
    //
    //

    /* Please see man pages for details 
        

                
                
    */
    ReturnCode          returnCode;

    /* Please see man pages for details 
        
    */
    wchar_t             filePath[MAX_FILE_PATH_LENGTH + 1];

    /* Please see man pages for details 
        

        
    */
    u8                  reserved[1024 - 4 - sizeof(wchar_t) * (MAX_FILE_PATH_LENGTH + 1)];

    //
};


/* Please see man pages for details 
    
    
    
*/
struct Parameter
{
    /* Please see man pages for details 
        
    */
    u32     version;

    /* Please see man pages for details 
        
    */
    Config  config;

    /* Please see man pages for details 
        
    */
    Input   input;

    /* Please see man pages for details 
        
    */
    Output  output;
};


/* Please see man pages for details 
    

    
    
*/
void InitializeParameter(Parameter* pParameter);

/* Please see man pages for details 
    
*/
bool PreloadVoiceSel();

/* Please see man pages for details 
    
*/
bool CancelPreloadVoiceSel();

/* Please see man pages for details 
    
*/
void WaitForPreloadVoiceSel();

/* Please see man pages for details 
    

    
                    
*/
bool IsRegisteredVoiceSel();

/* Please see man pages for details 
    

    
*/
nn::applet::AppletWakeupState StartVoiceSel(Parameter* pParameter);


} // end of namespace CTR
} // end of namespace voicesel
} // end of namespace nn

#endif /* __cplusplus */

#endif /* NN_VOICESEL_CTR_VOICESEL_API_H_ */
