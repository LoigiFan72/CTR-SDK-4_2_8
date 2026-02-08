/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_SharedMemoryChannel.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_SHAREDMEMORYCHANNEL_H_
#define NN_HIO_CTR_HIO_SHAREDMEMORYCHANNEL_H_
#ifdef  NN_SWITCH_ENABLE_HOST_IO

/* Please see man pages for details 
    

    

*/


#include <nn/types.h>

namespace nn {
namespace hio {
namespace CTR {

    /* Please see man pages for details 
    

                

                
    */
    class SharedMemoryChannel
    {
    private:
        s32     m_Ch;

    public:
        /* Please see man pages for details 
        
        */
        SharedMemoryChannel() : m_Ch(-1) {}

        /* Please see man pages for details 
        
        */
        ~SharedMemoryChannel()
        {
            if( m_Ch >= 0 )
            {
                Close();
            }
        }

        /* Please see man pages for details 
        

        
        

        
        */
        Result Open(int ch, void* pWorkMemory);


        /* Please see man pages for details 
        

        

        */
        Result Close();

        /* Please see man pages for details 
        

        

        */
        size_t GetSpaceSize();


        /* Please see man pages for details 
        

                                
                                
        
        
        

        
        */
        Result Read(void* buf, size_t length, int offset);


        /* Please see man pages for details 
        

                                

        
        
        

        
        */
        Result Write(const void* buf, size_t length, int offset);
    };

}
}
}


#endif  // ifdef NN_SWITCH_ENABLE_HOST_IO
#endif  // ifndef NN_HIO_CTR_HIO_SHAREDMEMORYCHANNEL_H_
