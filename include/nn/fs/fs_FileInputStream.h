/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileInputStream.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILEINPUTSTREAM_H_
#define NN_FS_FS_FILEINPUTSTREAM_H_

#include <nn/fs/fs_IInputStream.h>
#include <nn/fs/fs_FileBase.h>
#include <nn/fnd/fnd_Storage.h>

namespace nn { namespace fs {

/* Please see man pages for details 
    

    

            

            
            
            
            
*/
class FileInputStream : public IInputStream, public detail::FileBase, private nn::util::NonCopyable<FileInputStream>
{
public:
    
    /* Please see man pages for details 
        

        

                

                
    */
    FileInputStream() {}
    
    /* Please see man pages for details 
        

        

                

        
    */
    explicit FileInputStream(const wchar_t* pathName) : detail::FileBase(pathName, OPEN_MODE_READ) {}
    
    /* Please see man pages for details 
        

        

                

                
                

        
    */
    explicit FileInputStream(const char* pathName) : detail::FileBase(pathName, OPEN_MODE_READ) {}
    
    /* Please see man pages for details 
        

        

                
                

        
    */
    void Initialize(const wchar_t* pathName) { detail::FileBase::Initialize(pathName, OPEN_MODE_READ); }
    
    /* Please see man pages for details 
        

        

                
                

                
                

        
    */
    void Initialize(const char* pathName) { detail::FileBase::Initialize(pathName, OPEN_MODE_READ); }
    
    /* Please see man pages for details 
        

        

                
                

                

        

        
    */
    Result TryInitialize(const wchar_t* pathName) { return detail::FileBase::TryInitialize(pathName, OPEN_MODE_READ); }
    
    /* Please see man pages for details 
        

        
        
                
                

                

                
                

        

        
    */
    Result TryInitialize(const char* pathName) { return detail::FileBase::TryInitialize(pathName, OPEN_MODE_READ); }
    
    /* Please see man pages for details 
        

                
    */
    void Finalize() { detail::FileBase::Finalize(); }
    
    /* Please see man pages for details 
        

                
    */
    virtual ~FileInputStream() {}
    
    /* Please see man pages for details 
        

                
                
                
                

         
         

         
    */
    virtual s32 Read(void* buffer, size_t size) { return detail::FileBase::Read(buffer, size); }
    
    /* Please see man pages for details 
        

                
                
                
                

         
         
         

         
    */
    virtual Result TryRead(s32* pOut, void* buffer, size_t size) { return detail::FileBase::TryRead(pOut, buffer, size); }
    
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
