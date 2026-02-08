/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_NsData.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_NSDATA_H_
#define NN_BOSS_BOSS_NSDATA_H_

#include <nn/fnd/fnd_DateTime.h>
#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class NsData
{
public:
    static const s32 NN_BOSS_NSDATA_READ_ERROR_GET_HEADER = -1;  //
    static const s32 NN_BOSS_NSDATA_READ_ERROR_READ_DATA  = -2;  //
    static const s32 NN_BOSS_NSDATA_READ_ERROR_IPC        = -3;  //
    static const s32 NN_BOSS_NSDATA_READ_ERROR_UPDATED    = -4;  //
    NN_PADDING4;

/* Please see man pages for details 
  
*/
    explicit NsData(void);

/* Please see man pages for details 
  
*/
    virtual ~NsData(void);

/* Please see man pages for details 
  

  
  
  
  
*/
    nn::Result Initialize(u32 serial);

/* Please see man pages for details 
  

                

  
  
  
  
  
*/
    nn::Result Delete(void);

/* Please see man pages for details 
  

                
                
                
                
                
                
                
                
                
                
                

  
  
  
  
  
  
  
  
  
  
  
*/
    nn::Result GetHeaderInfo(HeaderInfoType type, void* pValue, size_t size);

/* Please see man pages for details 
  

                
                
                
                
                
                
                
                

  
  
  
  
  
  
  
*/
    s32 ReadData(u8* pDataBuf, size_t bufLen);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
  
  
*/
    nn::Result SetReadDataPosition(s64 position, PositionBase base);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
*/
    nn::Result SetAdditionalInfo(u32 info);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
  
*/
    nn::Result GetAdditionalInfo(u32* pInfo);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
*/
    nn::Result SetReadFlag(bool flag);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
*/
    nn::Result GetReadFlag(bool* pFlag);

/* Please see man pages for details 
  

                

  
  
  
  
  
  
  
  
*/
    nn::Result GetLastUpdated(nn::fnd::DateTime* pTime);

protected:
    bool            m_Privileged;
    NN_PADDING3;
    u32             m_SerialId;
    s32             m_dataSize;
    u32             m_DataVersion;
    AppIdType       m_AppId;
    s64             m_ReadDataPos;
};


} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus

#endif /* NN_BOSS_BOSS_NSDATA_H_ */
