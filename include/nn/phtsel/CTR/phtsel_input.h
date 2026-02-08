/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     phtsel_input.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_PHTSEL_CTR_PHTSEL_INPUT_H_
#define NN_PHTSEL_CTR_PHTSEL_INPUT_H_

/* Please see man pages for details 
  
  
*/

#include <nn/types.h>
#include <nn/fnd.h>

#ifdef  __cplusplus

namespace nn {
namespace phtsel {
namespace CTR {

/*
  
  
  
 */
struct DateTimeConvert
{
public:
    s64     seconds;   //

public:
    /*
      
      
      
      
      */
    static const DateTimeConvert&   GetMinSeconds();
    /*
      
      
      
      
      */
    static const DateTimeConvert&   GetMaxSeconds();

    /*
      
      
      */
    s64     GetSeconds() const{ return seconds; }
    /*
      
      
      */
    void    SetSeconds(s64 seconds);


    /*=======================================================================
      Seconds elapsed <--> YYYY/MM/DD HH:MM:SS
      =======================================================================*/
    /*
      
      
      
      
      
      
      
      */
    void    ConvertToParam(
                s32* pYear, s32* pMonth, s32* pDay,
                s32* pHour, s32* pMinute, s32* pSecond
            ) const;
    /*
      
      
      
      
      
      
      
      
      
      
      
      
      */
    bool    ConvertFromParam(
                s32 year, s32 month, s32 day,
                s32 hour, s32 minute, s32 second
            );

    /*=======================================================================
      Seconds elapsed <--> type nn:fnd::DateTime
      =======================================================================*/
    /*
      
      
      */
    nn::fnd::DateTime    ConvertToNNDateTime() const;
    /*
      
      
      */
    void    ConvertFromNNDateTime(const nn::fnd::DateTime& dateTime);
};

/*

  
  
  

 */
struct PhtselInput
{
public:
    //----------------------------------------
    //

    /* Please see man pages for details 
        
    */
    enum ImageKind
    {
        IMAGE_KIND_RESERVED_0 = 0, //

        IMAGE_KIND_JPEG,           //
        IMAGE_KIND_MP,             //
        IMAGE_KIND_RESERVED_1,     //

        IMAGE_KIND_RESERVED_4,     //
        IMAGE_KIND_RESERVED_5,     //
        IMAGE_KIND_RESERVED_6,     //
        IMAGE_KIND_RESERVED_7,     //

        IMAGE_KIND_NUM = IMAGE_KIND_RESERVED_4   //
    };

    /* Please see man pages for details 
        
    */
    enum ImageKindBit
    {
        IMAGE_KIND_BIT_JPEG    = 1 << IMAGE_KIND_JPEG,    //
        IMAGE_KIND_BIT_MP      = 1 << IMAGE_KIND_MP,      //

        //
        IMAGE_KIND_BIT_PICTURE = IMAGE_KIND_BIT_JPEG
                               | IMAGE_KIND_BIT_MP
    };

    /* Please see man pages for details 
        
    */
    static const u16   SHOOTING_TYPE_BIT_DEFAULT = 0xFFFF;

    /* Please see man pages for details 
        
    */
    static const u8    DISTINCTION_TYPE_BIT_DEFAULT = 0;

    /* Please see man pages for details 
        
    */
    enum ScreenShotType
    {
        SCREEN_SHOT_TYPE_FLAG_ON,   //
        SCREEN_SHOT_TYPE_FLAG_OFF,  //
        SCREEN_SHOT_TYPE_ALL,       //
        SCREEN_SHOT_TYPE_MAX        //
    };

    /* Please see man pages for details 
        
    */
    enum FaceType
    {
        FACE_TYPE_FLAG_ON,  //
        FACE_TYPE_FLAG_OFF, //
        FACE_TYPE_ALL,      //
        FACE_TYPE_MAX       //
    };


    /* Please see man pages for details 
        
    */
    static const size_t MAX_FACE_INFO_NUM = 4;

    /* Please see man pages for details 
        
    */
    static const size_t TITLE_UNIQUE_ID_MAX_NUM = 100;

    /* Please see man pages for details 
        
    */
    static const u32    TITLE_UNIQUE_ID_ERROR  = 0xFFFFFFFF;

    /* Please see man pages for details 
        
    */
    enum DistributeType
    {
        DISTRIBUTE_TYPE_FLAG_ON,            //
        DISTRIBUTE_TYPE_FLAG_OFF,           //
        DISTRIBUTE_TYPE_ALL,                //
        DISTRIBUTE_TYPE_MAX                 //
    };

    /* Please see man pages for details 
        
    */
    enum STSize
    {
        ST_SIZE_DEFAULT, //
        ST_SIZE_NUM      //
    };

    /* Please see man pages for details 
        
    */
    static const size_t MESSAGE_MAX_NUM     = 128;

    /* Please see man pages for details 
        
        
        
    */
    static const size_t INPUT_RESERVED_SIZE = 200;

protected:

    /* Please see man pages for details 
        

        
    */
    DateTimeConvert m_nSecStart;

    /* Please see man pages for details 
        

        
    */
    DateTimeConvert m_nSecEnd;

    /* Please see man pages for details 
        

        
    */
    u8 m_nStoTypeBit;

    /* Please see man pages for details 
        

        
    */
    ImageKindBit m_eImgKindBit;

    /* Please see man pages for details 
        

        
    */
    u16 m_nShootTypeBit;

    /* Please see man pages for details 
        

        
    */
    s32 m_nMinFaceNum;

    /* Please see man pages for details 
        

        
    */
    s32 m_nMaxFaceNum;

    /* Please see man pages for details 
        

        
    */
    u8 m_nDisTypeBit;

    /* Please see man pages for details 
        

        
    */
    ScreenShotType m_eScrShotType;

    /* Please see man pages for details 
        

        
    */
    FaceType m_eFaceType;


    /* Please see man pages for details 
        

        
    */
    DistributeType m_eDistributeType;

    /* Please see man pages for details 
        

        
    */
    u32 m_nTitleUniqueId[TITLE_UNIQUE_ID_MAX_NUM];

    /* Please see man pages for details 
        

        
    */
    u8  m_nTitleUniqueIdNum;

    NN_PADDING3;


    /* Please see man pages for details 
        

        
    */
    STSize m_eThumbnailSize;

    /* Please see man pages for details 
        

        
    */
    bool m_bSoundEnable;

    /* Please see man pages for details 
        

        
    */
    wchar_t m_nMessage[MESSAGE_MAX_NUM];

    NN_PADDING2;

    /* Please see man pages for details 
        

        
    */
    u8                  m_reserved[INPUT_RESERVED_SIZE];
public:

    //----------------------------------------
    //

    /* Please see man pages for details 
        

        

        

    */
    void InitAll();


    //----------------------------------------
    //

    /* Please see man pages for details 

        
        

        
    */
    void SetSecStart(const DateTimeConvert& secondsStart);

    /* Please see man pages for details 
        
        

        
    */
    void SetSecEnd(const DateTimeConvert& secondsEnd);

    /* Please see man pages for details 
        
        

        
    */
    void SetImgKindBit(ImageKindBit imageKindBit);

    /* Please see man pages for details 
        
        

        
    */
    void SetScreenShotType(ScreenShotType screenShotType);

    /* Please see man pages for details 
        
        

        
    */
    void SetFaceType(FaceType faceType);

    /* Please see man pages for details 
        
        

        
    */
    void SetMinFaceNum(s32 minFaceNum);

    /* Please see man pages for details 
        
        

        
    */
    void SetMaxFaceNum(s32 maxFaceNum);

    /* Please see man pages for details 
        

        

        
                        
    */
    void SetTitleUniqueId(u32 titleUniqueId) NN_ATTRIBUTE_DEPRECATED;

    /* Please see man pages for details 
        
        

        
                        
                        
                        
    */
    void AddTitleUniqueId(u32 titleUniqueId);

    /* Please see man pages for details 
        

        
    */
    void ClearTitleUniqueId();

    /* Please see man pages for details 
        
        

        
    */
    void SetDistributeType(DistributeType distributeType);

    /* Please see man pages for details 
        
        

        
    */
    void SetSoundEnable(bool soundEnable);

    /* Please see man pages for details 
        
        

        
                        
    */
    void SetMessage(const wchar_t* message);

    //----------------------------------------
    //

    /* Please see man pages for details 
        
        
    */
    const DateTimeConvert& GetSecStart() const;

    /* Please see man pages for details 
        
        
    */
    const DateTimeConvert& GetSecEnd() const;

    /* Please see man pages for details 
        
  
        
        
    */
    u8 GetStoTypeBit() const;

    /* Please see man pages for details 
        
        
    */
    ImageKindBit GetImgKindBit() const;

    /* Please see man pages for details 
        
        
    */
    u16 GetShootTypeBit() const;

    /* Please see man pages for details 
        
        
    */
    u8 GetDisTypeBit() const;

    /* Please see man pages for details 
        
        
    */
    ScreenShotType GetScreenShotType() const;

    /* Please see man pages for details 
        
        
    */
    FaceType GetFaceType() const;

    /* Please see man pages for details 
        
        
    */
    s32 GetMinFaceNum() const;

    /* Please see man pages for details 
        
        
    */
    s32 GetMaxFaceNum() const;

    /* Please see man pages for details 
        
        
        

        
                        
    */
    u32 GetTitleUniqueId(u8 titleUniqueIdIdx) const;

    /* Please see man pages for details 
        
        

        
                        
    */
    const u32* GetTitleUniqueIdTbl() const;

    /* Please see man pages for details 
        
        
    */
    u8 GetTitleUniqueIdNum() const;

    /* Please see man pages for details 
        
        
    */
    DistributeType GetDistributeType() const;

    /* Please see man pages for details 
        
        
    */
    STSize GetThumbnailSize() const;

    /* Please see man pages for details 
        
        
    */
    bool GetSoundEnable() const;

    /* Please see man pages for details 
        
        
    */
    const wchar_t* GetMessage() const;
};

} // end of namespace CTR
} // end of namespace phtsel
} // end of namespace nn

#endif /*__cplusplus*/

#endif /* NN_PHTSEL_CTR_PHTSEL_INPUT_H_ */
