/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ngc_ProfanityFilter.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47308 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NGC_CTR_PROFANITY_FILTER_H_
#define NN_NGC_CTR_PROFANITY_FILTER_H_

#include <nn/os.h>

#if !defined( NN_NGC_CTR_PROFANITY_FILTER_PATTERN_LIST_H_ ) || !defined( NN_NGC_CTR_PROFANITY_FILTER_BASE_H_ )
#   error include error
#endif

namespace nn
{

namespace fs
{
    class FileInputStream;
}   // namespace fs

namespace ngc
{
namespace CTR
{

/* Please see man pages for details 
   
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
 */
#pragma diag_suppress 2530
class ProfanityFilter : public ProfanityFilterBase
{
public:
    
    /* Please see man pages for details 
      
             
             
     */
    explicit ProfanityFilter();
    
    /* Please see man pages for details 
      
             
             
             
     */
    explicit ProfanityFilter( const nn::WithInitialize& );
    
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
      
     */
    explicit ProfanityFilter( uptr pWorkMemory ) { Initialize( pWorkMemory ); }
    
    /* Please see man pages for details 
      
             
             
     */
    virtual ~ProfanityFilter(){ Finalize(); }
    
    /* Please see man pages for details 
      
             
             
             
     */
    nn::Result Initialize();

    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
      
      
      
     */
    nn::Result Initialize( uptr pWorkMemory );
    
    void SkipAtSignCheck( bool bSkipChecking );
    
    /* Please see man pages for details 
      
             
             
             
      
     */
    nn::Result Finalize();
    
    /* Please see man pages for details 
      
      
     */
    virtual u32 GetContentVersion();
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, const wchar_t** ppWords, size_t nWordCount );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, ProfanityFilterPatternList nPatternCode, const wchar_t** ppWords, size_t nWordCount );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, bool bCommunicateWithOtherRegions, const wchar_t** ppWords, size_t nWordCount );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
                                    
     */
    void SetMaskMode( bool bOverWrite );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
                                                
                                                
                                                
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, wchar_t* pText );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
                                                
                                                
                                                
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, ProfanityFilterPatternList nPatternCode, wchar_t* pText );
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
                                                     
                                                     
                                                     
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, bool bCommunicateWithOtherRegions, wchar_t* pText );
    
public:
    /* Please see man pages for details 
      
     */
    enum
    {
        //
        WORKMEMORY_SIZE = 64 * 1024
    };
    
private:
    void CleanUpVariables();
    void SetupMemoryArea();
    nn::Result MountSharedContents();
    
    nn::Result CheckArguments_Word( const bit32* pCheckResults, const wchar_t** ppWords, size_t nWordCount ) const;
    nn::Result CheckProfanityWords_Impl( bit32* pCheckResults, nn::fs::FileInputStream* pFileStream, const wchar_t** ppWords, size_t nWordCount );
    void CheckWords( bit32* pCheckResults, const wchar_t *pPattern, size_t nLength, wchar_t* const* ppConvertedWords, size_t nWordCount );
    
    nn::Result CheckArguments_Text( const wchar_t* pText ) const;
    nn::Result MaskProfanityWordsInText_Impl( int* pProfanityWordCount, wchar_t* pUserInput, wchar_t* pConvertedUserInput, u8* pMapping, nn::fs::FileInputStream* pFileStream );
    void MaskText( int* pProfanityWordCount, wchar_t* pUserInput, wchar_t* pConvertedUserInput, u8* pMapping, const wchar_t* pPattern, bool bIgnoreSpace );
    
private:
    //
    nn::os::MemoryBlock m_MemoryBlock;
    
    //
    bool m_bIsUsingMemoryBlock;
    
    //
    bool m_bContentMounted;
    
    //
    bool m_bSkipAtSignCheck;
    
    //
    ProfanityFilterPatternList m_nPatternList;
    
    //
    uptr m_pWorkingHead;
    
    //
    uptr m_pTempPoolHead;
    
    //
    uptr m_pPatternsHead;
    
    //
    uptr m_pMountWorkingArea;
    
    //
    uptr m_pUserArea;
    
    //
    bool m_bMaskOverWrite;
};
#pragma diag_default 2530

}   // namespace CTR
}   // namespaec ngc
}   // namespace nn

#endif // NN_NGC_CTR_PROFANITY_FILTER_H_
