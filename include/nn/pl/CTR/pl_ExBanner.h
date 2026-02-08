/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl_ExBanner.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_CTR_PL_EXBANNER_H_
#define NN_PL_CTR_PL_EXBANNER_H_

namespace nn
{
namespace pl
{
namespace CTR
{
    //Extended banner data
    //Possible to replace banner texture or change the text displayed on the lower part of the Home Menu top screen
    //
    const u32 EXBANNER_TEXTURE_NAME_LENGTH = 16;
    const u32 EXBANNER_MESSAGE_LENGTH      = 256;

    //Format of the texture image after replaced
    //The format must be the PICA native format
    //See the comments for which values correspond to which PICA native format
    //
    enum ExBannerTexFormat
    {
        EXBANNER_TEX_FORMAT_RGBA8    = 0,  //format GL_RGBA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_RGB8     = 1,  //format GL_RGB_NATIVE_DMP
        EXBANNER_TEX_FORMAT_RGBA5551 = 2,  //format GL_RGBA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_RGB565   = 3,  //format GL_RGB_NATIVE_DMP
        EXBANNER_TEX_FORMAT_RGBA4    = 4,  //format GL_RGBA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_LA8      = 5,  //format GL_LUMINANCE_ALPHA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_HILO8    = 6,  //format GL_HILO8_DMP_NATIVE_DMP
        EXBANNER_TEX_FORMAT_L8       = 7,  //format GL_LUMINANCE_NATIVE_DMP
        EXBANNER_TEX_FORMAT_A8       = 8,  //format GL_ALPHA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_LA4      = 9,  //format GL_LUMINANCE_ALPHA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_L4       = 10, //format GL_LUMINANCE_NATIVE_DMP
        EXBANNER_TEX_FORMAT_A4       = 11, //format GL_ALPHA_NATIVE_DMP
        EXBANNER_TEX_FORMAT_ETC1     = 12, //format GL_ETC1_RGB8_NATIVE_DMP
        EXBANNER_TEX_FORMAT_ETC1A4   = 13  //format GL_ETC1_ALPHA_RGB8_A4_NATIVE_DMP
    };

    struct ExBanner
    {
        u16 tex_width;   // Width of the texture after replaced
        u16 tex_height;  // Height of the texture after replaced
        u8  tex_format;  // Texture format (specify with nn::CTR::ExBannerTexFormat)
        NN_PADDING3;

        s32 limit_year;  // Expiration term (can display the set year/month/date including the time 23:59)
        s32 limit_month; // The term setting is valid only for downloaded extended banners
        s32 limit_date;  // This setting is ignored for local extended banners

        char    texture_name[EXBANNER_TEXTURE_NAME_LENGTH]; // Name of texture to overwrite
        wchar_t text[EXBANNER_MESSAGE_LENGTH];              // Extended banner message
        void    *tex_data;                                  // Variable length, start of texture data 
    };
}
}
}

#endif  // ifndef NN_PL_CTR_PL_EXBANNER_H_

