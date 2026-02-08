/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl_ReadTexturePackage.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/util.h>
#include <nn/tpl.h>

#include <cstring>
#include <cstdio>

#include "tpl_crc32.h"
#include "tpl_Internal.h"

namespace nn { namespace tpl { namespace CTR {

// Gets the number of textures included in the texture package file.
u16 GetTextureNum(const void* pTexPackage)
{
    if (pTexPackage == NULL)
    {
        NN_NULL_TASSERT_(pTexPackage);
        return 0;
    }
    const CtrTexturePackageHeader* header =
        reinterpret_cast<const CtrTexturePackageHeader*>(pTexPackage);
    return header->numTexture;
}

// Function to get the texture index
s16 GetTextureIndex(const void* pTexPackage, const char* texPath)
{
    if(pTexPackage == NULL || texPath == NULL)
    {
        NN_NULL_TASSERT_(pTexPackage);
        NN_NULL_TASSERT_(texPath);
        return -1;
    }
    // Creates the CRC32 hash code.
    int fileNameLen = (int)::std::strlen(texPath);
    unsigned int crc32key = calculate_crc32(texPath, fileNameLen);

    const CtrTexturePackageHeader &header =
        *reinterpret_cast<const CtrTexturePackageHeader *>(pTexPackage);
    const CtrTextureHash *texHash = reinterpret_cast<const CtrTextureHash *>
                      ((const char*)pTexPackage + (header.texHashOffset));

    // Compares to texture information in the package and searches for matches.
    TPK_SEARCH_DATA data = { texPath, fileNameLen, pTexPackage };
    int t = search_crc32_data(
        texHash, header.numTexture, sizeof(CtrTextureHash), crc32key, &data);

    if(t < 0) return -1;
    return texHash[t].index;
}

// Function to get texture
void* GetTexture(s32* mipLevel, u32* mipmapSize, const void* pTexPackage, const s16 texIndex)
{
    if( mipLevel == NULL || mipmapSize == NULL || pTexPackage == NULL )
    {
        NN_NULL_TASSERT_(mipLevel);
        NN_NULL_TASSERT_(mipmapSize);
        NN_NULL_TASSERT_(pTexPackage);
        return 0;
    }

    // Confirms that the specified number is included in the number of textures.
    const CtrTexturePackageHeader *header =
        reinterpret_cast<const CtrTexturePackageHeader *>(pTexPackage);
    NN_TASSERT_((0 <= texIndex) && (texIndex < header->numTexture));
    if((texIndex < 0) || (header->numTexture <= texIndex))
    {
        return 0;
    }

    const CtrTextureInfo *texInfo = reinterpret_cast<const CtrTextureInfo *>
        (((const char*)pTexPackage) + (sizeof(CtrTexturePackageHeader)) + (sizeof(CtrTextureInfo) * texIndex));

    if(texInfo == NULL)
    {
        return 0;
    }

    // get texture size.
    const unsigned int *Size = reinterpret_cast<const unsigned int *>
        (((const char*)pTexPackage) + (4 * texInfo->bitmapSizeOffset));

    *mipLevel = static_cast<int>(texInfo->mipLevel);
    for(int i=0; i < *mipLevel; i++)
    {
        mipmapSize[i] = Size[i];
    }

    return (void*)(((const char*)pTexPackage) + (header->texDataOffset + texInfo->texDataOffset));
}

// Function to get texture information
bool GetTextureInfo(CtrTextureInfo* pTexInfo, const void* pTexPackage, const s16 texIndex)
{
    if(pTexPackage == NULL || pTexInfo == NULL)
    {
        NN_NULL_TASSERT_(pTexPackage);
        NN_NULL_TASSERT_(pTexInfo);
        return false;
    }


    // Confirms that the specified number is included in the number of textures.
    const CtrTexturePackageHeader *header =
        reinterpret_cast<const CtrTexturePackageHeader *>(pTexPackage);
    NN_TASSERT_((0 <= texIndex) && (texIndex < header->numTexture));
    if((texIndex < 0) || (header->numTexture <= texIndex))
    {
        return false;
    }

    const CtrTextureInfo *texInfo = reinterpret_cast<const CtrTextureInfo *>
        (((const char*)pTexPackage) + (sizeof(CtrTexturePackageHeader)) + (sizeof(CtrTextureInfo) * texIndex));

    pTexInfo->filePathOffset   = texInfo->filePathOffset;
    pTexInfo->texDataSize      = texInfo->texDataSize;
    pTexInfo->texDataOffset    = texInfo->texDataOffset;
    pTexInfo->texFormat        = texInfo->texFormat;
    pTexInfo->width            = texInfo->width;
    pTexInfo->height           = texInfo->height;
    pTexInfo->mipLevel         = texInfo->mipLevel;
    pTexInfo->type             = texInfo->type;
    pTexInfo->cubeDir          = texInfo->cubeDir;
    pTexInfo->bitmapSizeOffset = texInfo->bitmapSizeOffset;
    pTexInfo->srcFileTime      = texInfo->srcFileTime;

    return true;
}


// Function to check the texture package header (helper function)
bool CheckTexturePackageHeader(const void* pTexPackage)
{
    if(pTexPackage == NULL)
    {
        NN_NULL_TASSERT_(pTexPackage);
        return false;
    }

    // Confirms that the specified number is included in the number of textures.
    const CtrTexturePackageHeader *header =
        reinterpret_cast<const CtrTexturePackageHeader *>(pTexPackage);
    NN_NULL_TASSERT_(header);

    // Confirms header magic code.
    if(::std::strncmp(header->magic, "CTPK", 4) != 0)
    {
        NN_LOG("ERROR: The texture package's magic code isn't 'CTPK'.\n");
        return false;
    }

    if(header->version != CTR_TEXTURE_PACKAGE_VERSION)
    {
        NN_LOG("ERROR: The texture package's version code differs.\n");
        return false;
    }

    return true;
}


}}}
