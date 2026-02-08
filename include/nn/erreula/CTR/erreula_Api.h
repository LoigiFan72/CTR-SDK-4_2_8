/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     erreula_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47400 $
 *---------------------------------------------------------------------------*/

#ifndef NN_ERREULA_CTR_ERREULA_API_H_
#define NN_ERREULA_CTR_ERREULA_API_H_

#include <nn/types.h>
#include <nn/applet.h>

#ifdef  __cplusplus

namespace nn
{
namespace erreula
{
namespace CTR
{

/* Please see man pages for details 
    
*/
enum
{
    ERROR_LANGUAGE_FLAG = 0x100,    //
    ERROR_WORD_WRAP_FLAG = 0x200    //
};

/* Please see man pages for details 
    
*/
enum ErrorType
{
    ERROR_TYPE_ERROR_CODE = 0,      //
    ERROR_TYPE_ERROR_TEXT,          //
    ERROR_TYPE_EULA,                //
    ERROR_TYPE_EULA_FIRST_BOOT,     //
    ERROR_TYPE_EULA_DRAW_ONLY,      //
    ERROR_TYPE_AGREE,               //

    ERROR_TYPE_ERROR_CODE_LANGUAGE = ERROR_TYPE_ERROR_CODE | ERROR_LANGUAGE_FLAG,   //
    ERROR_TYPE_ERROR_TEXT_LANGUAGE = ERROR_TYPE_ERROR_TEXT | ERROR_LANGUAGE_FLAG,   //
    ERROR_TYPE_EULA_LANGUAGE = ERROR_TYPE_EULA | ERROR_LANGUAGE_FLAG,               //

    ERROR_TYPE_ERROR_TEXT_WORD_WRAP = ERROR_TYPE_ERROR_TEXT | ERROR_WORD_WRAP_FLAG, //
    ERROR_TYPE_ERROR_TEXT_LANGAUAGE_WORD_WRAP = ERROR_TYPE_ERROR_TEXT | ERROR_LANGUAGE_FLAG | ERROR_WORD_WRAP_FLAG, //

    ERROR_TYPE_MAX_BIT = (1u << 31)  //!< Enumerator used during internal processing. This enumerator cannot be used by applications.
};

/* Please see man pages for details 
    
*/
enum
{
    UPPER_SCREEN_NORMAL = 0,    //
    UPPER_SCREEN_STEREO,        //

    UPPER_SCREEN_MAX
};

/* Please see man pages for details 
    
*/
enum
{
    USE_LANGUAGE_DEFAULT = 0,   //
    USE_LANGUAGE_JAPANESE,      //
    USE_LANGUAGE_ENGLISH,       //
    USE_LANGUAGE_FRENCH,        //
    USE_LANGUAGE_GERMAN,        //
    USE_LANGUAGE_ITALIAN,       //
    USE_LANGUAGE_SPANISH,       //
    USE_LANGUAGE_SIMP_CHINESE,  //
    USE_LANGUAGE_KOREAN,        //
    USE_LANGUAGE_DUTCH,         //
    USE_LANGUAGE_PORTUGUESE,    //
    USE_LANGUAGE_RUSSIAN,       //
    USE_LANGUAGE_TRAD_CHINESE,  //
    
    USE_LANGUAGE_MAX
};

/* Please see man pages for details 
    

            
*/
enum ReturnCode
{
    RETURN_CODE_UNKNOWN = -1,       //
    RETURN_CODE_NONE    = 0,        //
    RETURN_CODE_SUCCESS,            //
    RETURN_CODE_NOT_SUPPORTED,      //

    RETURN_CODE_HOME_BUTTON = 10,   //
    RETURN_CODE_SOFTWARE_RESET,     //
    RETURN_CODE_POWER_BUTTON,       //

    RETURN_CODE_MAX_BIT = (s32)(1u << 31)  //!< Enumerator used during internal processing. This enumerator cannot be used by applications.
};

/* Please see man pages for details 
    
*/
const u16 ERROR_TEXT_LENGTH_MAX = 1900;

/* Please see man pages for details 
    

    */
//    Make a structure having a maximum size of 4092 bytes.

struct Config
{
    //----------------------------------------
    //

    /* Please see man pages for details 
        
    */
    ErrorType   errorType;

    /* Please see man pages for details 
        

                
    */
    s32         errorCode;

    /* Please see man pages for details 
        
                
                
                
    */
    s16         upperScreenFlag;

    /* Please see man pages for details 
        
        
    */
    u16         useLanguage;

    /* Please see man pages for details 
        
    */
    wchar_t     errorText[ERROR_TEXT_LENGTH_MAX];

    /* Please see man pages for details 
        
                
                
    */
    bool        homeButton;

    /* Please see man pages for details 
        
                
                
    */
    bool        softwareReset;

    /* Please see man pages for details 
        
                
                
    */
    bool        appJump;

    u8          pad0[137];


    //----------------------------------------
    //

    /* Please see man pages for details 
        

                
                
    */
    ReturnCode  returnCode;

    /* Please see man pages for details 
        

                
                
    */
    u16         eulaVersion;

    u8          pad1[10];
};

/* Please see man pages for details 
    
*/
struct Parameter
{
    Config  config;  //
};

/* Please see man pages for details 
    

    
    
*/
void InitializeConfig(Config* pConfig);

/* Please see man pages for details 
    

                    
                    
*/
void PreloadErrEulaApplet();

/* Please see man pages for details 
    
*/
void CancelPreloadErrEulaApplet();

/* Please see man pages for details 
    

                    
*/
void WaitForPreloadErrEulaApplet();

/* Please see man pages for details 
    

    
                    
*/
bool IsRegisteredErrEulaApplet();

/* Please see man pages for details 
    

    
    
*/
void StartErrEulaApplet( nn::applet::AppletWakeupState* pWakeupState, Parameter* pParameter );

}}}

#endif // __cplusplus

#endif // ifndef NN_ERREULA_CTR_ERREULA_API_H_
