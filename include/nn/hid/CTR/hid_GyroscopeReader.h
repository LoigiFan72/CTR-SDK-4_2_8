/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_GyroscopeReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
 

 */

#ifndef NN_HID_CTR_GYROSCOPEREADER_H_
#define NN_HID_CTR_GYROSCOPEREADER_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_Result.h>
#include <nn/hid/CTR/hid_Api.h>
#include <nn/hid/CTR/hid_Gyroscope.h>
#include <nn/hid/CTR/hid_AccelerometerReader.h>
#include <nn/hid/CTR/hid_DeviceStatus.h>
#include <nn/util/util_SizedEnum.h>
#include <nn/util/util_NonCopyable.h>

namespace nn
{
namespace hid
{
namespace CTR
{

/* Please see man pages for details 
   
*/
enum ZeroDriftMode
{
    GYROSCOPE_ZERODRIFT_LOOSE,   //
    GYROSCOPE_ZERODRIFT_STANDARD,//
    GYROSCOPE_ZERODRIFT_TIGHT,   //
    GYROSCOPE_ZERODRIFT_NUM      //
};


/* Please see man pages for details 
    
*/
class GyroscopeReader: private nn::util::NonCopyable<GyroscopeReader>
{
public:


    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
    

                    

                    
                    
                    
                    
                    
    
                                                       
    

    */
    GyroscopeReader(AccelerometerReader* pAccelerometerReader = NULL, Gyroscope& gyroscope = GetGyroscope());

    /* Please see man pages for details 
    
    */

    ~GyroscopeReader();

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
      

      
      
      
      

    */
    void Read(GyroscopeStatus* pBufs, s32* pReadLen, s32 bufLen);

    /* Please see man pages for details 
      

      
      
      
      

    */
    bool ReadLatest(GyroscopeStatus* pBuf);

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
     

     
     */

    void Reset();

    /*  

*/

    /* Please see man pages for details 
     
     
     */


    /* Please see man pages for details 
     
     
     
     
     
     */
    void SetAngle(f32 ax, f32 ay, f32 az);

    /* Please see man pages for details 
     
     
     
     */
    void SetDirection(const Direction& direction);

    /* Please see man pages for details 
     
     
     
     
     
     */
    void SetAngleMagnification(f32 pitch, f32 yaw, f32 roll);

    /* Please see man pages for details 
     

                   

     
     
     */
    void SetDirectionMagnification(f32 magnification);

    /*  

*/

    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
     
     
     */
    void EnableZeroPlay();

    /* Please see man pages for details 
     
     
     */
    void DisableZeroPlay();

    /* Please see man pages for details 
     
     
     */
    bool IsEnableZeroPlay() const;

    /* Please see man pages for details 
     

                   

     

                   
     */
    f32 GetZeroPlayEffect() const;


    /* Please see man pages for details 
     

                   

                   

     
     
     */
    void SetZeroPlayParam(f32 radius);

    /* Please see man pages for details 
     

                   

     
     
     */
    void GetZeroPlayParam(f32& radius) const;

    /* Please see man pages for details 
     

                   

     
     */
    void ResetZeroPlayParam();

    /*  

*/


    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
     
     
     */
    void EnableZeroDrift();

    /* Please see man pages for details 
     
     
     */
    void DisableZeroDrift();

    /* Please see man pages for details 
     

                   

     
     
     
     */
    bool IsEnableZeroDrift() const;

    /* Please see man pages for details 
     

                   
                   

     
     */
    f32 GetZeroDriftEffect() const;

    /* Please see man pages for details 
     

                   

     
     */
    void ResetZeroDriftMode();

    /* Please see man pages for details 
     

                   

                   
                   

                   

                   

     
     
     */
    void SetZeroDriftMode(const ZeroDriftMode& mode);

    /* Please see man pages for details 
     
     
     
     */
    void GetZeroDriftMode(ZeroDriftMode& mode) const;

    /*  

*/


    /* Please see man pages for details 
     
     
     */

    /* Please see man pages for details 
     

                   

                   

                   

     
     */
    void EnableAccRevise();

    /* Please see man pages for details 
     
     
     */
    void DisableAccRevise();

    /* Please see man pages for details 
     

                   

     
     */
    bool IsEnableAccRevise() const;

    /* Please see man pages for details 
     
     

                   
     */
    f32 GetAccReviseEffect() const;


    /* Please see man pages for details 
     

                   

     
     

                                  

                                  
     
     */
    void SetAccReviseParam(f32 revisePower, f32 reviseRange);

    /* Please see man pages for details 
     
     
     
     
     */
    void GetAccReviseParam(f32& revisePower, f32& reviseRange) const;

    /* Please see man pages for details 
     

                   

     
     */
    void ResetAccReviseParam();

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
    static const s8 MAX_READ_NUM = 31;

private :

    void ReadLocal(GyroscopeStatus* pBufs, s32* pReadLen, s32 bufLen);
    void GetZeroDriftParam(f32& radius, s32& count, f32& power) const;
    void SetZeroDriftParam(f32 radius, s32 count, f32 power);
    f32 ReviseDirection_Acceleration(Direction& rev_dir, const nn::math::VEC3& acc);
    void CalculateGyroscopeAxisStatus(
        f32 *destSpeed,
        s32 *nearSamplingNum,
        f32 *zeroOffset,
        s32 srcSpeed,
        f32 speedScale,
        s32* oldValueArray);
    void CalculateDirection();
    void InitializeCalibrationData();

private :
    /* Maximum number for the drift correction count*/
    static const u32 GYROSCOPE_DRIFT_COUNT_MAX = 256; //Must be to the n power of 2


private :
    static const s32 GYROSCOPE_LOCAL_BUFFER_SIZE = 32;
    s32              m_GyroscopeLocalBufferSize;
    GyroscopeStatus m_GyroscopeStatusLocalBuffer[GYROSCOPE_LOCAL_BUFFER_SIZE];
    bool            m_IsFirstRead;
    util::SizedEnum1<ZeroDriftMode> m_ZeroDriftMode;
    NN_PADDING2;

    AccelerometerReader m_DefaultAccelerometerReader;

    GyroscopeStatus m_CurrentStatus;
    AccelerometerReader* m_pAccelerometerReader;

    nn::math::VEC3 m_SpeedOld;
    nn::math::VEC3 m_SpeedVector;
    nn::math::VEC3 m_SpeedScale;
    f32         m_DirectionMagnification;           // Magnification when calculating attitude

    f32         m_Period;           // Coefficient for calculations
    f32         m_FreqDegree;          // Coefficient for calculations
    f32         m_FreqRadian;          // Coefficient for calculations

    bool        m_EnableZeroPlay;       // Enable zero point play?
    bool        m_EnableZeroDrift;      // Use automatic zero point correction?
    bool        m_EnableAccRevise;      // Correct attitude using acceleration?
    bool        m_EnableRotate;

    f32         m_ZeroPlayRadius;   // Radius of zero point play (1 = 360deg/sec)
    f32         m_ZeroDriftRadius;  // Drift count permitted radius (1 = 360deg/sec)
    s32         m_ZeroDriftCount;      // Drift correction count
    f32         m_ZeroDriftPower;      // Drift correction power
    f32         m_AccRevisePower;      // Acceleration correction power
    f32         m_AccReviseRange;   // Acceleration correction enable radius

    f32         m_ZeroPlayEffect;        // Play circle inner status  0: outside - 1: center
    f32         m_ZeroDriftEffect;        // Drift correction count continuation state (0-1)
    f32         m_AccRevEffect;      // How much acceleration correction is applied

    nn::math::VEC3   m_CalibrationZero;  // Calibration value
    f64         m_CalibrationScale[3];  // Calibration value

    nn::math::VEC3   m_CountZero;        // Count value indicating zero point
    s32         m_CountIdx;         // Buffer index where the newest is stored
    s32         m_CountT[3][GYROSCOPE_DRIFT_COUNT_MAX];      // XYZ hardware value
    f32         m_DpsPitchMagnification;      // Scale ratio for calculating angular velocity in the pitch direction
    f32         m_DpsYawMagnification;        // Scale ratio for calculating angular velocity in the yaw direction
    f32         m_DpsRollMagnification;       // Scale ratio for calculating angular velocity in the roll direction
    NN_PADDING4;

    /*from Low*/
    Gyroscope&          m_Gyroscope;
    s32                 m_IndexOfRead;
    s64                 m_TickOfRead;

    /*rotate axis*/
    nn::math::MTX34     m_RotateMtx;

};

} // namespace CTR {
} // namespace hid {
} // namespace nn {

#endif // #ifndef NN_HID_CTR_GYROSCOPEREADER_H_
