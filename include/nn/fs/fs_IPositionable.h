/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_IPositionable.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_IPOSITIONABLE_H_
#define NN_FS_FS_IPOSITIONABLE_H_

#include <nn/fs/fs_Parameters.h>

namespace nn {
namespace fs {

class IPositionable
{
protected:
    virtual ~IPositionable() {};

public:

    virtual Result TrySeek(s64 position, PositionBase base) = 0;
    virtual void Seek(s64 position, PositionBase base) = 0;
    
    virtual Result TryGetPosition(s64* pOut) const = 0;
    virtual s64 GetPosition() const = 0;
    
    virtual Result TrySetPosition(s64 position) = 0;
    virtual void SetPosition(s64 position) = 0;
    
    virtual Result TryGetSize(s64* pOut) const = 0;
    virtual s64 GetSize() const = 0;
    
};

}
}

#endif /* NN_FS_FS_IPOSITIONABLE_H_ */
