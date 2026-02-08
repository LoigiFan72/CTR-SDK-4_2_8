/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_HostFile.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_HOSTFILE_H_
#define NN_HIO_CTR_HIO_HOSTFILE_H_
#ifdef  NN_SWITCH_ENABLE_HOST_IO

/* Please see man pages for details 
    
   
    

*/

#include <nn/types.h>

namespace nn {
namespace hio {
namespace CTR {

    class HostSystemChannel;


    /* Please see man pages for details 
    
            
    */
    class HostFile
    {
    public:
        /* Please see man pages for details 
        

        */
        enum SeekType
        {
            SEEK_TYPE_SET,          //
            SEEK_TYPE_CURRENT,      //
            SEEK_TYPE_END           //
        };
        
        /* Please see man pages for details 
        

        */
        enum AccessMode
        {
            ACCESS_MODE_READ        = (1u << 31),                           //
            ACCESS_MODE_WRITE       = (1u << 30),                           //
            ACCESS_MODE_READ_WRITE  = (ACCESS_MODE_READ|ACCESS_MODE_WRITE)  //
        };
        
        
        /* Please see man pages for details 
        

        */
        enum OpenDisp
        {
            OPEN_DISP_CREATE_NEW        = 1,    //
            OPEN_DISP_CREATE_ALWAYS     = 2,    //
            OPEN_DISP_OPEN_EXISTING     = 3,    //
            OPEN_DISP_OPEN_ALWAYS       = 4     //
        };

    private:
        int                 m_Fd;

    public:
        /* Please see man pages for details 
          

        */
        HostFile() : m_Fd(-1) {}

        /* Please see man pages for details 
          

        */
        ~HostFile()
        {
            if( m_Fd >= 0 )
            {
                Close();
            }
        }

        /* Please see man pages for details 
          

          

                        
                        
                        
                        
          
          
          
          

        */
        Result Open(const char* path, bit32 accessMode, OpenDisp disp);


        /* Please see man pages for details 
          
          
          

                        
                        
                        
                        
                        
          
          
          
          
          
        */
        Result Open(const wchar_t* path, bit32 accessMode, OpenDisp disp);

        /* Please see man pages for details 
          

          

        */
        Result Close();

        /* Please see man pages for details 
          

          

                        
                        
          
          
          
          
          

        */
        Result Read(size_t* pRead, void* buf, size_t size);

        /* Please see man pages for details 
          

          

                        
                        
          
          
          
          

        */
        s32 Read(void* buf, size_t size)
        {
            size_t read;
            return Read(&read, buf, size).IsFailure() ? -1: static_cast<s32>(read);
        }

        /* Please see man pages for details 
          

          

                        
                        
          
          
          
          
          

        */
        Result Write(size_t* pWritten, const void* buf, size_t size);

        /* Please see man pages for details 
          

          

                        
                        
                        
          
          
          

        */
        s32 Write(const void* buf, size_t size)
        {
            size_t written;
            return Write(&written, buf, size).IsFailure() ? -1: static_cast<s32>(written);
        }
        
        /* Please see man pages for details 
          

          

                        
                        

          
          
          
          

        */
        Result Seek(s64* pPosition, s64 offset, SeekType type);
        
        /* Please see man pages for details 
          

          

                        
                        

          
          
          

        */
        s64 Seek(s64 offset, SeekType type)
        {
            s64 pos;
            return Seek(&pos, offset, type).IsFailure() ? -1: pos;
        }

        /* Please see man pages for details 
          
          
          
          

        */
        Result SetSize(s64 size);


        /* Please see man pages for details 
          
          
          

                        
          
          
          
          

        */
        Result Exists(bool *exist, const char* path);

        /* Please see man pages for details 
          

          


                        
                        
          
          
          
          

        */
        Result Exists(bool *exist, const wchar_t* path);
    };

}
}
}


#endif  // ifdef NN_SWITCH_ENABLE_HOST_IO
#endif  // ifndef NN_HIO_CTR_HIO_HOSTFILE_H_
