/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_IInputStream.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_IINPUTSTREAM_H_
#define NN_FS_FS_IINPUTSTREAM_H_

#include <nn/fs/fs_IPositionable.h>

namespace nn {
namespace fs {

class IInputStream : public virtual IPositionable
{
public:
    virtual ~IInputStream() {};

    virtual Result TryRead(s32* pOut, void* buffer, size_t size) = 0;
    virtual s32 Read(void* buffer, size_t size) = 0;
};

}
}

#endif /* NN_FS_FS_IINPUTSTREAM_H_ */
