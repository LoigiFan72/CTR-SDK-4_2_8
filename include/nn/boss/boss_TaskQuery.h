/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_TaskQuery.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46667 $
 *---------------------------------------------------------------------------*/

#ifndef NN_BOSS_BOSS_TASK_QUERY_H_
#define NN_BOSS_BOSS_TASK_QUERY_H_

#include <nn/boss/boss_Const.h>
#include <nn/boss/boss_Result.h>
#include <nn/boss/boss_Types.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  
*/
class TaskQuery
{
public:
/* Please see man pages for details 
  
*/
    explicit TaskQuery(void);

/* Please see man pages for details 
  
*/
    virtual ~TaskQuery(void);

/* Please see man pages for details 
  

  
  
  
*/
    nn::Result Initialize(void);

/* Please see man pages for details 
  

  
*/
    u8 GetSize(void);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
*/
    nn::Result GetType(u8 index, QueryType* pType);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
*/
    nn::Result GetName(u8 index, char* pName, size_t size);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
*/
    nn::Result GetValue(u8 index, void* pValue, size_t size);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
*/
    nn::Result AddQuery(const char* pName, const char* pValue);

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
  
*/
    nn::Result AddQuery(const char* pName, s32 value, bool hex = false) { return AddQuery(pName, &value, sizeof(s32), hex ? QUERYTYPE_HEX_S32 : QUERYTYPE_S32); }

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
  
*/
    nn::Result AddQuery(const char* pName, u32 value, bool hex = false) { return AddQuery(pName, &value, sizeof(u32), hex ? QUERYTYPE_HEX_U32 : QUERYTYPE_U32); }

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
  
*/
    nn::Result AddQuery(const char* pName, s64 value, bool hex = false) { return AddQuery(pName, &value, sizeof(s64), hex ? QUERYTYPE_HEX_S64 : QUERYTYPE_S64); }

/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
  
*/
    nn::Result AddQuery(const char* pName, u64 value, bool hex = false) { return AddQuery(pName, &value, sizeof(u64), hex ? QUERYTYPE_HEX_U64 : QUERYTYPE_U64); }

protected:
    nn::Result AddQuery(const char* pName, const void* pValue, size_t size, QueryType type);
    u8 GetNextIndex(void);
    bool IsValidIndex(u8 index);

    friend class AccessConfig;
    TaskQueryConfig m_Query;
};

}
}

#endif

#endif /* NN_BOSS_BOSS_TASK_QUERY_H_ */
