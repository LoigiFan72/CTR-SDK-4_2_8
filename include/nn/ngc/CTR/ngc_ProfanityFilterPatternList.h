/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ngc_ProfanityFilterPatternList.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47211 $
 *---------------------------------------------------------------------------*/

#ifndef NN_NGC_CTR_PROFANITY_FILTER_PATTERN_LIST_H_
#define NN_NGC_CTR_PROFANITY_FILTER_PATTERN_LIST_H_

namespace nn
{
namespace ngc
{
namespace CTR
{

/* Please see man pages for details 
  
         
         
         
         
 */
enum ProfanityFilterPatternList
{
    //
    PATTERNLIST_JAPAN_JAPANESE = 0,
    
    //
    PATTERNLIST_AMERICA_ENGLISH = 1,
    
    //
    PATTERNLIST_AMERICA_FRENCH = 2,
    
    //
    PATTERNLIST_AMERICA_SPANISH = 3,
    
    //
    PATTERNLIST_EUROPE_ENGLISH = 4,
    
    //
    PATTERNLIST_EUROPE_FRENCH = 5,
    
    //
    PATTERNLIST_EUROPE_GERMAN = 6,
    
    //
    PATTERNLIST_EUROPE_ITALIAN = 7,
    
    //
    PATTERNLIST_EUROPE_SPANISH = 8,
    
    //
    PATTERNLIST_EUROPE_DUTCH = 9,
    
    //
    PATTERNLIST_KOREA_KOREAN = 10,
    
    //
    PATTERNLIST_CHINA_SIMP_CHINESE = 11,
    
    //
    PATTERNLIST_EUROPE_PORTUGUESE = 12,
    
    //
    PATTERNLIST_EUROPE_RUSSIAN = 13,
    
    //
    PATTERNLIST_AMERICA_PORTUGUESE = 14,
    
    //
    PATTERNLIST_TAIWAN_TRAD_CHINESE = 15,
    
    //
    PATTERNLIST_TAIWAN_ENGLISH = 16,
    
    // NOTE: Numerical values above must match those in internal resource, so do not change them.
    
    
    //
    PATTERNLIST_MAX
};


}   // namespace CTR
}   // namespaec ngc
}   // namespace nn

#endif // NN_NGC_CTR_PROFANITY_FILTER_PATTERN_LIST_H_
