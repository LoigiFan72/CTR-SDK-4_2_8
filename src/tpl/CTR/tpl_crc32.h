/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     tpl_crc32.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_TPL_CTR_TPL_CRC32_H_
#define NN_TPL_CTR_TPL_CRC32_H_

#ifdef __cplusplus
extern "C" {
#endif

namespace nn { namespace tpl { namespace CTR {

// Implementation to search for texture using the hash (search_crc32_data()) from the texture package (.ctpk) header information.
// 
struct TPK_SEARCH_DATA
{
    const char *szFileName; // Texture file name being searched
    int fileNameLen;        // Character count for comparison (will change depending on whether extensions are compared)
    const void *infoData;   // Texture package header information
};

/* Please see man pages for details 

*/
unsigned int calculate_crc32(
    const void *data,
    unsigned int size);


/* Please see man pages for details 







*/
int search_crc32_index(
    const void *base, unsigned int num, unsigned int width, unsigned int crc);


/* Please see man pages for details 
 
 















*/
int search_crc32_data(
    const void *base, unsigned int num, unsigned int width, unsigned int crc,
    const void *value);

}}} // Namespace

#ifdef __cplusplus
}
#endif


#endif	// NN_TPL_CTR_TPL_CRC32_H_
