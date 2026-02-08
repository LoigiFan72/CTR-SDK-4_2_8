/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49830 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_API_H_
#define NN_CFG_CTR_CFG_API_H_

/* Please see man pages for details 
    

    
*/

#include <nn/cfg/CTR/cfg_UserInfo.h>
#include <nn/cfg/CTR/cfg_LanguageCode.h>
#include <nn/cfg/CTR/cfg_CountryCode.h>
#include <nn/cfg/CTR/cfg_RegionCode.h>
#include <nn/cfg/CTR/cfg_Sound.h>
#include <nn/cfg/CTR/cfg_Coppacs.h>
#include <nn/Result.h>

#ifdef __cplusplus

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
    
                  
                  
                  
    
    
*/
void Initialize(void);

/* Please see man pages for details 
    
    
                  
                  
                  
                  

    
*/
void Finalize(void);

/* Please see man pages for details 
    
    
                  

    

    
*/
void GetUserName(UserName* pUserName);

/* Please see man pages for details 
    

    

    
*/
void GetBirthday(Birthday* pBirthday);

/* Please see man pages for details 
    

    
*/
CfgCountryCode GetCountry(void);

/* Please see man pages for details 
    
                  

    

    
                  
*/
const char* GetCountryCodeA2(CfgCountryCode cfgCountryCode);

/* Please see man pages for details 
    

    
*/
CfgLanguageCode GetLanguage(void);

/* Please see man pages for details 
    
                  

    

    
                  
*/
const char* GetLanguageCodeA2(CfgLanguageCode cfgLanguageCode);

/* Please see man pages for details 
    

                  
                  
                  

    
*/
void GetSimpleAddress(SimpleAddress* pSimpleAddress);

/* Please see man pages for details 
    
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
    
    
    
    

    
    
    
                                      
    
                                              
    
                                      
*/
nn::Result GetSimpleAddress(SimpleAddress* pSimpleAddress, SimpleAddressId simpleAddressId, uptr pWorkMemory, u32 workMemorySize);

/* Please see man pages for details 
    

    
*/
void GetSimpleAddressId(SimpleAddressId* pSimpleAddressId);

/* Please see man pages for details 
    

    
*/
CfgRegionCode GetRegion(void);

/* Please see man pages for details 
    
                  

    

    
                  
*/
const char* GetRegionCodeA3(CfgRegionCode cfgRegionCode);

/* Please see man pages for details 
    

    
*/
CfgSoundOutputMode GetSoundOutputMode(void);

/* Please see man pages for details 
    

             
             

             

    
*/
nn::fnd::TimeSpan GetUserTimeOffset();

/* Please see man pages for details 
    

             
             

    
*/
bool IsCoppacsSupported();

/* Please see man pages for details 
    

             
             
             
             
             
             

    
*/
CfgCoppacsRestriction GetCoppacsRestriction(void);

/* Please see man pages for details 
    
*/
const u8 CFG_PARENTAL_CONTROL_PIN_CODE_LENGTH = 4;

/* Please see man pages for details 
    

    

    
*/
bool CheckParentalControlPinCode(const char *input);

/* Please see man pages for details 
    

    
*/
bool IsRestrictPhotoExchange(void);

/* Please see man pages for details 
    

    
*/
bool IsRestrictAddFriend(void);

/* Please see man pages for details 
    

    
*/
bool IsRestrictP2pInternet(void);

/* Please see man pages for details 
    

    
*/
bool IsRestrictP2pCec(void);

/* Please see man pages for details 
    

    
*/
bool IsRestrictShopUse(void);

/* Please see man pages for details 
    

             
             
             

    
*/
bool IsAgreedEula(void);

/* Please see man pages for details 
    

                  
                  

    

    




*/
bit64 GetTransferableId(bit32 uniqueId);

} // namespace CTR {
} // namespace cfg {
} // namespace nn {

#endif

#endif //   #ifndef NN_CFG_CTR_CFG_API_H_
