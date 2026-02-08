/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     y2r_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46687 $
 *---------------------------------------------------------------------------*/

#ifndef NN_Y2R_CTR_Y2R_API_H_
#define NN_Y2R_CTR_Y2R_API_H_

/* Please see man pages for details 
    
*/

#include <nn/os.h>
#include <nn/y2r/CTR/y2r_Types.h>

#include <nn/y2r/CTR/y2r_Y2r.h>

namespace nn {
namespace y2r {
namespace CTR {

    namespace detail
    {
        bool InitializeBase(Handle* pSession, const char* name);
        bool PingProcess(u8* connectedNumber);
        void FinalizeBase(Handle* pSession);
        void SetInputFormat( InputFormat format );
        InputFormat GetInputFormat( void );
        void SetOutputFormat( OutputFormat format );
        OutputFormat GetOutputFormat( void );
        void SetRotation( Rotation rotation );
        Rotation GetRotation( void );
        void SetBlockAlignment( BlockAlignment align );
        BlockAlignment GetBlockAlignment( void );
        void SetSpacialDithering( bool enable );
        bool GetSpacialDithering( void );
        void SetTemporalDithering( bool enable );
        bool GetTemporalDithering( void );
        void SetTransferEndInterrupt( bool enable );
        bool GetTransferEndInterrupt( void );
        void GetTransferEndEvent( nn::os::Event* pEvent );
        void SetSendingY( u32 pSrc, size_t imageSize, s16 transferUnit, s16 transferStride );
        void SetSendingU( u32 pSrc, size_t imageSize, s16 transferUnit, s16 transferStride );
        void SetSendingV( u32 pSrc, size_t imageSize, s16 transferUnit, s16 transferStride );
        void SetSendingYuv( u32 pSrc, size_t imageSize, s16 transferUnit, s16 transferStride );
        bool IsFinishedSendingYuv( void );
        bool IsFinishedSendingY( void );
        bool IsFinishedSendingU( void );
        bool IsFinishedSendingV( void );
        void SetReceiving( u32 pDst, size_t imageSize, s16 transferUnit, s16 transferStride );
        bool IsFinishedReceiving( void );
        void SetInputLineWidth( s16 width );
        s16 GetInputLineWidth( void );
        void SetInputLines( s16 lines );
        s16 GetInputLines( void );
        size_t GetOutputFormatBytes( OutputFormat format );
        size_t GetOutputBlockSize( s16 lineWidth, OutputFormat format );
        size_t GetOutputImageSize( s16 lineWidth, s16 height, OutputFormat format );
        void SetCoefficientParams( CoefficientParams src );
        void GetCoefficientParams( CoefficientParams* pDst );
        void SetStandardCoefficient( StandardCoefficient no );
        void GetStandardCoefficientParams( CoefficientParams* pDst, StandardCoefficient no );
        void SetAlpha( s16 alpha );
        s16 GetAlpha( void );
        void SetDitheringWeightParams( const DitheringWeightParams & w );
        void GetDitheringWeightParams( DitheringWeightParams* pW );
        nn::Result StartConversion( void );
        void StopConversion( void );
        bool IsBusyConversion( void );

        // Batch parameter settings utility functions
        void SetPackageParameter(const PackageParameter& param);
        void GetPackageParameter(PackageParameter* pParam);
    }

    namespace
    {
        const char PORT_NAME_USER[]      = "y2r:u";
        const u16 OUTPUT_BUF_SIZE = 24*1024; // Output buffer size
        const u8 OUTPUT_LINES_NUM = 8; // Maximum number of lines to accumulate in the output buffer
    }

    /* Please see man pages for details 
    

                

    
    */
    bool Initialize();

    inline bool Initialize()  { return detail::InitializeBase(&detail::Y2r::s_Session, PORT_NAME_USER); }

    /* Please see man pages for details 
    

    
    */
    void Finalize();

    inline void Finalize()    { detail::FinalizeBase(&detail::Y2r::s_Session); }

    /* Please see man pages for details 
      

      
      
    */
    inline void SetInputFormat( InputFormat format )
    {
        detail::SetInputFormat(format);
    }
    /* Please see man pages for details 
      

      
    */
    inline InputFormat GetInputFormat( void )
    {
        return detail::GetInputFormat();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetOutputFormat( OutputFormat format )
    {
        detail::SetOutputFormat(format);
    }
    /* Please see man pages for details 
      

      
    */
    inline OutputFormat GetOutputFormat( void )
    {
        return detail::GetOutputFormat();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetRotation( Rotation rotation )
    {
        detail::SetRotation(rotation);
    }
    /* Please see man pages for details 
      

      
    */
    inline Rotation GetRotation( void )
    {
        return detail::GetRotation();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetBlockAlignment( BlockAlignment align )
    {
        detail::SetBlockAlignment(align);
    }
    /* Please see man pages for details 
      

      
    */
    inline BlockAlignment GetBlockAlignment( void )
    {
        return detail::GetBlockAlignment();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetSpacialDithering( bool enable )
    {
        detail::SetSpacialDithering(enable);
    }
    /* Please see man pages for details 
      

      
    */
    inline bool GetSpacialDithering( void )
    {
        return detail::GetSpacialDithering();
    }
    /* Please see man pages for details 
      
                    

      
      
    */
    inline void SetTemporalDithering( bool enable )
    {
        detail::SetTemporalDithering(enable);
    }
    /* Please see man pages for details 
      
                    

      
    */
    inline bool GetTemporalDithering( void )
    {
        return detail::GetTemporalDithering();
    }
    /* Please see man pages for details 
      
                    

      
      
    */
    inline void SetTransferEndInterrupt( bool enable )
    {
        detail::SetTransferEndInterrupt(enable);
    }
    /* Please see man pages for details 
      

      
    */
    inline bool GetTransferEndInterrupt( void )
    {
        return detail::GetTransferEndInterrupt();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void GetTransferEndEvent( nn::os::Event* pEvent )
    {
        detail::GetTransferEndEvent(pEvent);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
      
    */
    inline void SetSendingY( const void* pSrc, size_t imageSize, s16 transferUnit, s16 transferStride = 0 )
    {
        detail::SetSendingY(reinterpret_cast<u32>(pSrc), imageSize, transferUnit, transferStride);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline void SetSendingU( const void* pSrc, size_t imageSize, s16 transferUnit, s16 transferStride = 0 )
    {
        detail::SetSendingU(reinterpret_cast<u32>(pSrc), imageSize, transferUnit, transferStride);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline void SetSendingV( const void* pSrc, size_t imageSize, s16 transferUnit, s16 transferStride = 0 )
    {
        detail::SetSendingV(reinterpret_cast<u32>(pSrc), imageSize, transferUnit, transferStride);
    }
    /* Please see man pages for details 
      

      
      
      
      
      
    */
    inline void SetSendingYuv( const void* pSrc, size_t imageSize, s16 transferUnit, s16 transferStride = 0 )
    {
        detail::SetSendingYuv(reinterpret_cast<u32>(pSrc), imageSize, transferUnit, transferStride);
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsFinishedSendingYuv( void )
    {
        return detail::IsFinishedSendingYuv();
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsFinishedSendingY( void )
    {
        return detail::IsFinishedSendingY();
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsFinishedSendingU( void )
    {
        return detail::IsFinishedSendingU();
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsFinishedSendingV( void )
    {
        return detail::IsFinishedSendingV();
    }
    /* Please see man pages for details 
      

      
      
      
      
                                    
      
    */
    inline void SetReceiving( void* pDst, size_t imageSize, s16 transferUnit, s16 transferStride = 0 )
    {
        detail::SetReceiving(reinterpret_cast<u32>(pDst), imageSize, transferUnit, transferStride);
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsFinishedReceiving( void )
    {
        return detail::IsFinishedReceiving();
    }
    /* Please see man pages for details 
      

                    

      
      
    */
    inline void SetInputLineWidth( s16 width )
    {
        detail::SetInputLineWidth(width);
    }
    /* Please see man pages for details 
      

      
    */
    inline s16 GetInputLineWidth( void )
    {
        return detail::GetInputLineWidth();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetInputLines( s16 lines )
    {
        detail::SetInputLines(lines);
    }
    /* Please see man pages for details 
      

      
    */
    inline s16 GetInputLines( void )
    {
        return detail::GetInputLines();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline size_t GetOutputFormatBytes( OutputFormat format )
    {
        return detail::GetOutputFormatBytes(format);
    }
    /* Please see man pages for details 
      

      
      
      
    */
    inline size_t GetOutputBlockSize( s16 lineWidth, OutputFormat format )
    {
        return detail::GetOutputBlockSize(lineWidth, format);
    }
    /* Please see man pages for details 
      

      
      
      
      
    */
    inline size_t GetOutputImageSize( s16 lineWidth, s16 height, OutputFormat format )
    {
        return detail::GetOutputImageSize(lineWidth, height, format);
    }
    /* Please see man pages for details 
      

                    

      
      
    */
    inline void SetCoefficientParams( CoefficientParams src )
    {
        detail::SetCoefficientParams(src);
    }
    /* Please see man pages for details 
      

                    

      
      
    */
    inline void GetCoefficientParams( CoefficientParams* pDst )
    {
        detail::GetCoefficientParams(pDst);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetStandardCoefficient( StandardCoefficient no )
    {
        detail::SetStandardCoefficient(no);
    }
    /* Please see man pages for details 
      

                    

      
      
      
    */
    inline void GetStandardCoefficientParams( CoefficientParams* pDst, StandardCoefficient no )
    {
        detail::GetStandardCoefficientParams(pDst, no);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetAlpha( s16 alpha )
    {
        detail::SetAlpha(alpha);
    }
    /* Please see man pages for details 
      

      
    */
    inline s16 GetAlpha( void )
    {
        return detail::GetAlpha();
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void SetDitheringWeightParams( const DitheringWeightParams & w )
    {
        detail::SetDitheringWeightParams(w);
    }
    /* Please see man pages for details 
      

      
      
    */
    inline void GetDitheringWeightParams( DitheringWeightParams* pW )
    {
        detail::GetDitheringWeightParams(pW);
    }
    /* Please see man pages for details 
      

      
      
      
    */
    inline nn::Result StartConversion( void )
    {
        return detail::StartConversion();
    }
    /* Please see man pages for details 
      

      
    */
    inline void StopConversion( void )
    {
        detail::StopConversion();
    }
    /* Please see man pages for details 
      

      
    */
    inline bool IsBusyConversion( void )
    {
        return detail::IsBusyConversion();
    }

    /* Please see man pages for details 
      

      
      
    */
    inline void SetPackageParameter(const PackageParameter& param)
    {
        return detail::SetPackageParameter( param );
    }

    /* Please see man pages for details 
      

      
      
    */
    inline void GetPackageParameter(PackageParameter* pParam)
    {
        return detail::GetPackageParameter( pParam );
    }
}
}
}

#endif  // ifndef NN_Y2R_CTR_Y2R_API_H_
