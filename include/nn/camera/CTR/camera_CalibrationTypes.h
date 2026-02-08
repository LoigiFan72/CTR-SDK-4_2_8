/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     camera_CalibrationTypes.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CAMERA_CTR_CAMERA_CALIBRATION_TYPES_H_
#define NN_CAMERA_CTR_CAMERA_CALIBRATION_TYPES_H_

namespace nn {
namespace camera {
namespace CTR {

    /* Please see man pages for details 
      
    */
    struct StereoCameraCalibrationData
    {
        //----------------------------------------
        //
        //

        //
        struct Flags
        {
            //
            bool  isValidRotationXY;

            //
            bool  reservedFlag[ 3 ];
        }
        flags;

        //

        //----------------------------------------
        //
        //

        //
        f32  scale;

        //
        f32  rotationZ;

        //
        f32  translationX;   

        //
        f32  translationY;

        //
        f32  rotationX;

        //
        f32  rotationY;

        //
        f32  angleOfViewRight;

        //
        f32  angleOfViewLeft;

        //

        //----------------------------------------
        //
        //

        //
        f32  distanceToChart;

        //
        f32  distanceCameras;

        //
        s16  imageWidth;

        //
        s16  imageHeight;

        //

        //----------------------------------------
        //
        //

        //
        u8   reserved[ 16 ];

        //

    }; //struct StereoCameraCalibrationData

    /* Please see man pages for details 
      

                    
    */
    struct ImageQualityCalibrationData
    {
       s16 aeBaseTarget;    // 0xA24F
       s16 kRL;             // 0xA366
       s16 kGL;             // 0xA367
       s16 kBL;             // 0xA368
       s16 ccmPosition;     // 0xA353
       u16 awbCcmL9Right;   // Right camera's 0x2318
       u16 awbCcmL9Left;    // Left camera's 0x2318
       u16 awbCcmL10Right;  // Right camera's 0x231A
       u16 awbCcmL10Left;   // Left camera's 0x231A
       u16 awbX0Right;      // Right camera's 0xA365
       u16 awbX0Left;       // Left camera's 0xA365
    };
} // namespace CTR
} // namespace camera
} // namespace nn

#endif //NN_CAMERA_CTR_CAMERA_TYPES_H_
