/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileSystem.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_FS_FILESYSTEM_H_
#define NN_FS_FS_FILESYSTEM_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>
#include <nn/util/util_Result.h>
#include <nn/fs/fs_Parameters.h>
#include <nn/fs/fs_FileSystemBase.h>

/* Please see man pages for details 
    
*/

namespace nn {
namespace fs {

//----------------------------------------
//
//

/* Please see man pages for details 
  

  
*/
void DeleteFile( const wchar_t* pathName );

/* Please see man pages for details 
  

                
                

  
*/
void DeleteFile( const char* pathName );

/* Please see man pages for details 
  

                

  

  
*/
Result TryDeleteFile( const wchar_t* pathName );

/* Please see man pages for details 
  

                

                
                
                


  
*/
Result TryDeleteFile( const char* pathName );

/* Please see man pages for details 
  

  
  
*/
void RenameFile( const wchar_t* currentPath, const wchar_t* newPath);

/* Please see man pages for details 
  


                

  
  
*/
void RenameFile( const char* currentPath, const char* newPath);

/* Please see man pages for details 
  

                

  
  

  
*/
Result TryRenameFile( const wchar_t* currentPath, const wchar_t* newPath);

/* Please see man pages for details 
  

                

                
                
                

  
  

*/
Result TryRenameFile( const char* currentPath, const char* newPath);

/* Please see man pages for details 
  

  
*/
void DeleteDirectory( const wchar_t* pathName );

/* Please see man pages for details 
  

                
                

  
*/
void DeleteDirectory( const char* pathName );

/* Please see man pages for details 
  

                

  

  
*/
Result TryDeleteDirectory( const wchar_t* pathName );

/* Please see man pages for details 
  

                


                

  

  
*/
Result TryDeleteDirectory( const char* pathName );

/* Please see man pages for details 
  

                

  

  
*/
Result TryDeleteDirectoryRecursively( const wchar_t* pathName );

/* Please see man pages for details 
  

                
                
                

  

  
*/
Result TryDeleteDirectoryRecursively( const char* pathName );

/* Please see man pages for details 
  

  
  
*/
void CreateFile( const wchar_t* pathName, s64 size );

/* Please see man pages for details 
  

                
                

  
  
*/
void CreateFile( const char* pathName, s64 size );

/* Please see man pages for details 
  

                

                
                

  
  

  
*/
Result TryCreateFile( const wchar_t* pathName, s64 size );

/* Please see man pages for details 
  

                


                

                
                

  
  

  
*/
Result TryCreateFile( const char* pathName, s64 size );

/* Please see man pages for details 
  

  
*/
void CreateDirectory( const wchar_t* pathName );

/* Please see man pages for details 
  

                
                

  
*/
void CreateDirectory( const char* pathName );

/* Please see man pages for details 
  

                

  

  
*/
Result TryCreateDirectory( const wchar_t* pathName );

/* Please see man pages for details 
  

                


                

  

  
*/
Result TryCreateDirectory( const char* pathName );

/* Please see man pages for details 
  

  
  
*/
void RenameDirectory( const wchar_t* currentPath, const wchar_t* newPath);

/* Please see man pages for details 
  


                

  
  
*/
void RenameDirectory( const char* currentPath, const char* newPath);

/* Please see man pages for details 
  

                

  
  

  
*/
Result TryRenameDirectory( const wchar_t* currentPath, const wchar_t* newPath);

/* Please see man pages for details 
  

                

                
                

  
  

  
*/
Result TryRenameDirectory( const char* currentPath, const char* newPath);

//

inline void DeleteFile(const wchar_t* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteFile(pathName);
}
inline void DeleteFile(const char* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteFile(pathName);
}
inline Result TryDeleteFile(const wchar_t* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteFile(pathName);
}
inline Result TryDeleteFile(const char* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteFile(pathName);
}

inline void RenameFile( const wchar_t* currentPath, const wchar_t* newPath)
{
    detail::GetGlobalFileSystemBase().RenameFile(currentPath, newPath);
}
inline void RenameFile( const char* currentPath, const char* newPath)
{
    detail::GetGlobalFileSystemBase().RenameFile(currentPath, newPath);
}
inline Result TryRenameFile( const wchar_t* currentPath, const wchar_t* newPath)
{
    return detail::GetGlobalFileSystemBase().TryRenameFile(currentPath, newPath);
}
inline Result TryRenameFile( const char* currentPath, const char* newPath)
{
    return detail::GetGlobalFileSystemBase().TryRenameFile(currentPath, newPath);
}

inline void DeleteDirectory(const wchar_t* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteDirectory(pathName);
}
inline void DeleteDirectory(const char* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteDirectory(pathName);
}
inline void DeleteDirectoryRecursively(const wchar_t* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteDirectoryRecursively(pathName);
}
inline void DeleteDirectoryRecursively(const char* pathName)
{
    detail::GetGlobalFileSystemBase().DeleteDirectoryRecursively(pathName);
}
inline Result TryDeleteDirectory(const wchar_t* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteDirectory(pathName);
}
inline Result TryDeleteDirectory(const char* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteDirectory(pathName);
}
inline Result TryDeleteDirectoryRecursively(const wchar_t* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteDirectoryRecursively(pathName);
}
inline Result TryDeleteDirectoryRecursively(const char* pathName)
{
    return detail::GetGlobalFileSystemBase().TryDeleteDirectoryRecursively(pathName);
}

inline void CreateFile(const wchar_t* pathName, s64 size)
{
    detail::GetGlobalFileSystemBase().CreateFile(pathName, size);
}
inline void CreateFile(const char* pathName, s64 size)
{
    detail::GetGlobalFileSystemBase().CreateFile(pathName, size);
}
inline Result TryCreateFile(const wchar_t* pathName, s64 size)
{
    return detail::GetGlobalFileSystemBase().TryCreateFile(pathName, size);
}
inline Result TryCreateFile(const char* pathName, s64 size)
{
    return detail::GetGlobalFileSystemBase().TryCreateFile(pathName, size);
}

inline void CreateDirectory(const wchar_t* pathName)
{
    detail::GetGlobalFileSystemBase().CreateDirectory(pathName);
}
inline void CreateDirectory(const char* pathName)
{
    detail::GetGlobalFileSystemBase().CreateDirectory(pathName);
}
inline Result TryCreateDirectory(const wchar_t* pathName)
{
    return detail::GetGlobalFileSystemBase().TryCreateDirectory(pathName);
}
inline Result TryCreateDirectory(const char* pathName)
{
    return detail::GetGlobalFileSystemBase().TryCreateDirectory(pathName);
}

inline void RenameDirectory( const wchar_t* currentPath, const wchar_t* newPath)
{
    detail::GetGlobalFileSystemBase().RenameDirectory(currentPath, newPath);
}
inline void RenameDirectory( const char* currentPath, const char* newPath)
{
    detail::GetGlobalFileSystemBase().RenameDirectory(currentPath, newPath);
}
inline Result TryRenameDirectory( const wchar_t* currentPath, const wchar_t* newPath)
{
    return detail::GetGlobalFileSystemBase().TryRenameDirectory(currentPath, newPath);
}
inline Result TryRenameDirectory( const char* currentPath, const char* newPath)
{
    return detail::GetGlobalFileSystemBase().TryRenameDirectory(currentPath, newPath);
}

}
}
#endif  // ifndef NN_FS_FS_FILESYSTEM_H_
