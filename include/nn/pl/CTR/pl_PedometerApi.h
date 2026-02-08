/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     pl_PedometerApi.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_PL_CTR_PL_PEDOMETER_API_H_
#define NN_PL_CTR_PL_PEDOMETER_API_H_

#include <nn/Result.h>
#include <nn/types.h>
#include <nn/fnd.h>

#ifdef __cplusplus

namespace nn {
namespace pl {
namespace CTR {

namespace detail{
    typedef enum _IPCPortType
    {
        PORT_PEDOMETER = 0,
        PORT_PEDOMETER_HID,
        PORT_PEDOMETER_SYS,
        NUM_OF_IPC_PORTS
    } IPCPortType;

}

const char  PORT_NAME_PEDOMETER[] = "ptm:pdm";
const char  PORT_NAME_PEDOMETER_HID[] = "ptm:pdmh";
const char  PORT_NAME_PEDOMETER_SYS[] = "ptm:pdms";


/* Please see man pages for details 
  
  
*/

const s32 MAX_MONTHDAYS = 31; //
const s32 DAYHOURS = 24; //
const s32 NUM_FREESPACE = 2; //
const s32 NUM_MONTHHISTORIES = 12 * 10; //
const s32 MAX_MONTHHISTORIES = NUM_MONTHHISTORIES + NUM_FREESPACE; //
const s32 NUM_MONTHHISTORYENTRIES = MAX_MONTHDAYS * DAYHOURS; //
const u16 INVALID_COUNTER = 0xffff; //

/* Please see man pages for details 
   

           
*/
struct PedometerMonthHeader
{
    u16 unusedCounter; //
    s16 year;          //
    s16 month;         //
};

/* Please see man pages for details 
   

           
*/
struct PedometerHistoryHeader
{
    s32 version;                                        //
    u32 totalStepCount;                                 //
    nn::fnd::DateTime startRecordTime;                  //
    PedometerMonthHeader monthInfo[MAX_MONTHHISTORIES]; //
    NN_PADDING4;
};

/* Please see man pages for details 
   
*/
typedef u16 PedometerMonthData[NUM_MONTHHISTORYENTRIES];

/* Please see man pages for details 
   
*/
typedef PedometerMonthData PedometerHistoryData[MAX_MONTHHISTORIES];

/*
    
*/
enum Description
{
    DESCRIPTION_PEDOMETER_IS_WRITING = 1 //
};

/* Please see man pages for details 
    
    
*/
    NN_DEFINE_RESULT_CONST(
        ResultIsWriting,
        Result::LEVEL_STATUS, Result::SUMMARY_NOTHING_HAPPENED, Result::MODULE_NN_PTM, DESCRIPTION_PEDOMETER_IS_WRITING
    );



/* Please see man pages for details 
  
*/
struct PedometerEntry
{
  s16 year;
  s16 month;
};

/* Please see man pages for details 
    

    
*/
bool GetPedometerState();

/* Please see man pages for details 
    

    
*/
s8 GetStepHistoryEntry(PedometerEntry* pEntry);

/* Please see man pages for details 
    

    
    
    
*/
void GetStepHistory( u16 pStepCounts[], s32 numHours, nn::fnd::DateTime start );

/* Please see man pages for details 
    

    
*/
u32 GetTotalStepCount();

/* Please see man pages for details 
    

    

    
    
    
    
*/
nn::Result GetStepHistoryAll( PedometerHistoryHeader& header, PedometerHistoryData& data );

/*  

*/

} // namespace CTR {
} // namespace pl {
} // namespace nn {

#endif

#endif //   #ifndef NN_PL_CTR_PL_PEDOMETER_API_H_
