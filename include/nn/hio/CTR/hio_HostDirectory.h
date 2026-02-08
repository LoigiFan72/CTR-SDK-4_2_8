/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     hio_HostDirectory.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HIO_CTR_HIO_HOSTDIRECTORY_H_
#define NN_HIO_CTR_HIO_HOSTDIRECTORY_H_
#ifdef  NN_SWITCH_ENABLE_HOST_IO

/* Please see man pages for details 

    

    
*/


#include <nn/types.h>
#include <nn/Result.h>
#include <nn/config.h>
#include <wchar.h>

namespace nn {
namespace hio {
namespace CTR {

    const int MAX_PATH = 260;   //

    /* Please see man pages for details 
    
    */
    struct HostSystemTime
    {
        bit16   year;       //
        bit16   month;      //
        bit16   dayofweek;  //
        bit16   day;        //
        bit16   hour;       //
        bit16   minute;     //
        bit16   second;     //
        bit16   msec;       //
    };

    /* Please see man pages for details 
    

    */
    enum FileAttribute
    {
        /* Please see man pages for details */
        FILE_ATTRIBUTE_READ_ONLY    = (1u << 0),
        /* Please see man pages for details */
        FILE_ATTRIBUTE_DIRECTORY    = (1u << 4)
    };

    class HostSystemChannel;

    //--------------------------------------------------
    // A

    /* Please see man pages for details 
    
    
    */
    struct DirectoryEntryA
    {
        s64             fileSize;           //
        bit32           fileAttributes;     //
        HostSystemTime  creationTime;       //
        HostSystemTime  lastAccessTime;     //
        HostSystemTime  lastWriteTime;      //
        char            filename[MAX_PATH]; //
    };

    /* Please see man pages for details 
    

    */
    class HostDirectoryA
    {
    private:
        s32                 m_Fd;
        NN_PADDING4;
        DirectoryEntryA     m_NextEntry;

    public:
        /* Please see man pages for details 
          

        */
        HostDirectoryA() : m_Fd(-1)
        {
        }
        

        /* Please see man pages for details 
          

        */
        ~HostDirectoryA()
        {
            if( m_Fd > 0 )
            {
                Close();
            }
        }

        /* Please see man pages for details 
          
                        
          
          
          

        */
        Result Open(const char* path);

        /* Please see man pages for details 
          

          

        */
        Result Close();


        /* Please see man pages for details 
          
          
          
          

        */
        Result GetNextEntry(DirectoryEntryA* pEntry);
    };



    //--------------------------------------------------
    // W


    /* Please see man pages for details 
    
    */
    struct DirectoryEntryW
    {
        s64             fileSize;           //
        bit32           fileAttributes;     //
        HostSystemTime  creationTime;       //
        HostSystemTime  lastAccessTime;     //
        HostSystemTime  lastWriteTime;      //
        wchar_t         filename[MAX_PATH]; //
        NN_PADDING4;
    };

    /* Please see man pages for details 
    
    */
    class HostDirectoryW
    {
    private:
        s32                 m_Fd;
        NN_PADDING4;
        DirectoryEntryW     m_NextEntry;

    public:
        /* Please see man pages for details 
          
        */
        HostDirectoryW() : m_Fd(-1)
        {
        }
        
        /* Please see man pages for details 
          
        */
        ~HostDirectoryW()
        {
            if( m_Fd > 0 )
            {
                Close();
            }
        }

        /* Please see man pages for details 
          
                        
          
          
          

        */
        Result Open(const wchar_t* path);
        
        /* Please see man pages for details 
          

          

        */
        Result Close();

        /* Please see man pages for details 
          
          
          
          

        */
        Result GetNextEntry(DirectoryEntryW* pEntry);
    };

}
}
}


#endif  // ifdef NN_SWITCH_ENABLE_HOST_IO
#endif  // ifndef NN_HIO_CTR_HIO_HOSTDIRECTORY_H_
