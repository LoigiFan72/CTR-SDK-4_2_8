/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ngc_ProfanityFilterBase.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47308 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NGC_CTR_PROFANITY_FILTER_BASE_H_
#define NN_NGC_CTR_PROFANITY_FILTER_BASE_H_

#include <nn/types.h>
#include <nn/Result.h>
#include <nn/WithInitialize.h>
#include <nn/cfg/CTR/cfg_RegionCode.h>

namespace nn
{
namespace ngc
{
namespace CTR
{

/* Please see man pages for details 
   
          
          
          
 */
class ProfanityFilterBase
{
public:
    /* Please see man pages for details 
      
     */
    virtual ~ProfanityFilterBase(){}
    
    /* Please see man pages for details 
      
      
     */
    virtual u32 GetContentVersion() = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, const wchar_t** ppWords, size_t nWordCount ) = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, ProfanityFilterPatternList nPatternCode, const wchar_t** ppWords, size_t nWordCount ) = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
      
     */
    virtual nn::Result CheckProfanityWords( bit32* pCheckResults, bool bCommunicateWithOtherRegions, const wchar_t** ppWords, size_t nWordCount ) = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
                                                
                                                
                                                
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, wchar_t* pText ) = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
                                                
                                                
                                                
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, ProfanityFilterPatternList nPatternCode, wchar_t* pText ) = 0;
    
    /* Please see man pages for details 
      
             
             
             
             
             
             
             
             
             
             
             
             
             
      
      
      
                                                     
                                                     
                                                     
     */
    virtual nn::Result MaskProfanityWordsInText( int* pProfanityWordCount, bool bCommunicateWithOtherRegions, wchar_t* pText ) = 0;
    
protected:
    void GetPatternListsFromRegion( ProfanityFilterPatternList* pPatternLists, int *pListNum, bool bCommunicateWithOtherRegions );
    static void ConvertUserInputForWord( wchar_t* pConvertedWord, int nLength, const wchar_t* pWord );
    static void ConvertUserInputForText( wchar_t* pConvertedWord, u8* pSourceLengthMapping, int nLength, const wchar_t* pWord );
    bool IsIncludesAtSign( const wchar_t* pWord, int nLength );
    static bool ConvertRegexPatternForText( wchar_t* pConvertedPattern, const wchar_t* pPattern, size_t nLength );

private:
    /* Please see man pages for details 
      
     */
    typedef struct SmallMap
    {
        //
        wchar_t small;
        
        //
        wchar_t big;
    } SmallMap;
    
    /* Please see man pages for details 
      
     */
    typedef struct HalfwidthMap
    {
        //
        wchar_t half;
        
        //
        wchar_t full;
    } HalfwidthMap;
    
    static void ConvertKatakanaToBig( wchar_t *pKana );
    static bool ConvertHalfwidthKatakanaToFullwidth( wchar_t *pBuffer, wchar_t half, const HalfwidthMap* pMapping, int mapNum );

private:
    static const SmallMap s_SmallMapping[];
    static const HalfwidthMap s_HalfMapping[];
    static const HalfwidthMap s_VoicedMapping[];
    static const HalfwidthMap s_SemiVoicedMapping[];
};

}   // namespace CTR
}   // namespaec ngc
}   // namespace nn

#endif // NN_NGC_CTR_PROFANITY_FILTER_BASE_H_
