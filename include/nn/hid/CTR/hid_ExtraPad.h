/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hid_ExtraPad.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_HID_CTR_HID_EXTRAPAD_H_
#define NN_HID_CTR_HID_EXTRAPAD_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/hid/CTR/hid_ExtraPadStatus.h>
#include <nn/hid/CTR/hid_HidBase.h>
#include <nn/os.h>

/*
 *
 */
namespace nn {
namespace hid {
namespace CTR {

const size_t EXTRA_PAD_WORKING_MEMORY_SIZE = 4096;

/* Please see man pages for details 
    
    
           
           
    
*/

class ExtraPad
{
public:
    /* Please see man pages for details 
      
      
    */
    typedef enum{
        /* Please see man pages for details */
        CONNECTION_STATE_NO_CONNECTION,
        /* Please see man pages for details */
        CONNECTION_STATE_CONNECTED,
        /* Please see man pages for details */
        CONNECTION_STATE_STOPPED
    }ConnectionState;

public:
    /* Please see man pages for details 
      
      
     */

    /* Please see man pages for details 
      

              
              
              


              
     */
    static void Initialize(void* workingMemory);

    /* Please see man pages for details 
      
      
              
     */
    static void Finalize();

    /*  

*/


    /* Please see man pages for details 
      
      
     */

    /* Please see man pages for details 
      

      
      
      

      
                                          
      
                                          

      

      
      
      
      

     */
    static nn::Result StartSampling(s32 samplingThreadPriority,s32 period);

    /* Please see man pages for details 
      

      

      
      


     */
    static nn::Result StopSampling();

    /*  

*/

    /* Please see man pages for details 
      
      
     */


    /* Please see man pages for details 
      

      

      
      
     */
    static bool IsSampling();


    /* Please see man pages for details 
      

      

      
      
      
     */
    static ConnectionState GetConnectionState();

    /* Please see man pages for details 
      

      

      
     */
    static void RegisterConnectionEvent(nn::os::LightEvent* pLightEvent);


    /* Please see man pages for details 
      

      
     */
    static void UnregisterConnectionEvent();

    /* Please see man pages for details 
      
                    
                    

      

      
     */
    static void RegisterSamplingEvent(nn::os::LightEvent *pLightEvent);

    /* Please see man pages for details 
      

      
     */
    static void UnregisterSamplingEvent();



    /*  

*/

    /* Please see man pages for details 
       
       
     */


    /* Please see man pages for details 
     
     
     */
    static uptr GetResource();


    /*  

*/

private:
    ExtraPad();
    virtual ~ExtraPad();

};

}

}

}

#endif /* NN_HID_CTR_HID_EXTRAPAD_H_ */
