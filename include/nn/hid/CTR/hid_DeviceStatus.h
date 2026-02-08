/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_DeviceStatus.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

*/

#ifndef NN_HID_CTR_HID_DEVICESTATUS_H_
#define NN_HID_CTR_HID_DEVICESTATUS_H_

#include <nn/types.h>
#include <nn/math/math_Types.h>
#include <nn/config.h>

namespace nn {
namespace hid {
namespace CTR {

/* Please see man pages for details */
const bit32 BUTTON_A                = 0x00000001;
/* Please see man pages for details */
const bit32 BUTTON_B                = 0x00000002;
const bit32 PSEUDO_BUTTON_SELECT    = 0x00000004;
/* Please see man pages for details 
  

              
              
*/
const bit32 BUTTON_SELECT_FOR_DEBUGGING = 0x00000004;
/* Please see man pages for details */
const bit32 BUTTON_START            = 0x00000008;
/* Please see man pages for details */
const bit32 BUTTON_RIGHT            = 0x00000010;
/* Please see man pages for details */
const bit32 BUTTON_LEFT             = 0x00000020;
/* Please see man pages for details */
const bit32 BUTTON_UP               = 0x00000040;
/* Please see man pages for details */
const bit32 BUTTON_DOWN             = 0x00000080;
/* Please see man pages for details */
const bit32 BUTTON_R                = 0x00000100;
/* Please see man pages for details */
const bit32 BUTTON_L                = 0x00000200;
/* Please see man pages for details */
const bit32 BUTTON_X                = 0x00000400;
/* Please see man pages for details */
const bit32 BUTTON_Y                = 0x00000800;
/* Please see man pages for details 
    

    
*/
const bit32 BUTTON_DEBUG            = 0x00001000;
const bit32 BUTTON_RESERVED         = 0x00002000;


/* Please see man pages for details */
const bit32 BUTTON_EMULATION_RIGHT  = 0x10000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_LEFT   = 0x20000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_UP     = 0x40000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_DOWN   = 0x80000000;

/* Please see man pages for details */
const bit32 BUTTON_MASK             = BUTTON_A | BUTTON_B | BUTTON_START |
                                      BUTTON_R | BUTTON_L | BUTTON_X | BUTTON_Y | BUTTON_DEBUG;
/* Please see man pages for details */
const bit32 PLUS_BUTTON_MASK        = BUTTON_RIGHT | BUTTON_LEFT | BUTTON_UP | BUTTON_DOWN;
/* Please see man pages for details */
const bit32 PLUS_BUTTON_EMULATION_MASK  = BUTTON_EMULATION_RIGHT | BUTTON_EMULATION_LEFT | BUTTON_EMULATION_UP | BUTTON_EMULATION_DOWN;
/* Please see man pages for details */
const bit32 ALL_MASK                = BUTTON_MASK | PLUS_BUTTON_MASK | PLUS_BUTTON_EMULATION_MASK;

/*
 * Related to Circle Pad Pro
 */
/* Please see man pages for details */
const bit32 BUTTON_ZL = 0x00004000;
/* Please see man pages for details */
const bit32 BUTTON_ZR = 0x00008000;

/* Please see man pages for details */
const bit32 BUTTON_EMULATION_R_RIGHT  = 0x01000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_R_LEFT   = 0x02000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_R_UP     = 0x04000000;
/* Please see man pages for details */
const bit32 BUTTON_EMULATION_R_DOWN   = 0x08000000;

/* Please see man pages for details */
const bit32 PLUS_BUTTON_EMULATION_R_MASK = BUTTON_EMULATION_R_RIGHT | BUTTON_EMULATION_R_LEFT | BUTTON_EMULATION_R_UP | BUTTON_EMULATION_R_DOWN;



/* Please see man pages for details 

*/
typedef struct
{
    /* Please see man pages for details */
    s16         x;
    /* Please see man pages for details */
    s16         y;
} AnalogStickStatus;

/* Please see man pages for details 
    
*/
typedef struct
{
    /* Please see man pages for details */
    bit32             hold;
    /* Please see man pages for details */
    bit32             trigger;
    /* Please see man pages for details */
    bit32             release;
    /* Please see man pages for details */
    AnalogStickStatus stick;
} PadStatus;

/* Please see man pages for details 
    

           
           
*/
typedef struct
{
    /* Please see man pages for details */
    u16         x;
    /* Please see man pages for details */
    u16         y;
    /* Please see man pages for details */
    u8          touch;
    NN_PADDING3;
} TouchPanelStatus;

/* Please see man pages for details 
    
*/
typedef struct
{
    /* Please see man pages for details */
    s16         x;
    /* Please see man pages for details */
    s16         y;
    /* Please see man pages for details */
    s16         z;
}AccelerometerStatus;

/* Please see man pages for details 
    
*/
typedef struct
{
    /* Please see man pages for details */
    f32         x;
    /* Please see man pages for details */
    f32         y;
    /* Please see man pages for details */
    f32         z;
}AccelerationFloat;

/* Please see man pages for details 
    
*/
struct Direction{
public :
    /* Please see man pages for details */
    nn::math::VEC3 x;/**/

    /* Please see man pages for details */
    nn::math::VEC3 y;

    /* Please see man pages for details */
    nn::math::VEC3 z;

public :
    /* Please see man pages for details */
    Direction()
    {};

    /* Please see man pages for details */
    explicit Direction(const nn::math::VEC3& vecx,const nn::math::VEC3& vecy,const nn::math::VEC3& vecz)
    :x(vecx),y(vecy),z(vecz){}

    /* Please see man pages for details */
    Direction(const nn::math::MTX33 &mtx33)
    :x(mtx33.v[0]),y(mtx33.v[1]),z(mtx33.v[2]){}

    /* Please see man pages for details */
    nn::math::MTX33 ToMTX33()
    {
        return nn::math::MTX33(
            x.x,x.y,x.z,
            y.x,y.y,y.z,
            z.x,z.y,z.z);
    }
};

/* Please see man pages for details 
    

    
    
    
    
    
*/
typedef struct {
    /* Please see man pages for details */
    nn::math::VEC3  speed;
    /* Please see man pages for details */
    nn::math::VEC3  angle;
    /* Please see man pages for details */
    Direction       direction;
} GyroscopeStatus;

/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_UP           = 0x00000001;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_LEFT         = 0x00000002;
/* Please see man pages for details */
const bit16 DEBUG_PAD_TRIGGER_ZR          = 0x00000004;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_X            = 0x00000008;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_A            = 0x00000010;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_Y            = 0x00000020;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_B            = 0x00000040;
/* Please see man pages for details */
const bit16 DEBUG_PAD_TRIGGER_ZL          = 0x00000080;
const bit16 DEBUG_PAD_RESERVED            = 0x00000100;
/* Please see man pages for details */
const bit16 DEBUG_PAD_TRIGGER_R           = 0x00000200;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_PLUS         = 0x00000400;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_HOME         = 0x00000800;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_MINUS        = 0x00001000;
/* Please see man pages for details */
const bit16 DEBUG_PAD_TRIGGER_L           = 0x00002000;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_DOWN         = 0x00004000;
/* Please see man pages for details */
const bit16 DEBUG_PAD_BUTTON_RIGHT        = 0x00008000;


/* Please see man pages for details 
    
*/
typedef struct
{
    /* Please see man pages for details */
    bit16             hold;
    /* Please see man pages for details */
    bit16             trigger;
    /* Please see man pages for details */
    bit16             release;
    NN_PADDING2;
    /* Please see man pages for details */
    f32               leftStickX;
    /* Please see man pages for details */
    f32               leftStickY;
    /* Please see man pages for details */
    f32               rightStickX;
    /* Please see man pages for details */
    f32               rightStickY;
} DebugPadStatus;



} // namespace CTR
} // namespace hid
} // namespace nn

#endif  //  NN_HID_CTR_HID_DEVICESTATUS_H_
