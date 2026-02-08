/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     midi_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MIDI_CTR_MIDI_API_H_
#define NN_MIDI_CTR_MIDI_API_H_

/* Please see man pages for details 
    
    
*/

#include <nn/types.h>
#include <nn/Result.h>
#include <nn/midi/CTR/midi_Types.h>

namespace nn {
namespace midi {
namespace CTR {

/* Please see man pages for details 
  

  
*/

/* Please see man pages for details 



*/
void Initialize();


/* Please see man pages for details 


*/
void Finalize();

/*  

*/

/* Please see man pages for details 







                             
                             

*/
Result Open();

/* Please see man pages for details 







*/
Result Close();

/* Please see man pages for details 

                    





                             

                             
                             

*/
Result Reset();

/* Please see man pages for details 







                             
                             

*/
Result GetDeviceInfo(DeviceInfo* pInfo);

/* Please see man pages for details 







                             

                             
                             
                             
                             

*/
Result GetReadableLength(s32* pSize);

/* Please see man pages for details 








                             

                             
                             
                             
                             
*/
Result Read(void* pBuf, s32* pReadSize, s32 bufferSize);





}
}
}


#endif  // ifndef NN_MIDI_CTR_MIDI_API_H_
