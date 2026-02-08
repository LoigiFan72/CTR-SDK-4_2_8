/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fs_FileSystemBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48204 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FS_CTR_MPCORE_FS_FILESYSTEMBASE_H_
#define NN_FS_CTR_MPCORE_FS_FILESYSTEMBASE_H_

#include <nn/Handle.h>
#include <nn/fs/CTR/MPCore/fs_UserFileSystem.h>

namespace nn { namespace fs { namespace detail {

class FileSystemBaseImpl : public nn::fs::CTR::MPCore::detail::UserFileSystem
{
};

}}}

namespace nn { namespace fs {

//----------------------------------------
//
//

/* Please see man pages for details 
    

                
                
                
                

    
    
    

    
*/
s32 GetRomRequiredMemorySize(size_t maxFile, size_t maxDirectory, bool useCache = true);

/* Please see man pages for details 
    

                
                
                

                
                
                

    
    
    
    
    
    

    
    
    
                                    
    
                                    
    
                                    
    
*/
Result MountRom(const char* archiveName, size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize, bool useCache = true);
Result MountRom(size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize, bool useCache = true);

//

//----------------------------------------
//
//

/* Please see man pages for details 
    

                
                

                
                

                
                

    
    
    

    
    
    
                                    
    
*/
Result FormatSaveData(size_t maxFiles, size_t maxDirectories, bool isDuplicateAll = false);

/* Please see man pages for details 
    

    
    
    

    
    
    
    
    
    
*/
Result GetSaveDataFormatInfo(size_t* maxFiles, size_t* maxDirectories, bool* isDuplicateAll);

/* Please see man pages for details 
    
    
    

                
                

                
                
                

    

    
    
    
                                        
    
                                        
    
    
    
    
*/
Result MountSaveData(const char* archiveName = "data:");

Result MountSaveData(const char* archiveName, bit32 uniqueId, bit8 variation);

/* Please see man pages for details 
    
    
    
    
                
                
                
                
                
                
                
                
                

    
    

    
    
    
                                        
    
                                        
    
                                        
    
                                        
    
                                        
    
*/
Result MountSaveData(const char* archiveName, bit32 uniqueId);

/* Please see man pages for details 
    
    
                
                
                
                
                
                
                
                
                

    
    
    

    
    
    
                                        
    
                                        
    
                                        
    
                                        
    
                                        
    
*/
Result MountDemoSaveData(const char* archiveName, bit32 uniqueId, bit8 demoIndex);

/* Please see man pages for details 
    

                
                
                

                
                
                

    

    
    
    
                                
    
*/
Result CommitSaveData(const char* archiveName = "data:");

//

//----------------------------------------
//
//

/* Please see man pages for details 
    

                
                

                

                
                

                
                

    
    
    
    
    

    
    
    
    
    
    
    
    
    
*/
Result CreateExtSaveData(nn::fs::ExtSaveDataId id, const void* iconData, size_t iconDataSize, u32 entryDirectory, u32 entryFile);

/* Please see man pages for details 
    

                
                
                

    
    
    

    
    
    
                                        
    
                                        
    
    
    
*/
Result GetExtSaveDataFormatInfo(u32* entryDirectory, u32* entryFile, nn::fs::ExtSaveDataId id);

/* Please see man pages for details 
    

                

                
                
                

                
                
                

    
    

    
    
    
                                        
    
    
                                        
    
                                        
    
    
    
                                        
    
    
*/
Result MountExtSaveData(const char* archiveName, nn::fs::ExtSaveDataId id);

/* Please see man pages for details 
    

                

    

    
    
    
                                        
    
    
    
    
    
    
*/
Result DeleteExtSaveData(ExtSaveDataId id);


//

/* Please see man pages for details 
    

                

                

                
                

    

    
    
    
                                
    
*/
Result Unmount(const char* archiveName);

/* Please see man pages for details 
    
    
                
                
                
                
                
                
                
                
                
                
                

    
    

    
    
    
                                
    
*/
Result CreateArchiveAlias(const char* aliasArchiveName, const char* srcArchiveName);

//----------------------------------------
//
//

/* Please see man pages for details 
    

                
                
                

                

    

    
    
    
    
                                        
    
    
    
    
*/
Result MountSdmc(const char* archiveName = "sdmc:");

/* Please see man pages for details 
    
               
*/
void InitializeLatencyEmulation( void);

/* Please see man pages for details 
    
               
*/
void ForceEnableLatencyEmulation( bool isEmulateEndurance = true, s64 constantWait = 0);

/* Please see man pages for details 
    
               
*/
void ForceDisableLatencyEmulation( void );

//

//----------------------------------------
//
//

/* Please see man pages for details 
    

                
                

    
    

    
    
    
                                
    
*/
Result SetArchivePriority(const char* archiveName, s32 priority);

/* Please see man pages for details 
    
    
    

                
                

    
    

    
    
    
                                
    
*/
Result GetArchivePriority(s32* pOut, const char* archiveName);
//

//----------------------------------------
//
//

/* Please see man pages for details 
    
    
    

                
                
                
                
                
                
                

    
*/
void SetSaveDataSecureValue(bit64 value);

/* Please see man pages for details 
    
    
    

                
                
                
                
                
                
                
                

    
    
*/
void SetSaveDataSecureValue(bit64 value, bit64 mask);

/* Please see man pages for details 
    
    
    

                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                

    

    
*/
bool VerifySaveDataSecureValue(bit64 value);

/* Please see man pages for details 
    
    
    

                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                

    
    

    
*/
bool VerifySaveDataSecureValue(bit64 value, bit64 mask);

/* Please see man pages for details 
    

                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                

    

    
*/
bool VerifySaveDataSecureValueLoosely(bit64 value);

/* Please see man pages for details 
    
    
    

                
                
                
                

    
    
    
*/
void SetOtherSaveDataSecureValue(bit64 value, bit32 uniqueId, bit8 variation);

/* Please see man pages for details 
    
    
    

                
                
                
                

    
    

    
*/
bit64 GetOtherSaveDataSecureValue(bit32 uniqueId, bit8 variation);

//


// TODO: Other details

/* Please see man pages for details 
    

                

                
                
                

    
    

    
    
    
                                
    
*/
Result GetArchiveFreeBytes(s64* pOut, const char* archiveName);

/* Please see man pages for details 
    

                
                
                
                
                
                
                
                
                
                
                
                
                
                

    
*/
void SetAnalysisLog(bool enabled);


}}


#ifdef NN_SWITCH_ENABLE_HOST_IO
namespace nn { namespace fs {

    /* Please see man pages for details 

        
        

        
    */
    namespace hio {

/* Please see man pages for details 
    

                
                

                
                

    
    
    
    
    
    

    
*/
Result MountHioArchive(const char* archiveName, const wchar_t* hostPath, size_t maxFile, size_t maxDirectory, void* workingMemory, size_t workingMemorySize);

/* Please see man pages for details 
    

                
                

    
    

    
*/
s32 GetHioRequiredMemorySize(size_t maxFile, size_t maxDirectory);

}}}
#endif//NN_SWITCH_ENABLE_HOST_IO

#endif
