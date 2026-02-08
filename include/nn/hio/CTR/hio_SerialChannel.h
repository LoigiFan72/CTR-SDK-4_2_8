/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_SerialChannel.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_SERIALCHANNEL_H_
#define NN_HIO_CTR_HIO_SERIALCHANNEL_H_
#ifdef  NN_SWITCH_ENABLE_HOST_IO

/* Please see man pages for details 
    
  
    
*/

#include <nn/types.h>

namespace nn {
namespace hio {
namespace CTR {

    /* Please see man pages for details 
    

                

                
                
    */
    class SerialChannel
    {
    public:
        /* Please see man pages for details 
        
        */
        enum Attribute
        {
            ATTRIBUTE_NONE      = 0,            //
            ATTRIBUTE_NO_WAIT   = (1u << 0),    //
            ATTRIBUTE_IN_PC     = (1u << 1)     //
        };

    private:
        s32     m_Ch;

    public:
        /* Please see man pages for details 
        
        */
        SerialChannel() : m_Ch(-1) {}

        /* Please see man pages for details 
        
        */
        ~SerialChannel()
        {
            if( m_Ch >= 0 )
            {
                Close();
            }
        }

        /* Please see man pages for details 
        

        
        

        

        */
        Result Open(s32 ch, void* pWorkMemory);


        /* Please see man pages for details 
        

        

        */
        Result Close();

        /* Please see man pages for details 
        
                                

        
        */
        Result Connect();


        /* Please see man pages for details 
        

        
                                
                                
                                
        

        

        

        */
        Result WaitHost(bit32 attr=ATTRIBUTE_NONE);


        /* Please see man pages for details 
        

        

        */
        Result Disconnect();

        /* Please see man pages for details 
        
                                

        
        */
        Result Flush();


        /* Please see man pages for details 
        

        
                                
        
        
                                
                                

        
        */
        Result GetReadableSize(size_t* pSize, bit32 attr=ATTRIBUTE_NONE);


        /* Please see man pages for details 
        

        
        
                                
                                
                                
                                
        
        
        
        
                                
                                

        
        */
        Result Read(size_t* pReadSize, void* buf, size_t size, bit32 attr=ATTRIBUTE_NONE);

        /* Please see man pages for details 
        

        

                                
                                
                                
                                
        
        
        
                                
                                

        
        */
        s32 Read(void* buf, size_t size, bit32 attr=ATTRIBUTE_NONE)
        {
            size_t read;
            return Read(&read, buf, size, attr).IsFailure() ? -1: static_cast<s32>(read);
        }

        /* Please see man pages for details 
        

        
                                
        
        
                                
                                

        
        */
        Result GetWritableSize(size_t* pSize, bit32 attr=ATTRIBUTE_NONE);

        /* Please see man pages for details 
        

        

                                
                                
                                

                                
        
        
        
        
                                    
                                    

        
        */
        Result Write(size_t* pWrittenSize, const void* buf, size_t size, bit32 attr=ATTRIBUTE_NONE);

        /* Please see man pages for details 
        

        

                                
                                
                                
                                
        
        
        
                                
                                

        
        */
        s32 Write(const void* buf, size_t size, bit32 attr=ATTRIBUTE_NONE)
        {
            size_t written;
            return Write(&written, buf, size,  attr).IsFailure() ? -1: static_cast<s32>(written);
        }
    };

    /* Please see man pages for details 
        
        
    */
    nn::Result ResultNoConnected();

    /* Please see man pages for details 
        
        
    */
    nn::Result ResultConnected();

    inline nn::Result ResultNoConnected()
    {
        return nn::Result(nn::Result::LEVEL_SUCCESS, nn::Result::SUMMARY_SUCCESS, nn::Result::MODULE_COMMON, 0);
    }

    inline nn::Result ResultConnected()
    {
        return nn::Result(nn::Result::LEVEL_SUCCESS, nn::Result::SUMMARY_SUCCESS, nn::Result::MODULE_COMMON, 1);
    }

}
}
}


#endif  // ifdef NN_SWITCH_ENABLE_HOST_IO
#endif  // ifndef NN_HIO_CTR_HIO_SERIALCHANNEL_H_
