/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     jpeg_MpEncoder.h

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

#ifndef NN_JPEG_JPEGMPENCODER_H_
#define NN_JPEG_JPEGMPENCODER_H_

#include <nn/util/util_NonCopyable.h>
#include <nn/jpeg/CTR/jpeg_MpTypes.h>
#include <string.h>

#ifdef __cplusplus

namespace nn {
namespace jpeg {
namespace CTR {

namespace detail {
    struct JpegMpEncoderWorkObj;
}

/* Please see man pages for details 
    
*/
class JpegMpEncoder : private nn::util::NonCopyable<JpegMpEncoder>
{
public:
    /* Please see man pages for details 
        

        
     */

    /* Please see man pages for details 
        

                    
     
        
                                
                                
                                
                                
     
        
                    
     */
    static size_t GetWorkBufferSize(u32 numImages = 0);

    /* Please see man pages for details 
        

                    
     */
    JpegMpEncoder() : m_Initialized(false) {}

    /* Please see man pages for details 
        

                    
     
                    
                    
     
        
                                        
                                        
                                        
     
        
                                        
     
        
                                        
                                        
     
        
                    
                    
     */
    bool Initialize(void* workBuffer, size_t workBufferSize, u32 numImages = 0);

    /* Please see man pages for details 
        
     
        
     */
    void Finalize() { m_Initialized = false; }

    /* Please see man pages for details 
        
                    
     */
    ~JpegMpEncoder() { Finalize(); }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe1() {}

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
     
                    
                    
     
                    
     
                    
                        
                        
                        
                    
     
                    
     
                    
                    
                    
                    
     
                    
                    
     
        
     
        

        
                                        

        
     */
    void SetThumbnailSize(u32 width, u32 height, PixelSampling dstPixelSampling = DEFAULT_THUMBNAIL_PIXEL_SAMPLING)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.thumbnailWidth    = width;
            m_TemporarySetting.thumbnailHeight   = height;
            m_TemporarySetting.thumbnailSampling = dstPixelSampling;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
     
                    
                    
                    
                    
                    
     
                    
                    
     
                    
     
                    
                        
                        
                    
     
        
                                        
                                        
     
        
     */
    void SetInputBufferWidth(u32 width)
    {
        if (m_Initialized)
        {
            if (width <= MAX_ENCODER_INPUT_BUFFER_WIDTH)
            {
                m_TemporarySetting.inputBufferWidth  = width;
            }
        }
    }

    /* Please see man pages for details 
        
     
                    
     
                    
     
                    
                    
                    
                    
     
                    
     
                    
                    
     
                    
                        
                        
                        
                        
                        
                        
                    
     
                    
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    
     
        
                                        
                                        
     
        
     */
    void SetOption(u32 option)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.option = option;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    u32 GetOption()
    {
        if (m_Initialized)
        {
            return m_TemporarySetting.option;
        }

        return JPEG_ENCODER_OPTION_NONE;
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
                                        
     
        
     */
    void SetDateTime(const char* pBuffer)
    {
        if (m_Initialized)
        {
            if (pBuffer)
            {
                memcpy(m_TemporarySetting.dateTimeBuffer, pBuffer, sizeof(m_TemporarySetting.dateTimeBuffer));
                m_TemporarySetting.dateTimeBuffer[sizeof(m_TemporarySetting.dateTimeBuffer) - 1] = '\0';
                m_TemporarySetting.isDateTimeSet = true;
            }
            else
            {
                m_TemporarySetting.isDateTimeSet = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
                    
     
        
                                        
     
        
     */
    static void GetDateTimeNow(char* pBuffer);

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
                                        
     
        
     */
    void SetSoftware(const char* pBuffer)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.pSoftware = pBuffer;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                        
                                   
                                   
                                   
                                  
                    
     
                    
                    
                    
                    
                    
                    
     
        
                                        
     
        
                                        
     
        
     */
    void SetUserMakerNote(const u8* pBuffer, size_t size);

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
                                        
     
        
     */
    void SetImageUid(const char* pBuffer)
    {
        if (m_Initialized)
        {
            if (pBuffer)
            {
                memcpy(m_TemporarySetting.imageUidBuffer, pBuffer, sizeof(m_TemporarySetting.imageUidBuffer));
                m_TemporarySetting.imageUidBuffer[sizeof(m_TemporarySetting.imageUidBuffer) - 1] = '\0';
                m_TemporarySetting.isImageUidSet = true;
            }
            else
            {
                m_TemporarySetting.isImageUidSet = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
     
        
     */
    void SetOrientation(u16 orientation)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.orientation = orientation;
            m_TemporarySetting.isOrientationSet = true;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearOrientation()
    {
        if (m_Initialized)
        {
            m_TemporarySetting.isOrientationSet = false;
        }
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe2() {}

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
                    
     
                    
                    
                    
     
                    
     
                    
                        
                        
                                   
                    
     
                    
                    
                    
                    
     
        
                                        
                                        
                                        
     
        
                                        
     
        
                                        
     
        
     */
    void SetMpTypeFlags(u32 flags = 0, u16 image1 = 0, u16 image2 = 0)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.isDependentParent = (flags & MP_TYPE_FLAG_DEPENDENT_IMAGE_PARENT) ? true : false;
            m_TemporarySetting.isDependentChild  = (flags & MP_TYPE_FLAG_DEPENDENT_IMAGE_CHILD)  ? true : false;
            m_TemporarySetting.isRepresentativeSet = true;
            m_TemporarySetting.isRepresentative  = (flags & MP_TYPE_FLAG_REPRESENTATIVE_IMAGE)   ? true : false;
            m_TemporarySetting.dependentImage1EntryNum = image1;
            m_TemporarySetting.dependentImage2EntryNum = image2;
        }
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe3() {}

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
     
        
     */
    void SetMpIndividualNum(u32 value)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.mpIndividualNum = value;
            m_TemporarySetting.mpAttribute.isMpIndividualNumValid = true;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpIndividualNum()
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.isMpIndividualNumValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
     
        
     */
    void SetMpPanOrientation(u32 value)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.panOrientation = value;
            m_TemporarySetting.mpAttribute.isPanOrientationValid = true;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpPanOrientation()
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.isPanOrientationValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpPanOverlapH(const Rational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.panOverlapH = *pValue;
                m_TemporarySetting.mpAttribute.isPanOverlapHValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isPanOverlapHValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpPanOverlapH() { SetMpPanOverlapH(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpPanOverlapV(const Rational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.panOverlapV = *pValue;
                m_TemporarySetting.mpAttribute.isPanOverlapVValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isPanOverlapVValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpPanOverlapV() { SetMpPanOverlapV(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
                    
     
                    
                    
                    
     
                    
                    
                    
     
        
     
        
     */
    void SetMpBaseViewpointNum(u32 value)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.baseViewpointNum = value;
            m_TemporarySetting.mpAttribute.isBaseViewpointNumValid = true;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpBaseViewpointNum()
    {
        if (m_Initialized)
        {
            m_TemporarySetting.mpAttribute.isBaseViewpointNumValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpConvergenceAngle(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.convergenceAngle = *pValue;
                m_TemporarySetting.mpAttribute.isConvergenceAngleValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isConvergenceAngleValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpConvergenceAngle() { SetMpConvergenceAngle(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpBaselineLength(const Rational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.baselineLength = *pValue;
                m_TemporarySetting.mpAttribute.isBaselineLengthValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isBaselineLengthValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpBaselineLength() { SetMpBaselineLength(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpVerticalDivergence(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.verticalDivergence = *pValue;
                m_TemporarySetting.mpAttribute.isVerticalDivergenceValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isVerticalDivergenceValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpVerticalDivergence() { SetMpVerticalDivergence(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpAxisDistanceX(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.axisDistanceX = *pValue;
                m_TemporarySetting.mpAttribute.isAxisDistanceXValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isAxisDistanceXValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpAxisDistanceX() { SetMpAxisDistanceX(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpAxisDistanceY(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.axisDistanceY = *pValue;
                m_TemporarySetting.mpAttribute.isAxisDistanceYValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isAxisDistanceYValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpAxisDistanceY() { SetMpAxisDistanceY(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpAxisDistanceZ(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.axisDistanceZ = *pValue;
                m_TemporarySetting.mpAttribute.isAxisDistanceZValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isAxisDistanceZValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpAxisDistanceZ() { SetMpAxisDistanceZ(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpYawAngle(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.yawAngle = *pValue;
                m_TemporarySetting.mpAttribute.isYawAngleValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isYawAngleValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpYawAngle() { SetMpYawAngle(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpPitchAngle(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.pitchAngle = *pValue;
                m_TemporarySetting.mpAttribute.isPitchAngleValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isPitchAngleValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpPitchAngle() { SetMpPitchAngle(NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetMpRollAngle(const Srational* pValue)
    {
        if (m_Initialized)
        {
            if (pValue)
            {
                m_TemporarySetting.mpAttribute.rollAngle = *pValue;
                m_TemporarySetting.mpAttribute.isRollAngleValid = true;
            }
            else
            {
                m_TemporarySetting.mpAttribute.isRollAngleValid = false;
            }
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearMpRollAngle() { SetMpRollAngle(NULL); }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
     
                    
                        
                        
                                   
                        
                                   
                        
                        
                                   
                    
     
                    
                    
     
        
                                        
     
        
     */
    static void InitializeGpsData(GpsData* pGps)
    {
        memset(pGps, 0, sizeof(*pGps));
        // GPS tag version is 2.2.
        pGps->versionId[0] = 2;
        pGps->versionId[1] = 2;
        pGps->isVersionIdValid = true;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
                    
     
        
     
        
                                        
                                        
     
        
     */
    static void SetGpsVersionId(GpsData* pGps, const u8* pVersionId)
    {
        NN_ASSERT(pGps);

        if (pVersionId)
        {
            memcpy(pGps->versionId, pVersionId, sizeof(pGps->versionId));
            pGps->isVersionIdValid = true;
        }
        else
        {
            pGps->isVersionIdValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsVersionId(GpsData* pGps) { SetGpsVersionId(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsLatitude(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->latitudeRef[0] = ref;
        pGps->latitudeRef[1] = '\0';

        if (pValue)
        {
            memcpy(pGps->latitude, pValue, sizeof(pGps->latitude));
            pGps->isLatitudeValid = true;
        }
        else
        {
            pGps->isLatitudeValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsLatitude(GpsData* pGps) { SetGpsLatitude(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsLongitude(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->longitudeRef[0] = ref;
        pGps->longitudeRef[1] = '\0';

        if (pValue)
        {
            memcpy(pGps->longitude, pValue, sizeof(pGps->longitude));
            pGps->isLongitudeValid = true;
        }
        else
        {
            pGps->isLongitudeValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsLongitude(GpsData* pGps) { SetGpsLongitude(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsAltitude(GpsData* pGps, u8 ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        if (pValue)
        {
            pGps->altitudeRef = ref;
            memcpy(&pGps->altitude, pValue, sizeof(pGps->altitude));
            pGps->isAltitudeRefValid = pGps->isAltitudeValid = true;
        }
        else
        {
            pGps->isAltitudeRefValid = pGps->isAltitudeValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsAltitude(GpsData* pGps) { SetGpsAltitude(pGps, 0, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
     */
    static void SetGpsTimeStamp(GpsData* pGps, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        if (pValue)
        {
            memcpy(pGps->timeStamp, pValue, sizeof(pGps->timeStamp));
            pGps->isTimeStampValid = true;
        }
        else
        {
            pGps->isTimeStampValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsTimeStamp(GpsData* pGps) { SetGpsTimeStamp(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
                                        
     
        
     */
    static void SetGpsSatellites(GpsData* pGps, const char* pSatellites)
    {
        NN_ASSERT(pGps);

        pGps->pSatellites = pSatellites;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsSatellites(GpsData* pGps) { SetGpsSatellites(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
     */
    static void SetGpsStatus(GpsData* pGps, char status)
    {
        NN_ASSERT(pGps);

        pGps->status[0] = status;
        pGps->status[1] = '\0';
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsStatus(GpsData* pGps) { SetGpsStatus(pGps, '\0'); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
     */
    static void SetGpsMeasureMode(GpsData* pGps, char measureMode)
    {
        NN_ASSERT(pGps);

        pGps->measureMode[0] = measureMode;
        pGps->measureMode[1] = '\0';
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsMeasureMode(GpsData* pGps) { SetGpsMeasureMode(pGps, '\0'); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
     */
    static void SetGpsDop(GpsData* pGps, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        if (pValue)
        {
            memcpy(&pGps->dop, pValue, sizeof(pGps->dop));
            pGps->isDopValid = true;
        }
        else
        {
            pGps->isDopValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDop(GpsData* pGps) { SetGpsDop(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsSpeed(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->speedRef[0] = ref;
        pGps->speedRef[1] = '\0';

        if (pValue)
        {
            memcpy(&pGps->speed, pValue, sizeof(pGps->speed));
            pGps->isSpeedValid = true;
        }
        else
        {
            pGps->isSpeedValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsSpeed(GpsData* pGps) { SetGpsSpeed(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsTrack(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->trackRef[0] = ref;
        pGps->trackRef[1] = '\0';

        if (pValue)
        {
            memcpy(&pGps->track, pValue, sizeof(pGps->track));
            pGps->isTrackValid = true;
        }
        else
        {
            pGps->isTrackValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsTrack(GpsData* pGps) { SetGpsTrack(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsImgDirection(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->imgDirectionRef[0] = ref;
        pGps->imgDirectionRef[1] = '\0';

        if (pValue)
        {
            memcpy(&pGps->imgDirection, pValue, sizeof(pGps->imgDirection));
            pGps->isImgDirectionValid = true;
        }
        else
        {
            pGps->isImgDirectionValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsImgDirection(GpsData* pGps) { SetGpsImgDirection(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
                                        
     
        
     */
    static void SetGpsMapDatum(GpsData* pGps, const char* pMapDatum)
    {
        NN_ASSERT(pGps);

        pGps->pMapDatum = pMapDatum;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsMapDatum(GpsData* pGps) { SetGpsMapDatum(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsDestLatitude(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->destLatitudeRef[0] = ref;
        pGps->destLatitudeRef[1] = '\0';

        if (pValue)
        {
            memcpy(pGps->destLatitude, pValue, sizeof(pGps->destLatitude));
            pGps->isDestLatitudeValid = true;
        }
        else
        {
            pGps->isDestLatitudeValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDestLatitude(GpsData* pGps) { SetGpsDestLatitude(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsDestLongitude(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->destLongitudeRef[0] = ref;
        pGps->destLongitudeRef[1] = '\0';

        if (pValue)
        {
            memcpy(pGps->destLongitude, pValue, sizeof(pGps->destLongitude));
            pGps->isDestLongitudeValid = true;
        }
        else
        {
            pGps->isDestLongitudeValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDestLongitude(GpsData* pGps) { SetGpsDestLongitude(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsDestBearing(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->destBearingRef[0] = ref;
        pGps->destBearingRef[1] = '\0';

        if (pValue)
        {
            memcpy(&pGps->destBearing, pValue, sizeof(pGps->destBearing));
            pGps->isDestBearingValid = true;
        }
        else
        {
            pGps->isDestBearingValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDestBearing(GpsData* pGps) { SetGpsDestBearing(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
     
        
                                        
     
        
     */
    static void SetGpsDestDistance(GpsData* pGps, char ref, const Rational* pValue)
    {
        NN_ASSERT(pGps);

        pGps->destDistanceRef[0] = ref;
        pGps->destDistanceRef[1] = '\0';

        if (pValue)
        {
            memcpy(&pGps->destDistance, pValue, sizeof(pGps->destDistance));
            pGps->isDestDistanceValid = true;
        }
        else
        {
            pGps->isDestDistanceValid = false;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDestDistance(GpsData* pGps) { SetGpsDestDistance(pGps, '\0', NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                            
     
        
                                            
     
        
     */
    static void SetGpsProcessingMethod(GpsData* pGps, const u8* pProcessingMethod, size_t processingMethodSize)
    {
        NN_ASSERT(pGps);

        if (pProcessingMethod && processingMethodSize)
        {
            pGps->pProcessingMethod    = pProcessingMethod;
            pGps->processingMethodSize = processingMethodSize;
        }
        else
        {
            pGps->pProcessingMethod    = NULL;
            pGps->processingMethodSize = 0;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsProcessingMethod(GpsData* pGps) { SetGpsProcessingMethod(pGps, NULL, 0); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                            
     
        
                                            
     
        
     */
    static void SetGpsAreaInformation(GpsData* pGps, const u8* pAreaInformation, size_t areaInformationSize)
    {
        NN_ASSERT(pGps);

        if (pAreaInformation && areaInformationSize)
        {
            pGps->pAreaInformation    = pAreaInformation;
            pGps->areaInformationSize = areaInformationSize;
        }
        else
        {
            pGps->pAreaInformation    = NULL;
            pGps->areaInformationSize = 0;
        }
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsAreaInformation(GpsData* pGps) { SetGpsAreaInformation(pGps, NULL, 0); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
                                        
                                        
     
        
     */
    static void SetGpsDateStamp(GpsData* pGps, const char* pDateStamp)
    {
        NN_ASSERT(pGps);

        pGps->pDateStamp = pDateStamp;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDateStamp(GpsData* pGps) { SetGpsDateStamp(pGps, NULL); }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     
        
     */
    static void SetGpsDifferential(GpsData* pGps, u16 differential)
    {
        NN_ASSERT(pGps);

        pGps->differential = differential;
        pGps->isDifferentialValid = true;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
     
        
     */
    static void ClearGpsDifferential(GpsData* pGps)
    {
        NN_ASSERT(pGps);

        pGps->isDifferentialValid = false;
    }

    
    /* Please see man pages for details 
        
     
                    
                    
     
                    
     
                    
     
                    
                    
                    
                    
                    
     
        
                                        
     
        
     */
    void SetGpsData(const GpsData* pGps)
    {
        if (m_Initialized)
        {
            m_TemporarySetting.pGpsData = pGps;
        }
    }

    /* Please see man pages for details 
        
     
        
     */
    void ClearGpsData() { SetGpsData(NULL); }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe4() {}

    /* Please see man pages for details 
        
     
                    
     
                    
                        
                        
                        
                    
     
        
     
        
                                        
     
        
                                        
     
        
     
        
     
        
                                        
     
        
     
        
     
        
     
        
                    
                    
     */
    size_t StartJpegEncoder(u8* dst,
                            size_t limit,
                            const void* src,
                            u32 width,
                            u32 height,
                            u32 quality,
                            PixelSampling dstPixelSampling,
                            PixelFormat srcPixelFormat,
                            bool addThumbnail);

    /* Please see man pages for details 
        
     
                    
                    
                    
                    
     
                    
                    
     
                    
     
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    
     
                    
     
                    
                        
                        
                        
                        
                        
                        
                    
     
                    
     
        
     
        
                                        
     
        
                                        
     
        
                                        
     
        
                                        
     
        
                                        
     
        
                                        
                                        
     
        
                                        
     
        
                                        
     
        
     
        
     
        
                    
                    
     */
    size_t StartMpEncoderLR(u8* dst,
                            size_t limit,
                            const void* srcL,
                            const void* srcR,
                            u32 width,
                            u32 height,
                            u32 quality,
                            PixelSampling dstPixelSampling,
                            PixelFormat srcPixelFormat,
                            bool addThumbnailL,
                            bool addThumbnailR);

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
                    
                    
     
                    
                    
                    
     
                    
                    
     
                    
                    
     
                    
                        
                                   
     
                                   
                                       
                                       
                                       
                                       
                                       
                                   
     
                    
                    
     
                    
     
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    
     
        
                                        
                                        
     
        
                                        
                                        
                                        
     
        
                                        
     
        
     
        
     
        
                                        
     
        
     
        
     
        
     
        
                                        
                                        
                                        
     
        
                                        
                                        
     
        
                                        
                                        
                                        
                                        
     
        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
     
        
                    
                    
     */
    size_t StartMpEncoderFirst(u8* dst,
                               size_t limit,
                               const void* src,
                               u32 width,
                               u32 height,
                               u32 quality,
                               PixelSampling dstPixelSampling,
                               PixelFormat srcPixelFormat,
                               bool addThumbnail,
                               u32 numImages = 2,
                               MpTypeCode typeCode = MP_TYPE_CODE_MULTI_VIEW_DISPARITY_IMAGE,
                               bool addImageUidList = false,
                               bool addTotalFrames = false);

    /* Please see man pages for details 
        
     
                    
     
                    
                    
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
                    
                    
                    
                    
     
                    
                    
     
                    
                        
                                   
     
                                    
                                        
                                        
                                        
                                        
                                        
                                    
     
                    
     
                    
     
                    
                    
     
                    
                        
                        
                            
                            
                            
                            
                            
                        
                        
                        
                            
                            
                        
                    
     
                    
                        
                        
     
        
                                        
     
        
     
        
     
        
                                        
     
        
     
        
     
        
     
        
                                        
                                        
     
        
                                        
                                        
                                        
                                        
     
        
                    
                    
     */
    size_t StartMpEncoderNext(const void* src,
                              u32 width,
                              u32 height,
                              u32 quality,
                              PixelSampling dstPixelSampling,
                              PixelFormat srcPixelFormat,
                              bool addThumbnail,
                              MpTypeCode typeCode = MP_TYPE_CODE_MULTI_VIEW_DISPARITY_IMAGE,
                              bool omitPixelDimensions = false);

    /* Please see man pages for details 
        
                    
     
                    
                    
                    
                    
     
                    
                    
     
                    
                    
                    
                    
     
                    
     
        
     
        
                    
                    
     */
    bool GetMpRegionsToBuildJpegData(MpRegionsToBuildJpegData* pBuffer);

    /* Please see man pages for details 
        
     
        
                    
                    
     */
    s32 GetLastError() const;

    /*  

*/

protected:
    detail::JpegMpEncoderWorkObj* m_pWork;
    bool    m_Initialized;
    bool    m_Padding[3];

    detail::JpegMpEncoderTemporarySettingObj m_TemporarySetting;
    void ClearTemporarySetting();

    void SetMakerNote(const u8* pBuffer, size_t size, u32 index);
};

} // namespace CTR {
} // namespace jpeg {
} // namespace nn {

#endif // __cplusplus

#endif // NN_JPEG_JPEGMPENCODER_H_
