/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_API_H_
#define NN_HIO_CTR_HIO_API_H_
#ifdef  NN_SWITCH_ENABLE_HOST_IO

/* Please see man pages for details 
    
    
*/

#include <nn/types.h>
#include <nn/Result.h>

namespace nn {
namespace hio {
namespace CTR {

//
const size_t WORKMEMORY_SIZE    = (80 * 1024 + 32);

//
const size_t MAX_CHANNEL_NUM    = 12;

/* Please see man pages for details 
  

  
*/

/* Please see man pages for details 




            

*/
Result Initialize(void* pDeviceMemory);


/* Please see man pages for details 


*/
Result Finalize();

/*  

*/

/* Please see man pages for details 



*/
Result GetHioDaemonStatus(bool* pIsRunning);

/* Please see man pages for details 


*/
s32 GetVersion();

/* Please see man pages for details 




                    




*/
Result DeleteFile(const char* path);

/* Please see man pages for details 




                    
                    
                    




*/
Result DeleteFile(const wchar_t* path);

/* Please see man pages for details 




                    
                    





*/
Result DeleteDirectory(const char* path);

/* Please see man pages for details 




                    
                    
                    
                    




*/
Result DeleteDirectory(const wchar_t* path);

/* Please see man pages for details 




                    





*/
Result CreateDirectory(const char* path);

/* Please see man pages for details 




                    
                    
                    




*/
Result CreateDirectory(const wchar_t* path);


/* Please see man pages for details 




                    






*/
Result Rename(const char* newName, const char* oldName);


/* Please see man pages for details 




                    
                    
                    





*/
Result Rename(const wchar_t* newName, const wchar_t* oldName);

/* Please see man pages for details 




                    







*/
Result GetCurrentDirectory(s32* pLength, char* buf, s32 length);


/* Please see man pages for details 




                    
                    
                    






*/
Result GetCurrentDirectory(s32* pLength, wchar_t* buf, s32 length);

/* Please see man pages for details 




                    






*/
s32 GetCurrentDirectory(char* buf, s32 length);

/* Please see man pages for details 




                    
                    






*/
s32 GetCurrentDirectory(wchar_t* buf, s32 length);

/* Please see man pages for details 



                    
                    





*/
Result SetCurrentDirectory(const char* path);

/* Please see man pages for details 



                    
                    
                    
                    




*/
Result SetCurrentDirectory(const wchar_t* path);

/* Please see man pages for details 




                    
                    








*/
Result GetEnvironmentVariable(s32* pLength, char* buf, s32 length, const char* name);

/* Please see man pages for details 




                    
                    







*/
s32 GetEnvironmentVariable(char* buf, size_t length, const char* name);




/* Please see man pages for details 




                    
                    
                    








*/
Result GetEnvironmentVariable(s32* pLength, wchar_t* buf, s32 length, const wchar_t* name);


/* Please see man pages for details 




                    
                    
                    







*/
s32 GetEnvironmentVariable(wchar_t* buf, s32 length, const wchar_t* name);




}
}
}


#endif  // ifdef NN_SWITCH_ENABLE_HOST_IO
#endif  // ifndef NN_HIO_CTR_HIO_API_H_
