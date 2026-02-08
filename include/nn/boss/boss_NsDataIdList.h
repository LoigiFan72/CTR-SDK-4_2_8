/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_NsDataIdList.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_NSDATA_ID_LIST_H_
#define NN_BOSS_BOSS_NSDATA_ID_LIST_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

const u32 INVALID_SERIAL_ID = (0xffffffff);     // Cannot get SERIALID because index is out of range.


/* Please see man pages for details 
  
*/
class NsDataIdList
{
public:
/* Please see man pages for details 
  
  
                            
                            
  

*/
    explicit NsDataIdList(u32* pSerial, u16 size);

/* Please see man pages for details 
  
*/
    virtual ~NsDataIdList(void);

/* Please see man pages for details 
  
*/
    void Initialize(void);


/* Please see man pages for details 
  
  

*/
    u16 GetSize(void);

/* Please see man pages for details 
  
  
  

*/
    u32 GetNsDataId(u16 index);

protected:
    friend class AccessConfig;
    NsDataIdInfoList    m_Nsdata;
};


} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_NSDATA_ID_LIST_H_ */
