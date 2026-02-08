/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ulcd_StereoCamera.h

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

#ifndef NN_ULCD_CTR_STEREO_CAMERA_H_
#define NN_ULCD_CTR_STEREO_CAMERA_H_

#include <nn/WithInitialize.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/math.h>

namespace nn {
namespace ulcd {
namespace CTR {

    /* Please see man pages for details 
        
    */
    class StereoCamera
    {
    public:

        /* Please see man pages for details 
            
            
                     
            
            
        */
        StereoCamera();
        /* Please see man pages for details 
            
            
            
        */
        StereoCamera(const nn::WithInitialize&);
        /* Please see man pages for details 
            
            
                     
            
            
        */
        ~StereoCamera();
        
        /* Please see man pages for details 
            
            
            
        */
        void Initialize(void);
        /* Please see man pages for details 
            
            
            
        */
        void Finalize(void);
        /* Please see man pages for details 
            
            
            
            
            
            
            
        */
        void SetBaseFrustum(const nn::math::Matrix44 *proj);
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            
            
            
            
        */
        void SetBaseFrustum(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 near, const f32 far);
        /* Please see man pages for details 
            
            
            
            
            
            
            
        */
        void SetBaseCamera(const nn::math::Matrix34 *view);
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            
            
        */
        void SetBaseCamera(const nn::math::Vector3 *position, const nn::math::Vector3 *rightDir,
                           const nn::math::Vector3 *upDir, const nn::math::Vector3 *targetDir);
        /* Please see man pages for details 
            
            
            
            
            
        */
        void SetLimitParallax(const f32 limit);
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            
            
            
            
            
        */
        void CalculateMatrices(nn::math::Matrix44* projL, nn::math::Matrix34* viewL,
                               nn::math::Matrix44* projR, nn::math::Matrix34* viewR,
                               const f32 depthLevel, const f32 factor,
                               const nn::math::PivotDirection pivot = nn::math::PIVOT_UPSIDE_TO_TOP);
        
        /* Please see man pages for details 
            
            
            
            
            
            
            
            
            
            
            
        */
        void CalculateMatricesReal(nn::math::Matrix44* projL, nn::math::Matrix34* viewL,
                                   nn::math::Matrix44* projR, nn::math::Matrix34* viewR,
                                   const f32 depthLevel, const f32 factor,
                                   const nn::math::PivotDirection pivot = nn::math::PIVOT_UPSIDE_TO_TOP);
        /* Please see man pages for details 
            
            
            

            
            
            
            
            
            
            
            
            

            
        */
        f32 CalculateMatrices( nn::math::Matrix44* projL, nn::math::Matrix34* viewL,
                               nn::math::Matrix44* projR, nn::math::Matrix34* viewR,
                               const nn::math::Matrix44* projOriginal, const nn::math::Matrix34* viewOriginal,
                               const f32 depthLevel, const f32 factor, const bool realSwitch);
        /* Please see man pages for details 
            
            
            
            
            
         */
        f32 GetParallax(const f32 distance) const;
        /* Please see man pages for details 
            
            
                     
         */
        f32 GetCoefficientForParallax(void) const;
        /* Please see man pages for details 
            
            
                     
         */
        f32 GetMaxParallax(void) const;
        /* Please see man pages for details 
            
            
            
         */
        f32 GetLimitParallax(void) const { return m_LimitParallax; }
        /* Please see man pages for details 
            
            
                     
         */
        f32 GetDistanceToLevel(void) const { return m_DepthLevel; }
        /* Please see man pages for details 
            
            
                     
         */
        f32 GetDistanceToNearClip(void) const { return m_DistanceToNearClip; }
        /* Please see man pages for details 
            
            
                     
         */
        f32 GetDistanceToFarClip(void) const { return m_DistanceToFarClip; }
        
    private:

        struct CameraInfo
        {
            f32 left;       //
            f32 right;      //
            f32 bottom;     //
            f32 top;        //
            f32 near;       //
            f32 far;        //
            
            nn::math::Vector3 position;     //
            nn::math::Vector3 rightDir;     //
            nn::math::Vector3 upDir;        //
            nn::math::Vector3 targetDir;    //
        };

        CameraInfo m_BaseCamera;
        
        f32 m_LimitParallax;
        
        f32 m_LevelWidth;
        f32 m_DepthLevel;
        f32 m_DistanceToNearClip;
        f32 m_DistanceToFarClip;
        f32 m_CameraInterval;

//        bool m_IsInitialized;
//        u8   rsv[3];
    };

}   // namespace CTR {
}   // namespace ulcd {
}   // namespace nn {


#endif  // #ifndef NN_ULCD_CTR_STEREO_CAMERA_H_

