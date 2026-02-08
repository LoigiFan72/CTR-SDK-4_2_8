/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl_PackagerType.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_TPL_CTR_TPL_PACKAGERTYPES_H_
#define NN_TPL_CTR_TPL_PACKAGERTYPES_H_


namespace nn { namespace tpl { namespace CTR {

// Maximum MipMap level
#define NN_TPL_MAX_MIPMAPLEVEL  8       // 1024×1024dot

/* Please see man pages for details 
    

    
    
    
*/
enum CtrTexFormat
{
    TEXFMT_RGBA8888 = 0,        //
    TEXFMT_RGB888   = 1,        //
    TEXFMT_RGBA5551 = 2,        //
    TEXFMT_RGB565   = 3,        //
    TEXFMT_RGBA4444 = 4,        //
    TEXFMT_LA88     = 5,        //
    TEXFMT_HL8      = 6,        //
    TEXFMT_L8       = 7,        //
    TEXFMT_A8       = 8,        //
    TEXFMT_LA44     = 9,        //
    TEXFMT_L4       = 10,       //
    TEXFMT_A4       = 11,       //
    TEXFMT_ETC1     = 12,       //
    TEXFMT_ETC1_A4  = 13,       //

    TEXFMT_SHADOW   = 0x10,     //
    TEXFMT_GAS      = 0x20,     //
    TEXFMT_REF      = 0x30,     //

    TEXFMT_UNSUPPORT = 0xff,    //

    TEXFMT_ForceInt32 = 0x7fffffff
};

/* Please see man pages for details 
    

    
    
*/
struct CtrTextureInfo
{
    unsigned int        filePathOffset;     //
    unsigned int        texDataSize;        //
    unsigned int        texDataOffset;      //
    CtrTexFormat        texFormat;          //
    unsigned short      width;              //
    unsigned short      height;             //
    unsigned char       mipLevel;           //
    unsigned char       type;               //
    unsigned short      cubeDir;            //
    unsigned int        bitmapSizeOffset;   //
    unsigned int        srcFileTime;        //
};

#define CTR_TEXTURE_PACKAGE_VERSION     1


}}} // Namespace


#endif  // ifndef NN_TPL_CTR_TPL_PACKAGERTYPES_H_
