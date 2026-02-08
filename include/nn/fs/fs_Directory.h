/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_Directory.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_DIRECTORY_H_
#define NN_FS_FS_DIRECTORY_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_DirectoryBase.h>

#include <nn/fs/fs_DirectoryBase.h>

namespace nn {
namespace fs {

/* Please see man pages for details 
    

    

            
            

            
            
            
            
*/
class Directory : private nn::util::NonCopyable<Directory>, private detail::DirectoryBase
{
public:

    /* Please see man pages for details 
        

        

                
                

                
    */
    Directory() {}

    /* Please see man pages for details 
        

        

                

        
    */
    explicit Directory( const wchar_t* pathName ) : DirectoryBase(pathName) {}

    /* Please see man pages for details 
        

        

                

                
                

        
    */
    explicit Directory( const char* pathName ) : DirectoryBase(pathName) {}

    /* Please see man pages for details 
        

        


                

        
    */
    void Initialize( const wchar_t* pathName ) { DirectoryBase::Initialize(pathName); }

    /* Please see man pages for details 
        

        

                
                

                
                

        
    */
    void Initialize( const char* pathName ) { DirectoryBase::Initialize(pathName); }

    /* Please see man pages for details 
        

        

                
                

        

        
    */
    Result TryInitialize( const wchar_t* pathName ) { return DirectoryBase::TryInitialize(pathName); }

    /* Please see man pages for details 
        

        

                
                

                
                

        

        
    */
    Result TryInitialize( const char* pathName ) { return DirectoryBase::TryInitialize(pathName); }

    /* Please see man pages for details 
        

                
    */
    void Finalize() { DirectoryBase::Finalize(); }

    /* Please see man pages for details 
        

                
    */
    virtual ~Directory() {}

    /* Please see man pages for details 
        

                
                

         
         

         
    */
    s32 Read( DirectoryEntry pEntries[], s32 numEntries ) { return DirectoryBase::Read(pEntries, numEntries); }

    /* Please see man pages for details 
        

                
                

         
         
         

         
    */
    Result TryRead( s32* pNumEntriesOut, DirectoryEntry pEntries[], s32 numEntries ) { return DirectoryBase::TryRead(pNumEntriesOut, pEntries, numEntries); }

    /* Please see man pages for details 
        

                    

        

        
    */
    void SetPriority(s32 priority) { detail::DirectoryBase::SetPriority(priority); }

    /* Please see man pages for details 
        

                    

        

        
    */
    Result TrySetPriority(s32 priority) { return detail::DirectoryBase::TrySetPriority(priority); }


    /* Please see man pages for details 
        
        
        

                    
                    

        
    */
    void GetPriority(s32* pOut) const { detail::DirectoryBase::GetPriority(pOut); }

    /* Please see man pages for details 
        
        
        

                    
                    

        

        
    */
    Result TryGetPriority(s32* pOut) const { return detail::DirectoryBase::TryGetPriority(pOut); }
};

} // end of namespace fs
} // end of namespace nn

#endif  // ifndef NN_FS_FS_DIRECTORY_H_
