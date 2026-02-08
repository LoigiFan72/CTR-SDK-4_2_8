/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     camera_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48613 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CAMERA_CTR_CAMERA_TYPES_H_
#define NN_CAMERA_CTR_CAMERA_TYPES_H_

#include <nn/Result.h>
#include <nn/camera/CTR/camera_CalibrationTypes.h>

namespace nn {
namespace csnd {
namespace CTR {

struct DataInfo;

struct ChannelParam;

struct OptionInfo;

}
}
}

namespace nn {
namespace camera {
namespace CTR {
    /* Please see man pages for details 
      
    */
    enum CameraSelect
    {
        SELECT_NONE      = 0,                                   //
        SELECT_OUT1      = (1<<0),                              //
        SELECT_IN1       = (1<<1),                              //
        SELECT_IN1_OUT1  = (SELECT_OUT1|SELECT_IN1),            //
        SELECT_OUT2      = (1<<2),                              //
        SELECT_OUT1_OUT2 = (SELECT_OUT1|SELECT_OUT2),           //
        SELECT_IN1_OUT2  = (SELECT_IN1|SELECT_OUT2),            //
        SELECT_ALL       = (SELECT_OUT1|SELECT_IN1|SELECT_OUT2) //
    };
    /* Please see man pages for details 
      
    */
    enum Port
    {
        PORT_NONE = 0,                    //
        PORT_CAM1 = (1<<0),               //
        PORT_CAM2 = (1<<1),               //
        PORT_BOTH = (PORT_CAM1|PORT_CAM2) //
    };
    /* Please see man pages for details 
      
    */
    enum Context
    {
        CONTEXT_NONE = 0,                    //
        CONTEXT_A    = (1<<0),               //
        CONTEXT_B    = (1<<1),               //
        CONTEXT_BOTH = (CONTEXT_A|CONTEXT_B) //
    };
    /* Please see man pages for details 
      
    */
    enum Flip
    {
        FLIP_NONE = 0,   //
        FLIP_HORIZONTAL, //
        FLIP_VERTICAL,   //
        FLIP_REVERSE,    //
        FLIP_MAX
    };
    /* Please see man pages for details 
      
    */
    enum Size
    {
        SIZE_VGA,           //
        SIZE_QVGA,          //
        SIZE_QQVGA,         //
        SIZE_CIF,           //
        SIZE_QCIF,          //
        SIZE_DS_LCD,        //
        SIZE_DS_LCDx4,      //
        SIZE_CTR_TOP_LCD,   //

        CAMERA_SIZE_MAX,
        
        SIZE_CTR_BOTTOM_LCD = SIZE_QVGA     //
    };
    /* Please see man pages for details 
      
    */
    enum FrameRate
    {
        FRAME_RATE_15 = 0,   //
        FRAME_RATE_15_TO_5,  //
        FRAME_RATE_15_TO_2,  //
        FRAME_RATE_10,       //
        FRAME_RATE_8_5,      //
        FRAME_RATE_5,        //
        FRAME_RATE_20,       //
        FRAME_RATE_20_TO_5,  //
        FRAME_RATE_30,       //
        FRAME_RATE_30_TO_5,  //
        FRAME_RATE_15_TO_10, //
        FRAME_RATE_20_TO_10, //
        FRAME_RATE_30_TO_10, //
        FRAME_RATE_MAX
    };
    /* Please see man pages for details 
      
    */
    enum WhiteBalance
    {
        WHITE_BALANCE_AUTO,

        WHITE_BALANCE_3200K,
        WHITE_BALANCE_4150K,
        WHITE_BALANCE_5200K,
        WHITE_BALANCE_6000K,
        WHITE_BALANCE_7000K,

        WHITE_BALANCE_MAX,

        // alias
        WHITE_BALANCE_NORMAL                     = WHITE_BALANCE_AUTO,  //
        WHITE_BALANCE_TUNGSTEN                   = WHITE_BALANCE_3200K, //
        WHITE_BALANCE_WHITE_FLUORESCENT_LIGHT    = WHITE_BALANCE_4150K, //
        WHITE_BALANCE_DAYLIGHT                   = WHITE_BALANCE_5200K, //
        WHITE_BALANCE_CLOUDY                     = WHITE_BALANCE_6000K, //
        WHITE_BALANCE_HORIZON                    = WHITE_BALANCE_6000K, //
        WHITE_BALANCE_SHADE                      = WHITE_BALANCE_7000K  //
    };
    /* Please see man pages for details 
      
    */
    enum PhotoMode
    {
        PHOTO_MODE_NORMAL,    //
        PHOTO_MODE_PORTRAIT,  //
        PHOTO_MODE_LANDSCAPE, //
        PHOTO_MODE_NIGHTVIEW, //
        PHOTO_MODE_LETTER,    //

        PHOTO_MODE_MAX
    };
    /* Please see man pages for details 
      
    */
    enum Effect
    {
        EFFECT_NONE,     //
        EFFECT_MONO,     //
        EFFECT_SEPIA,    //
        EFFECT_NEGATIVE, //
        EFFECT_NEGAFILM, //
        EFFECT_SEPIA01,  //

        EFFECT_MAX
    };
    /* Please see man pages for details 
      
    */
    enum Contrast
    {
        CONTRAST_PATTERN_01,    //
        CONTRAST_PATTERN_02,    //
        CONTRAST_PATTERN_03,    //
        CONTRAST_PATTERN_04,    //
        CONTRAST_PATTERN_05,    //
        CONTRAST_PATTERN_06,    //
        CONTRAST_PATTERN_07,    //
        CONTRAST_PATTERN_08,    //
        CONTRAST_PATTERN_09,    //
        CONTRAST_PATTERN_10,    //
        CONTRAST_PATTERN_11,    //

        CONTRAST_MAX,

        CONTRAST_LOW    = CONTRAST_PATTERN_05,  //
        CONTRAST_NORMAL = CONTRAST_PATTERN_06,  //
        CONTRAST_HIGH   = CONTRAST_PATTERN_07   //
    };
    /* Please see man pages for details 
      

                
                
    */
    enum LensCorrection
    {
        LENS_CORRECTION_OFF,        //
        LENS_CORRECTION_ON_70,      //
        LENS_CORRECTION_ON_90,      //
        
        LENS_CORRECTION_MAX,
        
        LENS_CORRECTION_DARK    = LENS_CORRECTION_OFF,      //
        LENS_CORRECTION_NORMAL  = LENS_CORRECTION_ON_70,    //
        LENS_CORRECTION_BRIGHT  = LENS_CORRECTION_ON_90     //
    };
    /* Please see man pages for details 
      
      
                    

    */
    enum OutputFormat
    {
        OUTPUT_YUV_422, //
        OUTPUT_RGB_565, //
        
        OUTPUT_MAX
    };
    /* Please see man pages for details 
      
    */
    enum ShutterSoundType
    {
        SHUTTER_SOUND_TYPE_NORMAL,    //
        SHUTTER_SOUND_TYPE_MOVIE,     //
        SHUTTER_SOUND_TYPE_MOVIE_END, //
        SHUTTER_SOUND_TYPE_MAX
    };

    /* Please see man pages for details 
      
    */
    struct PackageParameterCameraSelect
    {
        util::SizedEnum1<CameraSelect>    camera;                         //

        s8                                exposure;                       //
        util::SizedEnum1<WhiteBalance>    whiteBalance;                   //
        s8                                sharpness;                      //
        bool                              autoExposureOn;                 //
        bool                              autoWhiteBalanceOn;             //
        util::SizedEnum1<FrameRate>       frameRate;                      //
        util::SizedEnum1<PhotoMode>       photoMode;                      //
        util::SizedEnum1<Contrast>        contrast;                       //
        util::SizedEnum1<LensCorrection>  lensCorrection;                 //
        bool                              noiseFilterOn;                  //
        NN_PADDING1;
        s16             autoExposureWindowStartX;       //
        s16             autoExposureWindowStartY;       //
        s16             autoExposureWindowWidth;        //
        s16             autoExposureWindowHeight;       //
        s16             autoWhiteBalanceWindowStartX;   //
        s16             autoWhiteBalanceWindowStartY;   //
        s16             autoWhiteBalanceWindowWidth;    //
        s16             autoWhiteBalanceWindowHeight;   //
    };

    /* Please see man pages for details 
      
                
    */
    struct PackageParameterContext
    {
        util::SizedEnum1<CameraSelect>    camera;     //
        util::SizedEnum1<Context>         context;    //

        util::SizedEnum1<Flip>            flip;       //
        util::SizedEnum1<Effect>          effect;     //
        util::SizedEnum1<Size>            size;       //
    };

    /* Please see man pages for details 
      
                
    */
    struct PackageParameterContextDetail
    {
        util::SizedEnum1<CameraSelect>    camera;     //
        util::SizedEnum1<Context>         context;    //

        util::SizedEnum1<Flip>            flip;       //
        util::SizedEnum1<Effect>          effect;     //
        s16             width;      //
        s16             height;     //
        s16             cropX0;     //
        s16             cropY0;     //
        s16             cropX1;     //
        s16             cropY1;     //
    };

} // namespace CTR
} // namespace camera
} // namespace nn

#endif //NN_CAMERA_CTR_CAMERA_TYPES_H_
