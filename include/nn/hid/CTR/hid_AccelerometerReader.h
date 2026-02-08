/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_AccelerometerReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46940 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    

*/
#ifndef NN_HID_CTR_HID_ACCELEROMETERREADER_H_
#define NN_HID_CTR_HID_ACCELEROMETERREADER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_Result.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_Accelerometer.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_SizedEnum.h>
#include <nn/util/util_NonCopyable.h>
#include <nn/math.h>

namespace nn {
namespace hid {
namespace CTR {
/* Please see man pages for details 
  

*/
const s16   MAX_OF_ACCELEROMETER_VALUE                      = 930;

/* Please see man pages for details 
  

*/
const s16   ACCELEROMETER_VALUE_PER_1G                      = 512;
const f32   ACCELERATION_SCALE_PER_1G                       = 1.f / ACCELEROMETER_VALUE_PER_1G;

/* Please see man pages for details 
  

*/
const s16   MAX_OF_ACCELEROMETER_PLAY                       = MAX_OF_ACCELEROMETER_VALUE * 2;

const s16   ACCELEROMETER_SENSITIVITY_SCALE_SHIFT           = 7;

/* Please see man pages for details 
  

*/
const s16   MAX_OF_ACCELEROMETER_SENSITIVITY                = 128; // 1 << ACCELEROMETER_SENSITIVITY_SCALE_SHIFT


/* Please see man pages for details 
    


*/
class AccelerometerReader : private nn::util::NonCopyable<AccelerometerReader>
{
public:

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
    

                    

    

    */
    AccelerometerReader(Accelerometer& accelerometer = GetAccelerometer( ));

    /* Please see man pages for details 
    

    */
    ~AccelerometerReader( );

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
      

      
      
      
      

    */
    void Read(AccelerometerStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

      

      
      
      
      

    */
    bool ReadLatest(AccelerometerStatus* pBuf);

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
        
        
        
        

    */
    void GetSensitivity(s16* pPlay, s16* pSensitivity) const;

    /* Please see man pages for details 
        

                    

        
        
        

    */
    void SetSensitivity(s16 play, s16 sensitivity);

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
      

                    

                    

                    
     */
    void EnableAxisRotation();


    /* Please see man pages for details 
      
     */
    void DisableAxisRotation();


    /* Please see man pages for details 
      

      
    */
    bool IsEnableAxisRotation() const;


    /* Please see man pages for details 
      
      
     */
    void SetAxisRotationMatrix(const nn::math::MTX34& mtx);

    /* Please see man pages for details 
    

      

                    

      
     */
    nn::math::MTX34 GetAxisRotationMatrix() const;

    /* Please see man pages for details 
    

      
      

      
     */
    void GetAxisRotationMatrix(nn::math::MTX34* pMtx) const;


    /* Please see man pages for details 
      

                    

                    
     */
    void ResetAxisRotationMatrix();

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
      

                    

                    

                    
     */

    void EnableOffset();

    /* Please see man pages for details 
      

                    
     */
    void DisableOffset();

    /* Please see man pages for details 
      

      
     */
    bool IsEnableOffset() const;


    /* Please see man pages for details 
      

                    

                    

      
      
      
     */
    void SetOffset(s16 x, s16 y,s16 z);


    /* Please see man pages for details 
      

                    

      
     */

    void SetOffsetFromBaseStatus(AccelerometerStatus baseAccelerometerStatus);

    /* Please see man pages for details 
      

      
      
      
     */
    void GetOffset(s16* pX, s16* pY, s16*pZ) const;

    /* Please see man pages for details 
      

                    
     */
    void ResetOffset();

    /*  

*/


    /* Please see man pages for details 
     
     
     */
    /* Please see man pages for details 
      

      
      
      
      
                                        
      

    */
    void ConvertToAcceleration(AccelerationFloat* pAcceleration, s32 bufLen, const AccelerometerStatus* pSamplingData, s32 samplingLen = -1);

    /*  

*/


    /* Please see man pages for details 
      
    */
    static const s8 MAX_READ_NUM = 7;

private:
    void Transform(AccelerometerStatus* pAccStatus);

protected:
    Accelerometer&                              m_Accelerometer;
    s16                                         m_Play;
    s16                                         m_Sensitivity;

    AccelerometerStatus                         m_LatestCalculatedStatus;
    AccelerometerStatus                         m_OffsetAccStatus;
    NN_PADDING4;

    nn::math::MTX34                             m_RotateMtx;
    bool                                        m_EnableOffset;
    bool                                        m_EnableRotate;
    NN_PADDING2;
    s32                                         m_IndexOfRead;
    s64                                         m_TickOfRead;
};



// inline implementation
inline void AccelerometerReader::SetSensitivity(s16 play, s16 sensitivity)
{
    NN_TASSERT_(0 <= play && MAX_OF_ACCELEROMETER_PLAY >= play && 0 <= sensitivity && MAX_OF_ACCELEROMETER_SENSITIVITY >= sensitivity);
    m_Play = play;
    m_Sensitivity = sensitivity;
}

inline void AccelerometerReader::GetSensitivity(s16* pPlay, s16* pSensitivity) const
{
    *pPlay = m_Play;
    *pSensitivity = m_Sensitivity;
}

} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif  // #ifndef NN_HID_CTR_HID_ACCELEROMETERREADER_H_
