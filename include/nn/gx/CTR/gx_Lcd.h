/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gx_Lcd.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GX_CTR_GX_LCD_H_
#define NN_GX_CTR_GX_LCD_H_

#include <nn/types.h>
#include <nn/assert.h>

/*--------------------------------------------------------------------------
    C API
 *-------------------------------------------------------------------------*/
/* Please see man pages for details 
  
  
*/

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NN_GX_DISPLAY0_WIDTH
#define NN_GX_DISPLAY0_WIDTH    240
#endif // NN_GX_DISPLAY0_WIDTH

#ifndef NN_GX_DISPLAY0_HEIGHT
#define NN_GX_DISPLAY0_HEIGHT   400
#endif // NN_GX_DISPLAY0_HEIGHT

#ifndef NN_GX_DISPLAY1_WIDTH
#define NN_GX_DISPLAY1_WIDTH    240
#endif // NN_GX_DISPLAY1_WIDTH

#ifndef NN_GX_DISPLAY1_HEIGHT
#define NN_GX_DISPLAY1_HEIGHT   320
#endif  // NN_GX_DISPLAY1_HEIGHT

/*
  
                
  
 */
void nngxStartLcdDisplay( void );

#ifdef  __cplusplus
} // extern "C"
#endif // __cplusplus

/*  

*/

/*--------------------------------------------------------------------------
    C++ API
 *-------------------------------------------------------------------------*/
#ifdef  __cplusplus
namespace nn {
namespace gx {
namespace CTR {

/*
  
 */
enum DisplaySize
{
    /* Please see man pages for details */
    DISPLAY0_WIDTH  = NN_GX_DISPLAY0_WIDTH,
    /* Please see man pages for details */
    DISPLAY0_HEIGHT = NN_GX_DISPLAY0_HEIGHT,
    /* Please see man pages for details */
    DISPLAY1_WIDTH  = NN_GX_DISPLAY1_WIDTH,
    /* Please see man pages for details */
    DISPLAY1_HEIGHT = NN_GX_DISPLAY1_HEIGHT
};

/*
  
  
  
 */
inline void StartLcdDisplay( void )
{
    nngxStartLcdDisplay();
}


}}} // namespace nn::gx::CTR
#endif // __cplusplus


#endif /* NN_GX_CTR_GX_LCD_H_ */
