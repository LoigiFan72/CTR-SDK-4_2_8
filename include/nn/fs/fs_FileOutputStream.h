/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileOutputStream.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILEOUTPUTSTREAM_H_
#define NN_FS_FS_FILEOUTPUTSTREAM_H_

#include <nn/fs/fs_IOutputStream.h>
#include <nn/fs/fs_FileBase.h>
#include <nn/fnd/fnd_Storage.h>

namespace nn { namespace fs {

/* Please see man pages for details 
    

    

            

            

            













            

            
            
*/
class FileOutputStream : public IOutputStream, public detail::FileBase, private nn::util::NonCopyable<FileOutputStream>
{
public:

    /* Please see man pages for details 
        

        

                

                

    */
    FileOutputStream() {}

    /* Please see man pages for details 
        

        


                
                

        
        
    */
    FileOutputStream(const wchar_t* pathName, bool createIfNotExist) :
        detail::FileBase(pathName, OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)) {}

    /* Please see man pages for details 
        

        


                
                

                
                

        
        
    */
    FileOutputStream(const char* pathName, bool createIfNotExist) :
        detail::FileBase(pathName, OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)) {}

    /* Please see man pages for details 
        

        

                

                
                

        
        
    */
    void Initialize(const wchar_t* pathName, bool createIfNotExist)
    { detail::FileBase::Initialize(pathName,  OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)); }

    /* Please see man pages for details 
        

        

                

                
                

                
                

        
        
    */
    void Initialize(const char* pathName, bool createIfNotExist)
    { detail::FileBase::Initialize(pathName,  OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)); }

    /* Please see man pages for details 
        

        

                
                
                

                
                

        
        

        
    */
    nn::Result TryInitialize(const wchar_t* pathName, bool createIfNotExist)
    { return detail::FileBase::TryInitialize(pathName,  OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)); }

    /* Please see man pages for details 
        

        

                
                
                



                
                

        
        

        
    */
    nn::Result TryInitialize(const char* pathName, bool createIfNotExist)
    { return detail::FileBase::TryInitialize(pathName,  OPEN_MODE_WRITE | (createIfNotExist ? OPEN_MODE_CREATE : 0)); }

    /* Please see man pages for details 
        




                
    */
    void Finalize() { detail::FileBase::Finalize(); }

    /* Please see man pages for details 
        




                
    */
    virtual ~FileOutputStream() {}

    /* Please see man pages for details 
        

                

                
                

                
                


         
         


         

         
    */
    virtual s32 Write(const void* buffer, size_t size, bool flush) { return detail::FileBase::Write(buffer, size, flush); }

    /* Please see man pages for details 
        

                

                
                
                
                
                

         
         



         
         

         
    */
    virtual Result TryWrite(s32* pOut, const void* buffer, size_t size, bool flush) { return detail::FileBase::TryWrite(pOut, buffer, size, flush); }

    /* Please see man pages for details 
        

                

                
                

        
        
    */
    virtual void Seek(s64 position, PositionBase base) { detail::FileBase::Seek(position, base); }

    /* Please see man pages for details 
        
        
                

        
        
        
        
    */
    virtual Result TrySeek(s64 position, PositionBase base) { return detail::FileBase::TrySeek(position, base); }

    /* Please see man pages for details 
        

        
    */
    virtual s64 GetPosition() const { return detail::FileBase::GetPosition(); }
    
    /* Please see man pages for details 
        

        

        
    */
    virtual Result TryGetPosition(s64* pOut) const { return detail::FileBase::TryGetPosition(pOut); }

    /* Please see man pages for details 
        

        
    */
    virtual void SetPosition(s64 position) { detail::FileBase::SetPosition(position); }

    /* Please see man pages for details 
        

        

        
    */
    virtual Result TrySetPosition(s64 position) { return detail::FileBase::TrySetPosition(position); }

    /* Please see man pages for details 
        

        
    */
    virtual s64 GetSize() const { return detail::FileBase::GetSize(); }

    /* Please see man pages for details 
        

        

        
    */
    virtual Result TryGetSize(s64* pOut) const { return detail::FileBase::TryGetSize(pOut); }

    /* Please see man pages for details 
        

        
     */
    virtual void SetSize(s64 size) { detail::FileBase::SetSize(size); }

    /* Please see man pages for details 
        

        

        
     */
    virtual Result TrySetSize(s64 size) { return detail::FileBase::TrySetSize(size); }

    /* Please see man pages for details 
        

     */
    virtual void Flush() { detail::FileBase::Flush(); }

    /* Please see man pages for details 
        

        
     */
    virtual Result TryFlush() { return detail::FileBase::TryFlush(); }

    /* Please see man pages for details 
        

                    



        
    */
    void SetPriority(s32 priority) { detail::FileBase::SetPriority(priority); }

    /* Please see man pages for details 
        

                    



        

        
    */
    Result TrySetPriority(s32 priority) { return detail::FileBase::TrySetPriority(priority); }


    /* Please see man pages for details 
        
        
        

                    
                    

        
    */
    void GetPriority(s32* pOut) const { detail::FileBase::GetPriority(pOut); }

    /* Please see man pages for details 
        
        
        

                    
                    

        

        
    */
    Result TryGetPriority(s32* pOut) const { return detail::FileBase::TryGetPriority(pOut); }
};

}}

#endif
