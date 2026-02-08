/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mic_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIC_CTR_MIC_API_H_
#define NN_MIC_CTR_MIC_API_H_

/* Please see man pages for details 
    
*/

#include <nn/os.h>
#include <nn/mic/CTR/mic_Types.h>

#define NN_MIC_AMP_GAIN_MAX              119   // 10.5.0dB
#define NN_MIC_AMP_GAIN_MIN                0   // 70.0.0dB
#define NN_MIC_BUFFER_ALIGNMENT_SIZE    4096
#define NN_MIC_BUFFER_ALIGNMENT_ADDRESS 4096

namespace nn {
namespace mic {
namespace CTR {

    /* Please see man pages for details 
    
    */
    const u8 AMP_GAIN_MAX = NN_MIC_AMP_GAIN_MAX;

    /* Please see man pages for details 
    
    */
    const u8 AMP_GAIN_MIN = NN_MIC_AMP_GAIN_MIN;

    /* Please see man pages for details 
    
    */
    const s32 BUFFER_ALIGNMENT_ADDRESS = NN_MIC_BUFFER_ALIGNMENT_ADDRESS;
    
    /* Please see man pages for details 
    
    */
    const s32 BUFFER_ALIGNMENT_SIZE = NN_MIC_BUFFER_ALIGNMENT_SIZE;
    
    /* Please see man pages for details 
    

    
    
    
    
                                          
    */
    Result Initialize();

    /* Please see man pages for details 
    

                
                

    
    
    
    */
    Result Finalize();

    /* Please see man pages for details 
      

                    
                    

                    
                    

                    
                    
                    
                    

      
      
      
      
      
      
      
      
      
    */
    Result SetBuffer( void* address, size_t size ); 

    /* Please see man pages for details 
      

                    

      
      
      
      
    */
    Result ResetBuffer( );

    /* Please see man pages for details 
      

                    
                    

      
      
      
      
    */
    Result GetSamplingBufferSize(size_t* pSize);

    /* Please see man pages for details 
      

                    

      
      
      
      
                              
      
                              
                              
                              

      
      
      
      
      
      
    */
    Result StartSampling( SamplingType type, SamplingRate rate, s32 offset, size_t size, bool loop );

    /* Please see man pages for details 
      

      
      
    */
    Result StopSampling( void );

    /* Please see man pages for details 
      

                    
                    

                    
                    

      

      
      
      
    */
    Result AdjustSampling( SamplingRate rate );
    
    /* Please see man pages for details 
      

      

      
      
    */
    Result IsSampling( bool* pSampling );
    
    /* Please see man pages for details 
      

      

      
      
    */
    Result GetLastSamplingAddress( uptr* pAddress );

    /* Please see man pages for details 
      

                    
                    
                    

                    
                    

      

      
      
    */
    Result GetBufferFullEvent( nn::os::Event* pEvent );

    /* Please see man pages for details 
      

                    
                    

      

      
      
    */
    Result SetAmpGain( u8 gain );

    /* Please see man pages for details 
      

      

      
      
    */
    Result GetAmpGain( u8* pGain );
    
    /* Please see man pages for details 
      

                    
                    

                    
                    
                    
                    

      

      
      
    */
    Result SetAmp( bool enable );
    
    /* Please see man pages for details 
      

      

      
      
    */
    Result GetAmp( bool* pEnable );

    /* Please see man pages for details 
      
                    

      
      
      
      

      
      
      
    */
    bool GetForbiddenArea( s32* upper, s32* lower, SamplingType type, u8 gain );
    
    /* Please see man pages for details 
      
      
                    
                    
                    

      

      
      
    */
    Result SetLowPassFilter( bool enable );

    /* Please see man pages for details 
      

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

      

      
      
    */
    Result SetClamp( bool enable );
    
    /* Please see man pages for details 
      

      

      
      
    */
    Result GetClamp( bool* pEnable );

}
}
}

#endif  // ifndef NN_MIC_CTR_MIC_API_H_
