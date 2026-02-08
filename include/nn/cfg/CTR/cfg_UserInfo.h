/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_UserInfo.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_USER_INFO_H_
#define NN_CFG_CTR_CFG_USER_INFO_H_

#include <nn/fnd.h>
#include <nn/cfg/CTR/cfg_CountryCode.h>

namespace nn {
namespace cfg {
namespace CTR {

/*---------------------------------------------------------------------------*
 * User information
 *---------------------------------------------------------------------------*/
/* Please see man pages for details 
    
*/
const u8 CFG_USER_NAME_LENGTH               = 11;

/* Please see man pages for details 
    
    
             
             
             
             
             
*/
struct UserName
{
    wchar_t userName[CFG_USER_NAME_LENGTH]; //
    bool isNgUserName;                      //
    NN_PADDING1;
};

/* Please see man pages for details 
    
*/
struct Birthday
{
    s8  month;  //
    s8  day;    //
};


/*---------------------------------------------------------------------------*
 *  Simple address information
 *---------------------------------------------------------------------------*/
/* Please see man pages for details 
    
*/
const u8    CFG_SIMPLE_ADDRESS_ID_COUNTRY_SHIFT         = 24;
/* Please see man pages for details 
    
*/
const u8    CFG_SIMPLE_ADDRESS_ID_REGION_SHIFT          = 16;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_COUNTRY_MASK          = 0xffU << CFG_SIMPLE_ADDRESS_ID_COUNTRY_SHIFT;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_REGION_MASK           = 0xffU << CFG_SIMPLE_ADDRESS_ID_REGION_SHIFT;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_RESERVED_MASK         = 0x0000ffff;

/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_NOT_DEFINED           = 0xffffffff;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_COUNTRY_UNDEFINED     = 0x00U << CFG_SIMPLE_ADDRESS_ID_COUNTRY_SHIFT;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_COUNTRY_UNDEFINED2   = 0xffU << CFG_SIMPLE_ADDRESS_ID_COUNTRY_SHIFT;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_REGION_UNDEFINED     = 0x00U << CFG_SIMPLE_ADDRESS_ID_REGION_SHIFT;
/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_ID_REGION_UNDEFINED2    = 0xffU << CFG_SIMPLE_ADDRESS_ID_REGION_SHIFT;

/* Please see man pages for details 
    
*/
const u8    CFG_SIMPLE_ADDRESS_NUM_LANGUAGES   = 16;
/* Please see man pages for details 
    
*/
const u8    CFG_SIMPLE_ADDRESS_NAME_LENGTH     = 64;

/* Please see man pages for details 
    
*/
const u32   CFG_SIMPLE_ADDRESS_WORKMEMORY_SIZE = 256 * 1024;


/* Please see man pages for details 
    

             
             
             
             
*/
struct SimpleAddress
{
    u32 id;                                                                                 //
    wchar_t countryName[CFG_SIMPLE_ADDRESS_NUM_LANGUAGES][CFG_SIMPLE_ADDRESS_NAME_LENGTH];  //
    wchar_t regionName [CFG_SIMPLE_ADDRESS_NUM_LANGUAGES][CFG_SIMPLE_ADDRESS_NAME_LENGTH];  //
    u16 latitude;                                                                           //
    u16 longitude;                                                                          //
};

/* Please see man pages for details 
    
*/
struct SimpleAddressId
{
    u32 id;     //
    
    /* Please see man pages for details 
        
        
    */
    CfgCountryCode GetCountryCode(void) const
    {
        return static_cast<CfgCountryCode>((id & CFG_SIMPLE_ADDRESS_ID_COUNTRY_MASK) >> CFG_SIMPLE_ADDRESS_ID_COUNTRY_SHIFT);
    }

    /* Please see man pages for details 
        
        
    */
    u8 GetRegionCode(void) const
    {
        return (id & CFG_SIMPLE_ADDRESS_ID_REGION_MASK) >> CFG_SIMPLE_ADDRESS_ID_REGION_SHIFT;
    }
};

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

#endif      // NN_CFG_CTR_CFG_USER_INFO_H_
