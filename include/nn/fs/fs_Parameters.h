/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_Parameters.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_PARAMETERS_H_
#define NN_FS_FS_PARAMETERS_H_

#include <nn/types.h>
#include <nn/config.h>
#include <nn/dbg/dbg_Logger.h>
#include <nn/assert.h>
#include <nn/util.h>
#include <nn/util/util_Int64.h>

namespace nn {
namespace fs {

static const size_t MAX_ARCHIVE_NAME_LENGTH = 7;
static const size_t MAX_SUB_PATH_LENGTH = 253;
static const size_t MAX_FILE_PATH_LENGTH = MAX_ARCHIVE_NAME_LENGTH + 1 + MAX_SUB_PATH_LENGTH;

/* Please see man pages for details 
    
            
*/
static const s64 LATENCY_RECOMMENDED_SD_MAX = 700;

/* Please see man pages for details 
    

            
*/
static const s64 UI_BLOCK_SIZE = 128 * 1024;

/* Please see man pages for details 
    

    
*/
enum OpenMode
{
    OPEN_MODE_READ    = (1u << 0),  //
    OPEN_MODE_WRITE   = (1u << 1),  //
    OPEN_MODE_CREATE  = (1u << 2)   //
};

/* Please see man pages for details 
    
*/
enum PositionBase
{
    POSITION_BASE_BEGIN,    //
    POSITION_BASE_CURRENT,  //
    POSITION_BASE_END       //
};

struct Transaction
{
    bit32   dummy;
};

/* Please see man pages for details 
    

    
*/
struct Attributes
{
    bool isDirectory;   //
    bool isHidden;      //
    bool isArchive;     //
    bool isReadOnly;    //
};

/* Please see man pages for details 
    

    
*/
struct ShortName
{
    char body[10];      //
    char ext[4];        //
    bool valid;         //
    bit8 pad;
};

/* Please see man pages for details 
    

    
*/
struct DirectoryEntry
{
    wchar_t            entryName[MAX_FILE_PATH_LENGTH + 1]; //
    ShortName          shortName;   //
    nn::fs::Attributes attributes;  //
    s64                entrySize;   //
};

enum MediaType
{
    MEDIA_TYPE_NAND     = 0,
    MEDIA_TYPE_SDMC     = 1,
    MEDIA_TYPE_CTRCARD  = 2
};

namespace detail { struct ArchiveHandleTag {}; }
typedef nn::util::Int64<bit64, detail::ArchiveHandleTag> ArchiveHandle;

typedef bit64 ExtSaveDataId;    //
typedef bit64 TitleId;

/* Please see man pages for details 
    
*/
enum PriorityForApplication
{
    PRIORITY_APP_REALTIME   = -16, //
    PRIORITY_APP_NORMAL     =  -8, //
    PRIORITY_APP_LOW        =   8  //
};

} // end of namespace fs
} // end of namespace nn

namespace nn { namespace CTR {

typedef struct DUMMY1
{
    bit8 data[948];
} Dummy1;

typedef struct DUMMY2
{
    bit8 data[9152];
} Dummy2;

}}

#endif  // ifndef NN_FS_FS_ENUMS_H_
