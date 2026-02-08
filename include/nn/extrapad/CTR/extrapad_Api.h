/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     extrapad_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_EXTRAPAD_CTR_EXTRAPAD_API_H_
#define NN_EXTRAPAD_CTR_EXTRAPAD_API_H_

#include <nn/types.h>
#include <nn/applet.h>

#ifdef  __cplusplus

namespace nn
{
namespace extrapad
{
namespace CTR
{

/* Please see man pages for details 
    

            
*/
enum ReturnCode
{
    RETURN_CODE_UNKNOWN = -1,       //
    RETURN_CODE_NONE    = 0,        //
    RETURN_CODE_SUCCESS,            //

    RETURN_CODE_HOME_BUTTON = 10,   //
    RETURN_CODE_SOFTWARE_RESET,     //
    RETURN_CODE_POWER_BUTTON,       //

    RETURN_CODE_MAX_BIT = (s32)(1u << 31)   //
};

/* Please see man pages for details 
    

    

*/
//    Make a structure having a maximum size of 4092 bytes.
struct Config
{
    //----------------------------------------
    //

    /* Please see man pages for details 
        

                
                
    */
    bool        homeButton;

    /* Please see man pages for details 
        

                
                
    */
    bool        softwareReset;

    u8          pad0[62];


    //----------------------------------------
    //

    /* Please see man pages for details 
        

                
                
    */
    ReturnCode  returnCode;

    u8          pad1[60];
};

/* Please see man pages for details 
    
*/
struct Parameter
{
    Config  config; //
};

/* Please see man pages for details 
    

    
    
*/
void InitializeConfig(Config* pConfig);

/* Please see man pages for details 
    

                    
                    
*/
void PreloadExtraPadApplet();

/* Please see man pages for details 
    
*/
void CancelPreloadExtraPadApplet();

/* Please see man pages for details 
    

                    
*/
void WaitForPreloadExtraPadApplet();

/* Please see man pages for details 
    

    
                    

*/
bool IsRegisteredExtraPadApplet();

/* Please see man pages for details 
    
    
    
                    

    
    

*/
void StartExtraPadApplet( nn::applet::AppletWakeupState* pWakeupState, Parameter* pParameter );

}}}

#endif // __cplusplus

#endif // ifndef NN_EXTRAPAD_CTR_EXTRAPAD_API_H_
