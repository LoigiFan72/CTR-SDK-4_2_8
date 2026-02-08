/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     boss_NsaList.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46667 $
 *---------------------------------------------------------------------------*/


#ifndef NN_BOSS_BOSS_NSALIST_H_
#define NN_BOSS_BOSS_NSALIST_H_

#include <nn/os/os_CriticalSection.h>
#include <nn/boss/boss_FgOnlyTask.h>

#ifdef __cplusplus

namespace nn {
namespace boss {

/* Please see man pages for details 
  

                
                
                
                

                
                
                
                

                
                
                
                 
                
*/
class NsaList
{
public:
    /* Please see man pages for details 
      
    */
    enum ParseResult
    {
        NN_BOSS_NSALIST_PARSE_ERROR_INVALID_POINTER        = -1,  //
        NN_BOSS_NSALIST_PARSE_ERROR_INVALID_WORK_BUF_SIZE  = -2,  //
        NN_BOSS_NSALIST_PARSE_ERROR_FILE_INITIALIZE_FAILED = -3,  //
        NN_BOSS_NSALIST_PARSE_ERROR_FILE_GETSIZE_FAILED    = -4,  //
        NN_BOSS_NSALIST_PARSE_ERROR_FILE_READ_FAILED       = -5,  //
        NN_BOSS_NSALIST_PARSE_ERROR_FILE_INVALID_FORMAT    = -6,  //
        NN_BOSS_NSALIST_PARSE_RESULT_MAX_VALUE             = 999  //
    };

    static const u32 NN_BOSS_NSALIST_WAIT_FINISH_TIMEOUT_DEFAULT_SEC = 30;  //
    static const s64 NN_BOSS_NSALIST_MAX_SIZE = 236054;                     //

public:
    /* Please see man pages for details 
      

             
             
             
    */
    struct SearchAttributes
    {
        char* attribute1;
        char* attribute2;
        char* attribute3;
    };

    /* Please see man pages for details 
      
    */
    struct NsaInformation
    {
        char fileName[32];     //
        u32  fileSize;         //
        u32  updateEpochTime;  //
        char attribute1[10];   //
        char attribute2[10];   //
        char attribute3[10];   //
        u8   caption[150];     //
    };

public:
/* Please see man pages for details 
  
  
*/
    explicit NsaList(const char* nsaListFilePath);

/* Please see man pages for details 
  
*/
    virtual ~NsaList(void);


/* Please see man pages for details 
  

  
  
  
  
  
  
  
  
  
  
  
  
  
*/
    nn::Result Download(const char* bossCode, const char* taskId, const SearchAttributes* attributes = NULL, u32 waitTimeoutSec = NN_BOSS_NSALIST_WAIT_FINISH_TIMEOUT_DEFAULT_SEC, s64 fileSize = NN_BOSS_NSALIST_MAX_SIZE);


/* Please see man pages for details 
  

                

  
  
*/
    nn::Result Cancel(void);


/* Please see man pages for details 
  

                
                
                
                
                
                
                
                

  
  
*/
    u32 GetHttpStatusCode(void);


/* Please see man pages for details 
  

                
                
         
                
                
                  
                  
                
                  
                
                  
                  
                  
                  
                  
         

  
*/
    TaskResultCode GetResult(void);


/* Please see man pages for details 
  

                
                

  
  
  
  
  
  
  
*/
    ParseResult Parse(u32* pOutParseCount, NsaInformation pNsaInformationArray[], u32 nsaInformationArraySize, void* pWorkBuf, size_t workBufSize, u32 nsaFirstPos = 0);


 /* Please see man pages for details 
   

                 
                 
                 
                 

   
   
   
   
   
   
 */
    nn::Result GetDigest(u8* pDigestBuf, size_t digestBufSize);

 /* Please see man pages for details 
   

   
   
   
 */
    bool CheckValidity(void* pWorkBuf, size_t workBufSize);

private:
    nn::Result RegisterWaitEvent(nn::os::Event* pEvent);
    nn::Result UnregisterWaitEvent(nn::os::Event* pEvent);
    nn::Result WaitFinishWaitEvent(void);
    nn::Result WaitFinishWaitEvent(const nn::fnd::TimeSpan& timeout);
    nn::Result WaitFinish(void);
    nn::Result WaitFinish(const nn::fnd::TimeSpan& timeout);
    void CancelWaitFinish(void);

private:
    bool m_IsCanceled;
    NN_PADDING3;

    nn::os::CriticalSection m_Cs;
    nn::os::Event* m_pWaitEvent;

    const char* m_NsaListFilePath;

    FgOnlyTask m_FgTask;
};

} // end of namespace boss
} // end of namespace nn

#endif // __cplusplus
#endif /* NN_BOSS_BOSS_NSALIST_H_ */
