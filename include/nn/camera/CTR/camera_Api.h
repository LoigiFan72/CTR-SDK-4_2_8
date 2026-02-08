/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     camera_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48613 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CAMERA_CTR_CAMERA_API_H_
#define NN_CAMERA_CTR_CAMERA_API_H_

/* Please see man pages for details 
    
*/

#include <nn/os.h>
#include <nn/math.h>
#include <nn/camera/CTR/camera_Types.h>
#include <nn/y2r/CTR/y2r_Types.h>

#include <nn/camera/CTR/camera_Camera.h>

namespace nn {
namespace camera {
namespace CTR {

    namespace detail
    {
        nn::Result InitializeBase(Handle* pSession, const char* name, bool isCheck = false);
        void FinalizeBase(Handle* pSession);
        bool IsInitialized();
        void StartCapture( Port port );
        void StopCapture( Port port );
        bool IsBusy( Port port );
        void ClearBuffer( Port port );
        void GetVsyncInterruptEvent( nn::os::Event* pEvent, Port port );
        void GetBufferErrorInterruptEvent( nn::os::Event* pEvent, Port port );
        void SetReceiving( nn::os::Event* pEvent, u32 pDst, Port port, size_t imageSize, s16 transferUnit );
        bool IsFinishedReceiving( Port port );
        void SetTransferLines( Port port, s16 lines, s16 width, s16 height );
        s16 GetMaxLines( s16 width, s16 height );
        void SetTransferBytes( Port port, size_t bytes, s16 width, s16 height );
        size_t GetTransferBytes( Port port );
        size_t GetMaxBytes( s16 width, s16 height );
        void SetTrimming( Port port, bool enable );
        bool IsTrimming( Port port );
        void SetTrimmingParams( Port port, s16 xStart, s16 yStart, s16 xEnd, s16 yEnd );
        void GetTrimmingParams( s16* pXStart, s16* pYStart, s16* pXEnd, s16* pYEnd, Port port );
        void SetTrimmingParamsCenter( Port port, s16 trimWidth, s16 trimHeight, s16 camWidth, s16 camHeight );

        nn::Result Activate( CameraSelect select );
        nn::Result SwitchContext( CameraSelect select, Context next );
        nn::Result SetExposure( CameraSelect select, s8 exposure );
        nn::Result SetWhiteBalance( CameraSelect select, WhiteBalance wb );
        nn::Result SetSharpness( CameraSelect select, s8 sharpness );
        nn::Result SetAutoExposure( CameraSelect select, bool on );
        nn::Result IsAutoExposure( bool* pOn, CameraSelect select );
        nn::Result SetAutoWhiteBalance( CameraSelect select, bool on );
        nn::Result IsAutoWhiteBalance( bool* pOn, CameraSelect select );
        nn::Result FlipImage( CameraSelect select, Flip flip, Context context );
        nn::Result SetDetailSize( CameraSelect select, s16 width, s16 height, s16 cropX0, s16 cropY0, s16 cropX1, s16 cropY1, Context context );
        nn::Result SetSize( CameraSelect select, Size size, Context context );
        nn::Result SetFrameRate( CameraSelect select, FrameRate rate );
        nn::Result SetPhotoMode( CameraSelect select, PhotoMode mode );
        nn::Result SetEffect( CameraSelect select, Effect effect, Context context );
        nn::Result SetContrast( CameraSelect select, Contrast contrast );
        nn::Result SetLensCorrection( CameraSelect select, LensCorrection correction );
        nn::Result SetOutputFormat( CameraSelect select, OutputFormat format, Context context );
        nn::Result SetAutoExposureWindow( CameraSelect select, s16 startX, s16 startY, s16 width, s16 height );
        nn::Result SetAutoWhiteBalanceWindow( CameraSelect select, s16 startX, s16 startY, s16 width, s16 height );
        nn::Result SetNoiseFilter( CameraSelect select, bool on );
        nn::Result SynchronizeVsyncTiming( CameraSelect select1, CameraSelect select2 );
        nn::Result SetBrightnessSynchronization( bool enable );
        void GetLatestVsyncTiming( nn::fnd::TimeSpan *pTime, Port port, size_t past );
        void GetStereoCameraCalibrationData( StereoCameraCalibrationData * pDst );
        f32  GetParallaxOnChart( const StereoCameraCalibrationData & cal );
        f32  GetParallax( const StereoCameraCalibrationData & cal, const f32 distance );
        void GetStereoCameraCalibrationMatrixOld( nn::math::MTX34 * pDst, const StereoCameraCalibrationData & cal, const f32 translationByPixel, const bool isIncludeParallax );
        void GetStereoCameraCalibrationMatrix( nn::math::MTX34 * pDst, const StereoCameraCalibrationData & cal, const f32 translationByPixel, const bool isIncludeParallax );
        void GetStereoCameraCalibrationMatrixEx(
                    nn::math::MTX34 * pDstR,
                    nn::math::MTX34 * pDstL,
                    f32             * pDstScale,
                    const StereoCameraCalibrationData & cal,
                    const f32       translationByPixel,
                    const f32       parallax,
                    const s16       orgWidth,
                    const s16       orgHeight,
                    const s16       dstWidth,
                    const s16       dstHeight );

        // Batch parameter settings utility functions
        nn::Result SetPackageParameterWithoutContext(const PackageParameterCameraSelect& param);
        nn::Result SetPackageParameterWithContext(const PackageParameterContext& param);
        nn::Result SetPackageParameterWithContext(const PackageParameterContextDetail& param);

        nn::Result GetSuitableY2rStandardCoefficient(nn::y2r::CTR::StandardCoefficient* no);

        nn::Result PlayShutterSound( ShutterSoundType type );

        nn::Result LeaveApplication();
        nn::Result ArriveApplication();
    }

    namespace
    {
        const char PORT_NAME_USER[]      = "cam:u";
    }

    /* Please see man pages for details 
    

    
    
    
    
    
    

    */
    nn::Result Initialize();

    inline nn::Result Initialize() { return detail::InitializeBase(&detail::Camera::s_Session, PORT_NAME_USER); }

    /* Please see man pages for details 
    

    
    */
    void Finalize();

    inline void Finalize()    { detail::FinalizeBase(&detail::Camera::s_Session); }

    /* Please see man pages for details 
      

      
      
    */
    inline void StartCapture( Port port )
    {
        detail::StartCapture(port);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void StopCapture( Port port )
    {
        detail::StopCapture(port);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline bool IsBusy( Port port )
    {
        return detail::IsBusy(port);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void ClearBuffer( Port port )
    {
        detail::ClearBuffer(port);
    }
    /* Please see man pages for details 
      

      
      
      
    */
    inline void GetVsyncInterruptEvent( nn::os::Event* pEvent, Port port )
    {
        detail::GetVsyncInterruptEvent(pEvent, port);
    }
    /* Please see man pages for details 
      

                    

      
      
      
    */
    inline void GetBufferErrorInterruptEvent( nn::os::Event* pEvent, Port port )
    {
        detail::GetBufferErrorInterruptEvent(pEvent, port);
    }
    /* Please see man pages for details 
      
                    

      
      
      
      
      
      
    */
    inline void SetReceiving( nn::os::Event* pEvent, void* pDst, Port port, size_t imageSize, s16 transferUnit )
    {
        detail::SetReceiving(pEvent, reinterpret_cast<u32>(pDst), port, imageSize, transferUnit);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline bool IsFinishedReceiving( Port port )
    {
        return detail::IsFinishedReceiving(port);
    }
    /* Please see man pages for details 
      

                    

      
      
                              
                              
                              
                              
      
      
      
    */
    inline void SetTransferLines( Port port, s16 lines, s16 width, s16 height )
    {
        detail::SetTransferLines(port, lines, width, height);
    }
    /* Please see man pages for details 
      

                      
                      

                      
                      
                      
                      

      
      
      
    */
    inline s16 GetMaxLines( s16 width, s16 height )
    {
        return detail::GetMaxLines( width, height );
    }
    /* Please see man pages for details 
      

                    

      
      
                              
                              
                              
      
      
      
    */
    inline void SetTransferBytes( Port port, size_t bytes, s16 width, s16 height )
    {
        detail::SetTransferBytes(port, bytes, width, height);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline size_t GetTransferBytes( Port port )
    {
        return detail::GetTransferBytes(port);
    }
    /* Please see man pages for details 
      

                      
                      
                      
                      

      
      
      
    */
    inline size_t GetMaxBytes( s16 width, s16 height )
    {
        return detail::GetMaxBytes( width, height );
    }
    /* Please see man pages for details 
      

      
      
    */
    inline size_t GetLineBytes( s16 width )
    {
        return   ((width) << 1);    // Requires 2 bytes for each pixel
    }
    /* Please see man pages for details 
      

      
      
      
    */
    inline size_t GetFrameBytes( s16 width, s16 height )
    {
        return (GetLineBytes(width) * (height));
    }
    /* Please see man pages for details 
      

      
      
      
    */
    inline void SetTrimming( Port port, bool enable )
    {
        detail::SetTrimming(port, enable);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline bool IsTrimming( Port port )
    {
        return detail::IsTrimming(port);
    }
    /* Please see man pages for details 
      

                    
                    
                    
                    

      
      
      
      
      
      
    */
    inline void SetTrimmingParams( Port port, s16 xStart, s16 yStart, s16 xEnd, s16 yEnd )
    {
        detail::SetTrimmingParams(port, xStart, yStart, xEnd, yEnd);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline void GetTrimmingParams( s16* pXStart, s16* pYStart, s16* pXEnd, s16* pYEnd, Port port )
    {
        detail::GetTrimmingParams(pXStart, pYStart, pXEnd, pYEnd, port);
    }
    /* Please see man pages for details 
      

                    

      
      
      
      
      
      
    */
    inline void SetTrimmingParamsCenter( Port port, s16 trimWidth, s16 trimHeight, s16 camWidth, s16 camHeight )
    {
        detail::SetTrimmingParamsCenter(port, trimWidth, trimHeight, camWidth, camHeight);
    }


    /* Please see man pages for details 
      

                    
                    
                    
                    

      
      
      
      
      
    */
    inline nn::Result Activate( CameraSelect select )
    {
        return detail::Activate(select);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SwitchContext( CameraSelect select, Context next )
    {
        return detail::SwitchContext(select, next);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetExposure( CameraSelect select, s8 exposure )
    {
        return detail::SetExposure(select, exposure);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetWhiteBalance( CameraSelect select, WhiteBalance wb )
    {
        return detail::SetWhiteBalance(select, wb);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetSharpness( CameraSelect select, s8 sharpness )
    {
        return detail::SetSharpness(select, sharpness);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetAutoExposure( CameraSelect select, bool on )
    {
        return detail::SetAutoExposure(select, on);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result IsAutoExposure( bool* pOn, CameraSelect select )
    {
        return detail::IsAutoExposure(pOn, select);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetAutoWhiteBalance( CameraSelect select, bool on )
    {
        return detail::SetAutoWhiteBalance(select, on);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result IsAutoWhiteBalance( bool* pOn, CameraSelect select )
    {
        return detail::IsAutoWhiteBalance(pOn, select);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
    */
    inline nn::Result FlipImage( CameraSelect select, Flip flip, Context context = CONTEXT_BOTH )
    {
        return detail::FlipImage(select, flip, context);
    }
    /* Please see man pages for details 
      

      
      
      
      
                                  
                                  
                                  
                                  
                                  
      
                                  
                                  
                                  
      
                                  
                                  
                                  
                                  
      
                                  
                                  
                                  
      
      
      
      
      
    */
    inline nn::Result SetDetailSize( CameraSelect select, s16 width, s16 height, s16 cropX0 = 0, s16 cropY0 = 0, s16 cropX1 = 639, s16 cropY1 = 479, Context context = CONTEXT_BOTH )
    {
        return detail::SetDetailSize(select, width, height, cropX0, cropY0, cropX1, cropY1, context);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
    */
    inline nn::Result SetSize( CameraSelect select, Size size, Context context = CONTEXT_BOTH )
    {
        return detail::SetSize(select, size, context);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetFrameRate( CameraSelect select, FrameRate rate )
    {
        return detail::SetFrameRate(select, rate);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetPhotoMode( CameraSelect select, PhotoMode mode )
    {
        return detail::SetPhotoMode(select, mode);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
    */
    inline nn::Result SetEffect( CameraSelect select, Effect effect, Context context = CONTEXT_BOTH )
    {
        return detail::SetEffect(select, effect, context);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetContrast( CameraSelect select, Contrast contrast )
    {
        return detail::SetContrast(select, contrast);
    }
    /* Please see man pages for details 
      

                    
                    

      
      
      
      
      
      
    */
    inline nn::Result SetLensCorrection( CameraSelect select, LensCorrection correction )
    {
        return detail::SetLensCorrection(select, correction);
    }
    /* Please see man pages for details 
      
      
                    

      
      
      
      
      
      
      
    */
    inline nn::Result SetOutputFormat( CameraSelect select, OutputFormat format, Context context = CONTEXT_BOTH )
    {
        return detail::SetOutputFormat(select, format, context);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
      
      
    */
    inline nn::Result SetAutoExposureWindow( CameraSelect select, s16 startX, s16 startY, s16 width, s16 height )
    {
        return detail::SetAutoExposureWindow( select, startX, startY, width, height );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
      
      
    */
    inline nn::Result SetAutoWhiteBalanceWindow( CameraSelect select, s16 startX, s16 startY, s16 width, s16 height )
    {
        return detail::SetAutoWhiteBalanceWindow( select, startX, startY, width, height );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline nn::Result SetNoiseFilter( CameraSelect select, bool on )
    {
        return detail::SetNoiseFilter( select, on );
    }
    /* Please see man pages for details 
      
                    
                    
                    
                    
                    

      
      
      
      
      
      
    */
    inline nn::Result SynchronizeVsyncTiming( CameraSelect select1, CameraSelect select2 )
    {
        return detail::SynchronizeVsyncTiming( select1, select2 );
    }
    /* Please see man pages for details 
      
                    
                    

      
      
      
                              
                              
                              
                              
                              
      
    */
    inline void GetLatestVsyncTiming( nn::fnd::TimeSpan *pTime, Port port, size_t past = 1)
    {
        detail::GetLatestVsyncTiming( pTime, port, past );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline nn::Result SetBrightnessSynchronization( bool enable )
    {
        return detail::SetBrightnessSynchronization( enable );
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void GetStereoCameraCalibrationData( StereoCameraCalibrationData * pDst )
    {
        detail::GetStereoCameraCalibrationData( pDst );
    }
    /* Please see man pages for details 
      

      
      
                    
                    
    */
    inline f32 GetParallaxOnChart( const StereoCameraCalibrationData & cal )
    {
        return detail::GetParallaxOnChart( cal );
    }
    /* Please see man pages for details 
      

      
      
      
                    
                    
    */
    inline f32 GetParallax( const StereoCameraCalibrationData & cal, f32 distance )
    {
        return detail::GetParallax( cal, distance );
    }
    /* Please see man pages for details 
      

                    

      
      
      
      
      
    */
    inline void GetStereoCameraCalibrationMatrixOld(
                        nn::math::MTX34                   * pDst,            
                        const StereoCameraCalibrationData & cal,
                        const f32                         translationByPixel,
                        const bool                        isIncludeParallax = true )
    {
        detail::GetStereoCameraCalibrationMatrixOld( pDst, cal, translationByPixel, isIncludeParallax );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline void GetStereoCameraCalibrationMatrix(
                        nn::math::MTX34                   * pDst,            
                        const StereoCameraCalibrationData & cal,
                        const f32                         translationUnit,
                        const bool                        isIncludeParallax = true )
    {
        detail::GetStereoCameraCalibrationMatrix( pDst, cal, translationUnit, isIncludeParallax );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
      
      
      
      
      
    */
    inline void GetStereoCameraCalibrationMatrixEx(
                    nn::math::MTX34 * pDstR,
                    nn::math::MTX34 * pDstL,
                    f32             * pDstScale,
                    const StereoCameraCalibrationData & cal,
                    const f32       translationUnit,
                    const f32       parallax,
                    const s16       orgWidth,
                    const s16       orgHeight,
                    const s16       dstWidth,
                    const s16       dstHeight )
    {
        detail::GetStereoCameraCalibrationMatrixEx( pDstR, pDstL, pDstScale, cal, translationUnit, parallax, orgWidth, orgHeight, dstWidth, dstHeight );
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline nn::Result SetPackageParameterWithoutContext(const PackageParameterCameraSelect& param)
    {
        return detail::SetPackageParameterWithoutContext( param );
    }

    /* Please see man pages for details 
      
 
      
                    

      
      
      
      
      
    */
    inline nn::Result SetPackageParameterWithContext(const PackageParameterContext& param)
    {
        return detail::SetPackageParameterWithContext( param );
    }

    /* Please see man pages for details 
      

      
                    

      
      
      
      
      
    */
    inline nn::Result SetPackageParameterWithContext(const PackageParameterContextDetail& param)
    {
        return detail::SetPackageParameterWithContext( param );
    }

    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline nn::Result GetSuitableY2rStandardCoefficient(nn::y2r::CTR::StandardCoefficient* no)
    {
        return detail::GetSuitableY2rStandardCoefficient( no );
    }

    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline nn::Result PlayShutterSound( ShutterSoundType type )
    {
        return detail::PlayShutterSound( type );
    }

    // Function to notify the camera process of transitioning to another applet (internal use)
    inline nn::Result LeaveApplication()
    {
        return detail::LeaveApplication();
    }
    inline nn::Result ArriveApplication()
    {
        return detail::ArriveApplication();
    }
}
}
}

#endif  // ifndef NN_CAMERA_CTR_CAMERA_API_H_
