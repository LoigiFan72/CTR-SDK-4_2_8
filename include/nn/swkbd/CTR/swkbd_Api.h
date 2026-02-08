/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     swkbd_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SWKBD_CTR_SWKBD_API_H_
#define NN_SWKBD_CTR_SWKBD_API_H_

#include <nn/types.h>
#include <nn/applet.h>

#ifdef  __cplusplus

namespace nn
{
namespace swkbd
{
namespace CTR
{

/* Please see man pages for details 
    
*/
const u16   VERSION_NUMBER  = 5;

/* Please see man pages for details 
    
*/
enum KeyboardType
{
    KEYBOARD_TYPE_FULL = 0,             //
    KEYBOARD_TYPE_QWERTY,               //
    KEYBOARD_TYPE_TENKEY,               //
    KEYBOARD_TYPE_NO_JAPANESE,          //
    KEYBOARD_TYPE_MAX,                  //

    KEYBOARD_TYPE_MAX_BIT = (1u << 31)  //
};

/* Please see man pages for details 
    
*/
enum BottomButtonType
{
    BOTTOM_BUTTON_TYPE_1BUTTON = 0,     //
    BOTTOM_BUTTON_TYPE_2BUTTON,         //
    BOTTOM_BUTTON_TYPE_3BUTTON,         //
    BOTTOM_BUTTON_TYPE_MAX,             //

    BOTTOM_BUTTON_TYPE_MAX_BIT = (1u << 31) //
};

/* Please see man pages for details 
    
*/
enum BottomButton
{
    BOTTOM_BUTTON_0 = 0,    //
    BOTTOM_BUTTON_1,        //
    BOTTOM_BUTTON_2,        //
    BOTTOM_BUTTON_MAX,      //

    BOTTOM_BUTTON_1BUTTON           = BOTTOM_BUTTON_2,  //
    BOTTOM_BUTTON_2BUTTON_LEFT      = BOTTOM_BUTTON_0,  //
    BOTTOM_BUTTON_2BUTTON_RIGHT     = BOTTOM_BUTTON_2,  //
    BOTTOM_BUTTON_3BUTTON_LEFT      = BOTTOM_BUTTON_0,  //
    BOTTOM_BUTTON_3BUTTON_MIDDLE    = BOTTOM_BUTTON_1,  //
    BOTTOM_BUTTON_3BUTTON_RIGHT     = BOTTOM_BUTTON_2,  //

    BOTTOM_BUTTON_MAX_BIT = (1u << 31)  //
};

/* Please see man pages for details 
    
*/
enum TenkeyExtKey
{
    TENKEY_EXT_KEY_LEFT = 0,            //
    TENKEY_EXT_KEY_RIGHT,               //
    TENKEY_EXT_KEY_MAX,                 //

    TENKEY_EXT_KEY_MAX_BIT = (1u << 31) //
};

/* Please see man pages for details 
    
*/
enum FinishableCondition
{
    FINISHABLE_CONDITION_NONE = 0,          //
    FINISHABLE_CONDITION_ANY,               //
    FINISHABLE_CONDITION_NON_SPACE,         //
    FINISHABLE_CONDITION_EXCEPT_SPACE_ONLY, //
    FINISHABLE_CONDITION_FULL,              //

    FINISHABLE_CONDITION_MAX,               //

    FINISHABLE_CONDITION_MAX_BIT = (1u << 31)   //
};

/* Please see man pages for details 
    
*/
enum MaskMode
{
    MASK_MODE_DISABLE = 0,              //
    MASK_MODE_IMMEDIATE,                //
    MASK_MODE_WAIT_1SEC,                //

    MASK_MODE_MAX,                      //

    MASK_MODE_MAX_BIT = (1u << 31)      //
};

/* Please see man pages for details 
    
*/
enum ParentalControlsMode
{
    PARENTAL_CONTROLS_MODE_DISABLE = 0,     //
    PARENTAL_CONTROLS_MODE_ENABLE,          //
    PARENTAL_CONTROLS_MODE_SYSTEM_SETTINGS, //
    PARENTAL_CONTROLS_MODE_MAX,             //

    PARENTAL_CONTROLS_MODE_MAX_BIT = (1u << 31) //
};

/* Please see man pages for details 
    
*/
enum DisplayLanguage
{
    DISPLAY_LANGUAGE_DEFAULT = 0,           //
    DISPLAY_LANGUAGE_JAPANESE,              //
    DISPLAY_LANGUAGE_ENGLISH,               //
    DISPLAY_LANGUAGE_FRENCH,                //
    DISPLAY_LANGUAGE_GERMAN,                //
    DISPLAY_LANGUAGE_ITALIAN,               //
    DISPLAY_LANGUAGE_SPANISH,               //
    DISPLAY_LANGUAGE_SIMP_CHINESE,          //
    DISPLAY_LANGUAGE_KOREAN,                //
    DISPLAY_LANGUAGE_DUTCH,                 //
    DISPLAY_LANGUAGE_PORTUGUESE,            //
    DISPLAY_LANGUAGE_RUSSIAN,               //

    DISPLAY_LANGUAGE_MAX,                   //

    DISPLAY_LANGUAGE_MAX_BIT = (1u << 7)    //
};

/* Please see man pages for details 
    
*/
enum UpperScreenFlag
{
    UPPER_SCREEN_NORMAL                     = 0x0,  //
    UPPER_SCREEN_DARK                       = 0x1,  //

    UPPER_SCREEN_MAX_BIT = (1u << 31)               //
};

/* Please see man pages for details 
    
*/
enum TextCheckFlag
{
    TEXT_CHECK_DISABLE                      = 0x0,  //
    TEXT_CHECK_NUMBER                       = 0x1,  //
    TEXT_CHECK_AT_MARK                      = 0x2,  //
    TEXT_CHECK_PERCENT_SIGN                 = 0x4,  //
    TEXT_CHECK_BACKSLASH                    = 0x8,  //
    TEXT_CHECK_BANNED_WORDS                 = 0x10, //
    TEXT_CHECK_APP                          = 0x20, //

    TEXT_CHECK_MAX_BIT = (1u << 31)                 //
};

/* Please see man pages for details 
    
*/
enum ExtOutputDataFlag
{
    EXT_OUTPUT_DATA_NONE                    = 0x0,  //
    EXT_OUTPUT_DATA_STATUS                  = 0x1,  //
    EXT_OUTPUT_DATA_LEARNING                = 0x2,  //

    EXT_OUTPUT_DATA_MAX_BIT = (1u << 31)            //
};

/* Please see man pages for details 
    
*/
enum AppTextCheckResult
{
    APP_TEXT_CHECK_RESULT_OK = 0,       //
    APP_TEXT_CHECK_RESULT_NG_FINISH,    //
    APP_TEXT_CHECK_RESULT_NG_CONTINUE,  //

    APP_TEXT_CHECK_RESULT_MAX,          //

    APP_TEXT_CHECK_RESULT_MAX_BIT = (1u << 31)  //
};

/* Please see man pages for details 
    

            
*/
enum ReturnCode
{
    RETURN_CODE_UNKNOWN                         = -1,   //
    RETURN_CODE_INVALID_CONFIG                  = -2,   //
    RETURN_CODE_OUT_OF_MEMORY                   = -3,   //
    //RETURN_CODE_INVALID_VERSION                 = -4,   //
    RETURN_CODE_BOTTOM_BUTTON_1BUTTON           = 0,    //
    RETURN_CODE_BOTTOM_BUTTON_2BUTTON_LEFT      = 1,    //
    RETURN_CODE_BOTTOM_BUTTON_2BUTTON_RIGHT     = 2,    //
    RETURN_CODE_BOTTOM_BUTTON_3BUTTON_LEFT      = 3,    //
    RETURN_CODE_BOTTOM_BUTTON_3BUTTON_MIDDLE    = 4,    //
    RETURN_CODE_BOTTOM_BUTTON_3BUTTON_RIGHT     = 5,    //
    RETURN_CODE_HOME_BUTTON                     = 10,   //
    RETURN_CODE_SOFTWARE_RESET                  = 11,   //
    RETURN_CODE_POWER_BUTTON                    = 12,   //
    RETURN_CODE_PARENTAL_CONTROLS_SUCCESS       = 20,   //
    RETURN_CODE_PARENTAL_CONTROLS_FAILURE       = 21,   //
    RETURN_CODE_APP_TEXT_CHECK_NG               = 30,   //

    RETURN_CODE_MAX_BIT = (s32)(1u << 31)               //
};

/* Please see man pages for details 
    
*/
const size_t    STATUS_DATA_SIZE                        = 68;

/* Please see man pages for details 
    
*/
const size_t    LEARNING_DATA_SIZE                      = 42092;

/* Please see man pages for details 
    
*/
const u16       TEXT_LENGTH_MAX_MIN                     = 1;

/* Please see man pages for details 
    
*/
const u16       TEXT_LENGTH_MAX_MAX                     = 65000;

/* Please see man pages for details 
    
*/
const u16       FIXED_WIDTH_TEXT_LENGTH_MAX_MAX         = 32;

/* Please see man pages for details 
    
*/
const u16       TEXT_CHECK_TEXT_LENGTH_MAX_MAX          = 2000;

/* Please see man pages for details 
    
*/
const u16       BANNED_WORD_CHECK_TEXT_LENGTH_MAX_MAX   = 64;

/* Please see man pages for details 
    
*/
const u16       BOTTOM_BUTTON_TEXT_LENGTH_MAX           = 16;

/* Please see man pages for details 
    
*/
const u16       GUIDE_TEXT_LENGTH_MAX                   = 64;

/* Please see man pages for details 
    
*/
const u16       APP_TEXT_CHECK_DIALOG_TEXT_LENGTH_MAX   = 256;

/* Please see man pages for details 
    
*/
const u16       NUM_USER_WORDS_MAX                      = 500;

/* Please see man pages for details 
    
*/
const u16       USER_WORD_LENGTH_MAX                    = 40;

/* Please see man pages for details 
    
*/
const u16       USER_READING_LENGTH_MAX                 = 40;

/* Please see man pages for details 
    
*/
struct UserWord
{
    wchar_t     reading[USER_READING_LENGTH_MAX + 1];   //
    wchar_t     word[USER_WORD_LENGTH_MAX + 1];         //
    u8          language;                               //
    bool        allLanguage;                            //
};

/* Please see man pages for details 
    

    
    
    
    
*/
typedef AppTextCheckResult (*AppTextCheckCallback)(
    const wchar_t** ppDialogText,
    const wchar_t* pInputText,
    u16 inputTextLength
);

/* Please see man pages for details 
    
*/
struct Config
{
    //----------------------------------------
    //
    //

    KeyboardType        keyboardType;                           //
    BottomButtonType    bottomButtonType;                       //
    FinishableCondition finishableCondition;                    //
    MaskMode            maskMode;                               //
    ParentalControlsMode    parentalControlsMode;               //
    bit32               upperScreenFlag;                        //
    bit32               textCheckFlag;                          //
    bit32               extOutputDataFlag;                      //
    u16                 textLengthMax;                          //
    u16                 numUserWords;                           //
    u16                 numNumbersMax;                          //
    wchar_t             bottomButtonText[BOTTOM_BUTTON_MAX][BOTTOM_BUTTON_TEXT_LENGTH_MAX + 1]; //
    wchar_t             tenkeyExtKeyChar[TENKEY_EXT_KEY_MAX];   //
    wchar_t             guideText[GUIDE_TEXT_LENGTH_MAX + 1];   //
    bool                prediction;                             //
    bool                lineFeed;                               //
    bool                fixedWidthMode;                         //
    bool                homeButton;                             //
    bool                softwareReset;                          //
    bool                powerButton;                            //
    bool                communicateWithOtherRegions;            //
    bool                bootWithQwerty;                         //
    bool                bottomButtonToFinish[BOTTOM_BUTTON_MAX];//
    DisplayLanguage     displayLanguage;                        //

    u8                  padding0[2];

    //

    //----------------------------------------
    //
    //

    sptr                initialInputText;                       //
    sptr                userWordArray;                          //
    sptr                initialStatusData;                      //
    sptr                initialLearningData;                    //
    size_t              sharedMemorySize;                       //
    u16                 versionNumber;                          //
    u8                  padding1[2];

    //

    //----------------------------------------
    //
    //

    ReturnCode          returnCode;                             //
    sptr                statusData;                             //
    sptr                learningData;                           //
    sptr                inputText;                              //
    u16                 inputTextLength;                        //
    u8                  padding2[2];

    //

    //----------------------------------------
    //
    //

    AppTextCheckResult  appTextCheckResult;                     //
    wchar_t             appTextCheckDialogText[APP_TEXT_CHECK_DIALOG_TEXT_LENGTH_MAX + 1];  //

    u8                  padding3[2];

    //

    //----------------------------------------
    //
    //

    bool                skipAtMarkCheck;                        //
    u8                  reserved[171];                          //

    //
};

/* Please see man pages for details 
    
*/
struct Parameter
{
    Config                          config;     //
};

/* Please see man pages for details 
    

    
    
*/
void InitializeConfig(Config* pConfig);

/* Please see man pages for details 
    

    
    
    
    
                    
                    
*/
s32 GetSharedMemorySize(
    const Config* pConfig,
    const void* pInitialStatusData = NULL,
    const void* pInitialLearningData = NULL
);

/* Please see man pages for details 
    
*/
void PreloadKeyboardApplet();

/* Please see man pages for details 
    
*/
void CancelPreloadKeyboardApplet();

/* Please see man pages for details 
    
*/
void WaitForPreloadKeyboardApplet();

/* Please see man pages for details 
    

    
                    
*/
bool IsRegisteredKeyboardApplet();

/* Please see man pages for details 
    

    
    
    
    
    
    
    
    
    
    
*/
bool StartKeyboardApplet(
    nn::applet::AppletWakeupState* pWakeupState,
    Parameter* pParameter,
    void* pSharedMemoryAddr,
    size_t sharedMemorySize,
    const wchar_t* pInitialInputText = NULL,
    const UserWord* pUserWordArray = NULL,
    const void* pInitialStatusData = NULL,
    const void* pInitialLearningData = NULL,
    AppTextCheckCallback callback = NULL
);

}}}

#endif // __cplusplus

#endif // ifndef NN_SWKBD_CTR_SWKBD_API_H_
