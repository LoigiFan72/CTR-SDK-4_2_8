/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     jpeg_MpDecoder.h

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

#ifndef NN_JPEG_JPEGMPDECODER_H_
#define NN_JPEG_JPEGMPDECODER_H_

#include <nn/util/util_NonCopyable.h>
#include <nn/jpeg/CTR/jpeg_MpTypes.h>

#ifdef __cplusplus

namespace nn {
namespace jpeg {
namespace CTR {

namespace detail {
    struct JpegMpDecoderWorkObj;
}

/* Please see man pages for details 
    
*/
class JpegMpDecoder : private nn::util::NonCopyable<JpegMpDecoder>
{
public:
    /* Please see man pages for details 
        

        
     */

    /* Please see man pages for details 
        
     
                    
     
        
     */
    static size_t GetWorkBufferSize();

    /* Please see man pages for details 
        

                    
     */
    JpegMpDecoder() : m_Initialized(false) {}

    /* Please see man pages for details 
        

                    
     
                    
                    
     
        
                                        
                                        
                                        
     
        
                                        
     
        
                    
                    
     */
    bool Initialize(void* workBuffer, size_t workBufferSize);

    /* Please see man pages for details 
        
     
        
     */
    void Finalize() { m_Initialized = false; }

    /* Please see man pages for details 
        
                    
     */
    ~JpegMpDecoder() { Finalize(); }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
     
                    
                    
     
        
                                        
                                        
                                        
                                        
     
        
                                        
                                        
     
        
                                        
                                        
                                        
                                        
     
        
                    
     */
    static size_t GetDstBufferSize(u32 maxWidth,
                                   u32 maxHeight,
                                   PixelFormat dstPixelFormat)
    {
        size_t size = 0;
        u64 size64;

        switch (dstPixelFormat)
        {
        case PIXEL_FORMAT_YUYV8:
            // Rounds up to a multiple of width x 2.
            maxWidth = (maxWidth + 1) & ~1;
            size = 2;
            break;

        case PIXEL_FORMAT_CTR_RGB565:
            size = 2;
            break;

        case PIXEL_FORMAT_CTR_RGB565_BLOCK8:
            // Rounds up to a multiple of width and height x 8.
            maxWidth  = (maxWidth  + 7) & ~7;
            maxHeight = (maxHeight + 7) & ~7;
            size = 2;
            break;

        case PIXEL_FORMAT_RGB8:
        case PIXEL_FORMAT_BGR8:
            size = 3;
            break;

        case PIXEL_FORMAT_CTR_RGB8_BLOCK8:
            maxWidth  = (maxWidth  + 7) & ~7;
            maxHeight = (maxHeight + 7) & ~7;
            size = 3;
            break;

        case PIXEL_FORMAT_RGBA8:
        case PIXEL_FORMAT_ABGR8:
            size = 4;
            break;

        case PIXEL_FORMAT_CTR_RGBA8_BLOCK8:
            maxWidth  = (maxWidth  + 7) & ~7;
            maxHeight = (maxHeight + 7) & ~7;
            size = 4;
            break;

        default:
            // unexpected format
            size = 0;
            break;
        }

        size64 = static_cast<u64>(size) * maxWidth * maxHeight;
        size = static_cast<size_t>(size64);

        if (size != size64)
        {
            size = 0;
        }

        return size;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
     
                    
                    
                    
                    
                    
     
                    
                    
                    
     
                    
                    
                    
     
        
                                        
                                        
     
        
     */
    void SetOutputBufferWidth(u32 width)
    {
        if (m_Initialized)
        {
            if (width <= MAX_DECODER_OUTPUT_BUFFER_WIDTH)
            {
                m_TemporarySetting.outputBufferWidth  = width;
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

        return JPEG_DECODER_OPTION_NONE;
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe1() {}

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                        
                        
                        
                    
     
                    
                    
     
        
                                        
                                        
                                        
     
        
                                        
     
        
     
        
     
        
                                        
                                        
     
        
                                        
                                        
     
        
     
        
                                        
     
        
                    
                    
     */
    size_t StartJpegDecoder(void* dst,
                            size_t dstSize,
                            const u8* src,
                            size_t srcSize,
                            u32 maxWidth,
                            u32 maxHeight,
                            PixelFormat dstPixelFormat,
                            bool decodeThumbnail);

    /* Please see man pages for details 
        
     
                    
                    
     
                    
     
                    
                    
     
                    
                        
                        
                        
                        
                    
     
                    
                    
                    
     
                    
                    
                    
                    
     
                    
                    
     
        
                                        
     
        
                                        
                                        
                                        
                                        
                                        
     
        
     
        
     
        
                                        
                                        
                                        
     
        
                                        
                                        
                                        
     
        
     
        
                                        
     
        
                                        
                                        
     
        
                    
                    
    */
    size_t StartJpegDecoderShrink(void* dst,
                                  size_t dstSize,
                                  const u8* src,
                                  size_t srcSize,
                                  u32 maxWidth,
                                  u32 maxHeight,
                                  PixelFormat dstPixelFormat,
                                  bool decodeThumbnail,
                                  u32 shrinkLevel);

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
     
                    
                    
                    
                    
                    
     
                    
                    
                    
     
                    
                    
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    
     
                    
     
                    
                        
                        
                        
                    
     
                    
     
        
                                        
     
        
                                        
     
        
                                        
                                        
     
        
     
        
     
        
                                        
                                        
     
        
                                        
                                        
     
        
     
        
                    
                    
                    
     */
    size_t StartMpDecoderLR(void* dstL,
                            void* dstR,
                            size_t dstSize,
                            const u8* src,
                            size_t srcSize,
                            u32 maxWidth,
                            u32 maxHeight,
                            PixelFormat dstPixelFormat);

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
     
                    
                    
     
                    
                    
     
                    
                    
                    
     
                    
                    
     
                      
                      
                      
                         
     
                    
                    
     
                    
     
                    
     
        
     */
    void StopDecoder();

    /* Please see man pages for details 
        

                    
     
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                    
     
                    
     
                    
     
        
     
        
     
        
                                        
                                        
     
        
                    
                    
                    
     */
    bool ExtractExif(const u8* src, size_t srcSize, bool extractThumbnail);

    /* Please see man pages for details 
        
     
                    
                    
                    
                    
     
                    
                    
                    
     
                    
                    
                    
     
                    
                    
                    
                    
     
        
     
        
     
        
     
        
                    
                    
    */
    bool GetMpRegionsToBuildJpegData(MpRegionsToBuildJpegData* pBuffer, const u8* src, size_t srcSize);

    /* Please see man pages for details 
        
     
                    
     
                    
                        
                        
                        
                        
                        
                        
                        
                    
     
        
                    
                    
     */
    s32 GetLastError() const;

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
     
     
     
     */
    static void DoNotCallMe2() {}

    /* Please see man pages for details 
        
     
                    
     
        
     */
    u32 GetLastWidth() const;

    /* Please see man pages for details 
        
     
                    
     
        
     */
    u32 GetLastHeight() const;

    /* Please see man pages for details 
        
     
                    

        
                    
                    
                    
                    
     */
    u32 GetLastOutputBufferWidth() const;

    /* Please see man pages for details 
        
     
                    
     
        
                    
                    
     */
    u32 GetLastOutputBufferHeight() const;

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
     
        
                                        
                                        
     
        
                    
     */
    size_t GetLastDateTime(char* pBuffer) const;

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
                    
     
                    
     
        
                    
     */
    const char* GetLastDateTimePointer() const;

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
     
        
                    
                    
     */
    const char* GetLastSoftwarePointer() const;

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
     
        
                    
                    
     */
    size_t GetLastSoftwareLength() const;

    /* Please see man pages for details 
        
                    
     
                    
                    
     
                    
                    
     
                    
     
        
                    
     */
    const u8* GetLastUserMakerNotePointer() const;

    /* Please see man pages for details 
        
                    
     
                    
                    
     
                    
                    
     
                    
     
        
                    
     */
    size_t GetLastUserMakerNoteSize() const;

    /* Please see man pages for details 
        
                    
     
                    
                    
     
                    
     
        
                                        
     
        
                    
     */
    bool GetLastTwlPhotoMakerNote(u8* pBuffer) const;

    /* Please see man pages for details 
        
                    
     
                    
                    
     
                    
                    
     
                    
     
                    
                    
     
        
                    
     */
    const u8* GetLastTwlUserMakerNotePointer() const;

    /* Please see man pages for details 
        
                    
     
                    
                    
     
                    
     
                    
     
                    
                    
     
        
                    
     */
    size_t GetLastTwlUserMakerNoteSize() const;

    /* Please see man pages for details 
        
     
                    
                    
                    
     
                    
                    
     
        
                                        
                                        
     
        
                    
     */
    size_t GetLastImageUid(char* pBuffer);

    /* Please see man pages for details 
        
     
                    
                    
                    
     
        
     
        
                    
     */
    bool GetLastOrientation(u16* pBuffer);

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
                    
                    
     
        
                                        
                                        
     
        
                                        
     
        
     
        
                    
                    
     */
    bool GetMpIndex(MpIndex* pIndex, const u8* src, size_t srcSize);

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpNumberOfImages(u32* pNumber, const MpIndex* pIndex)
    {
        NN_ASSERT(pNumber);
        NN_ASSERT(pIndex);

        if (pIndex->isNumberOfImagesValid)
        {
            *pNumber = pIndex->numberOfImages;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
                    
                    
                    
    
        
                                        
     
        
                    
     */
    static size_t GetMpImageUidListSize(const MpIndex* pIndex)
    {
        NN_ASSERT(pIndex);

        if (pIndex->imageUidListSize && pIndex->offsetToImageUidList)
        {
            return pIndex->imageUidListSize;
        }

        return 0;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
                    
                    
     
        
                                        
     
        
                    
     */
    static size_t GetMpImageUidListOffset(const MpIndex* pIndex)
    {
        NN_ASSERT(pIndex);

        if (pIndex->imageUidListSize && pIndex->offsetToImageUidList)
        {
            return pIndex->offsetToImageUidList;
        }

        return 0;
    }

    /* Please see man pages for details 
        
     
                    
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpTotalFrames(u32* pFrames, const MpIndex* pIndex)
    {
        NN_ASSERT(pFrames);
        NN_ASSERT(pIndex);

        if (pIndex->isTotalFramesValid)
        {
            *pFrames = pIndex->totalFrames;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
                    
                    
                    
     
                    
     
        
                                        
                                        
     
        
                                        
     
        
     
        
                    
                    
     */
    static bool GetMpEntry(MpEntry* pEntry, const MpIndex* pIndex, u32 index);

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static u32 GetMpImageType(const MpEntry* pEntry)
    {
        NN_ASSERT(pEntry);
        return pEntry->type;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
                                        
     
        
     */
    static size_t GetMpImageSize(const MpEntry* pEntry)
    {
        NN_ASSERT(pEntry);
        return pEntry->imageDataSize;
    }

    /* Please see man pages for details 
        
     
                    
                    
     
        
                                        
     
        
                    
                    
     */
    static size_t GetMpImageOffset(const MpEntry* pEntry)
    {
        NN_ASSERT(pEntry);
        return pEntry->offsetToImageData;
    }

    /* Please see man pages for details 
        
    
        
                                        
     
        
     */
    static u16 GetMpDependentImage1EntryNum(const MpEntry* pEntry)
    {
        NN_ASSERT(pEntry);
        return pEntry->dependentImage1EntryNum;
    }

    /* Please see man pages for details 
        
    
        
                                        
     
        
     */
    static u16 GetMpDependentImage2EntryNum(const MpEntry* pEntry)
    {
        NN_ASSERT(pEntry);
        return pEntry->dependentImage2EntryNum;
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
                    
                    
                    
     
                    
                    
     
                    
                    
                    
                    
     
        
                                        
                                        
     
        
     
        
     
        
                    
                    
     */
    bool GetMpAttribute(MpAttribute* pAttr, const u8* src, size_t srcSize);

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpIndividualNum(u32* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isMpIndividualNumValid)
        {
            *pBuffer = pAttr->mpIndividualNum;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpPanOrientation(u32* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isPanOrientationValid)
        {
            *pBuffer = pAttr->panOrientation;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpPanOverlapH(Rational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isPanOverlapHValid)
        {
            *pBuffer = pAttr->panOverlapH;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpPanOverlapV(Rational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isPanOverlapVValid)
        {
            *pBuffer = pAttr->panOverlapV;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpBaseViewpointNum(u32* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isBaseViewpointNumValid)
        {
            *pBuffer = pAttr->baseViewpointNum;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpConvergenceAngle(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isConvergenceAngleValid)
        {
            *pBuffer = pAttr->convergenceAngle;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpBaselineLength(Rational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isBaselineLengthValid)
        {
            *pBuffer = pAttr->baselineLength;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpVerticalDivergence(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isVerticalDivergenceValid)
        {
            *pBuffer = pAttr->verticalDivergence;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpAxisDistanceX(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isAxisDistanceXValid)
        {
            *pBuffer = pAttr->axisDistanceX;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpAxisDistanceY(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isAxisDistanceYValid)
        {
            *pBuffer = pAttr->axisDistanceY;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpAxisDistanceZ(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isAxisDistanceZValid)
        {
            *pBuffer = pAttr->axisDistanceZ;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpYawAngle(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isYawAngleValid)
        {
            *pBuffer = pAttr->yawAngle;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpPitchAngle(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isPitchAngleValid)
        {
            *pBuffer = pAttr->pitchAngle;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetMpRollAngle(Srational* pBuffer, const MpAttribute* pAttr)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pAttr);

        if (pAttr->isRollAngleValid)
        {
            *pBuffer = pAttr->rollAngle;
            return true;
        }

        return false;
    }

    /* Please see man pages for details 
        

        

        
     */

    /* Please see man pages for details 
        
     
                    
                    
     
        
                                        
                                        
     
        
                    
     */
    bool GetLastGpsData(GpsData* pBuffer);

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
                    
                    
     */
    static const u8* GetGpsVersionId(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isVersionIdValid ? pGps->versionId : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsLatitudeRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->latitudeRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsLatitude(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isLatitudeValid ? pGps->latitude : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsLongitudeRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->longitudeRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsLongitude(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isLongitudeValid ? pGps->longitude : NULL;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetGpsAltitudeRef(u8* pBuffer, const GpsData* pGps)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pGps);

        if (pGps->isAltitudeRefValid)
        {
            *pBuffer = pGps->altitudeRef;
        }

        return pGps->isAltitudeRefValid;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsAltitude(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isAltitudeValid ? (&pGps->altitude) : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsTimeStamp(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isTimeStampValid ? pGps->timeStamp : NULL;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
     
        
                                        
     
        
                    
     */
    static const char* GetGpsSatellites(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->pSatellites;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsStatus(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->status[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsMeasureMode(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->measureMode[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsDop(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isDopValid ? (&pGps->dop) : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsSpeedRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->speedRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsSpeed(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isSpeedValid ? (&pGps->speed) : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsTrackRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->trackRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsTrack(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isTrackValid ? (&pGps->track) : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsImgDirectionRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->imgDirectionRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsImgDirection(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isImgDirectionValid ? (&pGps->imgDirection) : NULL;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
     
        
                                        
     
        
                    
     */
    static const char* GetGpsMapDatum(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->pMapDatum;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsDestLatitudeRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->destLatitudeRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsDestLatitude(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isDestLatitudeValid ? pGps->destLatitude : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsDestLongitudeRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->destLongitudeRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsDestLongitude(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isDestLongitudeValid ? pGps->destLongitude : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsDestBearingRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->destBearingRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsDestBearing(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isDestBearingValid ? (&pGps->destBearing) : NULL;
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static char GetGpsDestDistanceRef(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->destDistanceRef[0];
    }

    /* Please see man pages for details 
        
     
        
                                        
     
        
                    
     */
    static const Rational* GetGpsDestDistance(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->isDestDistanceValid ? (&pGps->destDistance) : NULL;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
                    
                    
     
        
                                        
     
        
                    
     */
    static const u8* GetGpsProcessingMethodPointer(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        if (pGps->pProcessingMethod && pGps->processingMethodSize)
        {
            return pGps->pProcessingMethod;
        }

        return NULL;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
                    
     
        
                                        
     
        
                    
     */
    static size_t GetGpsProcessingMethodSize(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        if (pGps->pProcessingMethod && pGps->processingMethodSize)
        {
            return pGps->processingMethodSize;
        }

        return 0;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
                    
                    
     
        
                                        
     
        
                    
     */
    static const u8* GetGpsAreaInformationPointer(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        if (pGps->pAreaInformation && pGps->areaInformationSize)
        {
            return pGps->pAreaInformation;
        }

        return NULL;
    }

    /* Please see man pages for details 
        
     
                    
     
                    
                    
     
        
                                        
     
        
                    
     */
    static size_t GetGpsAreaInformationSize(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        if (pGps->pAreaInformation && pGps->areaInformationSize)
        {
            return pGps->areaInformationSize;
        }

        return 0;
    }

    /* Please see man pages for details 
        
     
                    
     
        
                                        
     
        
                    
                    
     */
    static const char* GetGpsDateStamp(const GpsData* pGps)
    {
        NN_ASSERT(pGps);

        return pGps->pDateStamp;
    }

    /* Please see man pages for details 
        
     
        
     
        
                                        
     
        
                    
     */
    static bool GetGpsDifferential(u16* pBuffer, const GpsData* pGps)
    {
        NN_ASSERT(pBuffer);
        NN_ASSERT(pGps);

        if (pGps->isDifferentialValid)
        {
            *pBuffer = pGps->differential;
        }

        return pGps->isDifferentialValid;
    }

    /*  

*/

protected:
    detail::JpegMpDecoderWorkObj* m_pWork;
    bool    m_Initialized;
    bool    m_Padding[3];

    detail::JpegMpDecoderTemporarySettingObj m_TemporarySetting;
    void ClearTemporarySetting();

    const u8* GetLastMakerNotePointer(u32 index) const;
    size_t    GetLastMakerNoteSize(u32 index) const;
};

} // namespace CTR {
} // namespace jpeg {
} // namespace nn {

#endif // __cplusplus

#endif // NN_JPEG_JPEGMPDECODER_H_
