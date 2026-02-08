/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl_Internal.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_TPL_INTERNAL_H_
#define NN_TPL_INTERNAL_H_


namespace nn { namespace tpl { namespace CTR {

enum CtrTexType
{
    TEXTYPE_CUBE = 0,           //
    TEXTYPE_1D,                 //
    TEXTYPE_2D,                 //

    TEXTYPE_UNSUPPORT = 0xff,   //

    TEXTYPE_ForceInt32 = 0x7fffffff
};

enum CtrTexCubeDir
{
    TEXCUBEDIR_PLUS_X = 0,          //
    TEXCUBEDIR_MINUS_X,             //
    TEXCUBEDIR_PLUS_Y,              //
    TEXCUBEDIR_MINUS_Y,             //
    TEXCUBEDIR_PLUS_Z,              //
    TEXCUBEDIR_MINUS_Z,             //

    TEXCUBEDIR_UNSUPPORT = 0xff,    //

    TEXCUBEDIR_ForceInt32 = 0x7fffffff
};

/* Please see man pages for details 

*/
struct CtrTextureHash
{
    /// Hash value (CRC-32) generated from texture name
    unsigned int    crc;
    
    /// Texture index
    int             index;
};

/* Please see man pages for details 






*/
struct CtrTextureConvertOpt
{
    /// Specify output format. (Cast CtrTexFormat)
    unsigned char   specFormat;

    /// Upper limit specification for mipmap level (0 is unlimited)
    unsigned char   mipmapLimit;

    /// Compression is permitted (prohibit with 0)
    unsigned char   permitCompression;

    /// ETC1 compression method
    unsigned char   etc1Method;
};

/* Please see man pages for details 

 
 
 
 
 






*/
struct CtrTexturePackageHeader
{
    /// Magic code ("CTPK" fixed)
    char            magic[4];
    /// File format version number (CTR_TEXTURE_PACKAGE_VERSION is substituted)
    unsigned short  version;
    /// Number of textures
    unsigned short  numTexture;
    /// Offset to start of image data
    unsigned int    texDataOffset;
    /// Image data size
    unsigned int    texDataSize;
    /// Offset to filename hash
    unsigned int    texHashOffset;
    /// Offset to convert option table
    unsigned int    convertOptOffset;
    /// Padding to 32-byte boundary
    char            pad[8];
};


}}}


#endif  // ifndef NN_TPL_INTERNAL_H_
