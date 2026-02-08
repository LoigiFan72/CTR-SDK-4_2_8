/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_File.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILE_H_
#define NN_FS_FS_FILE_H_

#include <nn/fs/fs_FileStream.h>

namespace nn {
namespace fs {

// Do not use this class again
class File : private nn::fs::FileStream
{
private:
    typedef FileStream Base;
public:
    File() {}
    File( const wchar_t* pathName, bit32 mode, Attributes ) : FileStream(pathName, mode) {}

    void Open(const wchar_t* pathName, bit32 mode, Attributes ) { Base::Initialize(pathName, mode); }
    nn::Result TryOpen(const wchar_t* pathName, bit32 mode, Attributes) { return Base::TryInitialize(pathName, mode); }
    using Base::Read;
    using Base::Write;
#pragma push
#pragma diag_suppress 997
    void SetPosition( s64 position, PositionBase base) { Base::Seek(position, base); }
#pragma pop
    using Base::GetPosition;
    using Base::GetSize;
    using Base::SetSize;
    void Close() { Base::Finalize(); }
    
    static void Delete(const wchar_t* pathName);
    static Result TryDelete(const wchar_t* pathName);
    
};

} // end of namespace fs
} // end of namespace nn

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_Result.h>

#endif  // ifndef NN_FS_FS_FILE_H_
