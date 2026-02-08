/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     phtsel_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_PHTSEL_CTR_PHTSEL_API_H_
#define NN_PHTSEL_CTR_PHTSEL_API_H_

/* Please see man pages for details 
  
  
*/

#include <nn/types.h>
#include <nn/applet.h>
#include <nn/phtsel/CTR/phtsel_input.h>
#include <nn/phtsel/CTR/phtsel_output.h>

#ifdef  __cplusplus

namespace nn {
namespace phtsel {
namespace CTR {

/* Please see man pages for details 
    
*/
static const u32    VERSION = 0;

/* Please see man pages for details 
    
    
    
*/
struct Config
{
    /* Please see man pages for details 
        
        
        
    */
    static const size_t CONFIG_RESERVED_SIZE    = 200;

    //----------------------------------------
    //
    //
    /* Please see man pages for details 
        
    */
    u32                 version;

    /* Please see man pages for details 
        
    */
    bool                enableSoftReset;
    /* Please see man pages for details 
        
    */
    bool                enableHomeButton;

    NN_PADDING2;

    /* Please see man pages for details 
        
        
        
    */
    u8                  reserved[CONFIG_RESERVED_SIZE];
    //
};

/* Please see man pages for details 
    
    
    
*/
struct Parameter
{
    Config          config;   //
    PhtselInput     input;    //
    PhtselOutput    output;   //
};

/* Please see man pages for details 
    

    
    
*/
void InitializeParameter(Parameter& parameter);

/* Please see man pages for details 
    
    
    
    
*/
bool PreloadPhtsel();

/* Please see man pages for details 
    
    
    
    
*/
bool CancelPreloadPhtsel();

/* Please see man pages for details 
    
*/
void WaitForPreloadPhtsel();

/* Please see man pages for details 
    

    
                    

*/
bool IsRegisteredPhtsel();

/* Please see man pages for details 
    
    
*/
size_t GetWorkBufferSize();

/* Please see man pages for details 
    

    
    
    
                    
                    
                    
*/
nn::applet::AppletWakeupState StartPhtsel(Parameter* pParameter, void* pWorkBuffer);

/* Please see man pages for details 
    

    
    
                    
*/
nn::applet::AppletWakeupState StartPhtselNoCapture(Parameter* pParameter);

} // end of namespace CTR
} // end of namespace phtsel
} // end of namespace nn

#endif /*__cplusplus*/

#endif /* NN_PHTSEL_CTR_PHTSEL_API_H_ */
