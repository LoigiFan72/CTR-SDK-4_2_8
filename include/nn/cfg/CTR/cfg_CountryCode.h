/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cfg_CountryCode.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CFG_CTR_CFG_COUNTRY_CODE_H_
#define NN_CFG_CTR_CFG_COUNTRY_CODE_H_

namespace nn {
namespace cfg {
namespace CTR {

/* Please see man pages for details 
    
*/
enum CfgCountryCode
{
    CFG_COUNTRY_UNDEFINED   = 0,        //

    // JPN region
    CFG_COUNTRY_JAPAN       = 1,        //

    // USA region
    CFG_COUNTRY_ANGUILLA    = 8,        //
    CFG_COUNTRY_ANTIGUA_AND_BARBUDA,    //
    CFG_COUNTRY_ARGENTINA   = 10,       //
    CFG_COUNTRY_ARUBA,                  //
    CFG_COUNTRY_BAHAMAS,                //
    CFG_COUNTRY_BARBADOS,               //
    CFG_COUNTRY_BELIZE,                 //
    CFG_COUNTRY_BOLIVIA,                //
    CFG_COUNTRY_BRAZIL,                 //
    CFG_COUNTRY_BRITISH_VIRGIN_ISLANDS, //
    CFG_COUNTRY_CANADA,                 //
    CFG_COUNTRY_CAYMAN_ISLANDS,         //
    CFG_COUNTRY_CHILE       = 20,       //
    CFG_COUNTRY_COLOMBIA,               //
    CFG_COUNTRY_COSTA_RICA,             //
    CFG_COUNTRY_DOMINICA,               //
    CFG_COUNTRY_DOMINICAN_REPUBLIC,     //
    CFG_COUNTRY_ECUADOR,                //
    CFG_COUNTRY_EL_SALVADOR,            //
    CFG_COUNTRY_FRENCH_GUIANA,          //
    CFG_COUNTRY_GRENADA,                //
    CFG_COUNTRY_GUADELOUPE,             //
    CFG_COUNTRY_GUATEMALA   = 30,       //
    CFG_COUNTRY_GUYANA,                 //
    CFG_COUNTRY_HAITI,                  //
    CFG_COUNTRY_HONDURAS,               //
    CFG_COUNTRY_JAMAICA,                //
    CFG_COUNTRY_MARTINIQUE,             //
    CFG_COUNTRY_MEXICO,                 //
    CFG_COUNTRY_MONTSERRAT,             //
    CFG_COUNTRY_NETHERLANDS_ANTILLES,   //
    CFG_COUNTRY_NICARAGUA,              //
    CFG_COUNTRY_PANAMA      = 40,       //
    CFG_COUNTRY_PARAGUAY,               //
    CFG_COUNTRY_PERU,                   //
    CFG_COUNTRY_ST_KITTS_AND_NEVIS,     //
    CFG_COUNTRY_ST_LUCIA,               //
    CFG_COUNTRY_ST_VINCENT_AND_THE_GRENADINES,  //
    CFG_COUNTRY_SURINAME,               //
    CFG_COUNTRY_TRINIDAD_AND_TOBAGO,    //
    CFG_COUNTRY_TURKS_AND_CAICOS_ISLANDS,   //
    CFG_COUNTRY_UNITED_STATES,          //
    CFG_COUNTRY_URUGUAY     = 50,       //
    CFG_COUNTRY_US_VIRGIN_ISLANDS,      //
    CFG_COUNTRY_VENEZUELA,              //

    // EUR, NAL regions
    CFG_COUNTRY_ALBANIA     = 64,       //
    CFG_COUNTRY_AUSTRALIA,              //
    CFG_COUNTRY_AUSTRIA,                //
    CFG_COUNTRY_BELGIUM,                //
    CFG_COUNTRY_BOSNIA_AND_HERZEGOVINA, //
    CFG_COUNTRY_BOTSWANA,               //
    CFG_COUNTRY_BULGARIA    = 70,       //
    CFG_COUNTRY_CROATIA,                //
    CFG_COUNTRY_CYPRUS,                 //
    CFG_COUNTRY_CZECH_REPUBLIC,         //
    CFG_COUNTRY_DENMARK,                //
    CFG_COUNTRY_ESTONIA,                //
    CFG_COUNTRY_FINLAND,                //
    CFG_COUNTRY_FRANCE,                 //
    CFG_COUNTRY_GERMANY,                //
    CFG_COUNTRY_GREECE,                 //
    CFG_COUNTRY_HUNGARY     = 80,       //
    CFG_COUNTRY_ICELAND,                //
    CFG_COUNTRY_IRELAND,                //
    CFG_COUNTRY_ITALY,                  //
    CFG_COUNTRY_LATVIA,                 //
    CFG_COUNTRY_LESOTHO,                //
    CFG_COUNTRY_LIECHTENSTEIN,          //
    CFG_COUNTRY_LITHUANIA,              //
    CFG_COUNTRY_LUXEMBOURG,             //
    CFG_COUNTRY_MACEDONIA,              //
    CFG_COUNTRY_MALTA       = 90,       //
    CFG_COUNTRY_MONTENEGRO,             //
    CFG_COUNTRY_MOZAMBIQUE,             //
    CFG_COUNTRY_NAMIBIA,                //
    CFG_COUNTRY_NETHERLANDS,            //
    CFG_COUNTRY_NEW_ZEALAND,            //
    CFG_COUNTRY_NORWAY,                 //
    CFG_COUNTRY_POLAND,                 //
    CFG_COUNTRY_PORTUGAL,               //
    CFG_COUNTRY_ROMANIA,                //
    CFG_COUNTRY_RUSSIA      = 100,      //
    CFG_COUNTRY_SERBIA,                 //
    CFG_COUNTRY_SLOVAKIA,               //
    CFG_COUNTRY_SLOVENIA,               //
    CFG_COUNTRY_SOUTH_AFRICA,           //
    CFG_COUNTRY_SPAIN,                  //
    CFG_COUNTRY_SWAZILAND,              //
    CFG_COUNTRY_SWEDEN,                 //
    CFG_COUNTRY_SWITZERLAND,            //
    CFG_COUNTRY_TURKEY,                 //
    CFG_COUNTRY_UNITED_KINGDOM = 110,   //
    CFG_COUNTRY_ZAMBIA,                 //
    CFG_COUNTRY_ZIMBABWE,               //
    CFG_COUNTRY_AZERBAIJAN,             //
    CFG_COUNTRY_MAURITANIA,             //
    CFG_COUNTRY_MALI,                   //
    CFG_COUNTRY_NIGER,                  //
    CFG_COUNTRY_CHAD,                   //
    CFG_COUNTRY_SUDAN,                  //
    CFG_COUNTRY_ERITREA,                //
    CFG_COUNTRY_DJIBOUTI    = 120,      //
    CFG_COUNTRY_SOMALIA,                //
    CFG_COUNTRY_ANDORRA,                //
    CFG_COUNTRY_GIBRALTAR,              //
    CFG_COUNTRY_GUERNSEY,               //
    CFG_COUNTRY_ISLE_OF_MAN,            //
    CFG_COUNTRY_JERSEY,                 //
    CFG_COUNTRY_MONACO,                 //

    // TWN region
    CFG_COUNTRY_TAIWAN      = 128,      //

    // KOR region
    CFG_COUNTRY_SOUTH_KOREA = 136,      //

    // HKG region
    CFG_COUNTRY_HONG_KONG   = 144,      //
    CFG_COUNTRY_MACAU,                  //

    // ASI region
    CFG_COUNTRY_INDONESIA   = 152,      //

    // USA region
    CFG_COUNTRY_SINGAPORE   = 153,      //

    // ASI region (again)
    CFG_COUNTRY_THAILAND    = 154,      //
    CFG_COUNTRY_PHILIPPINES,            //

    // USA region
    CFG_COUNTRY_MALAYSIA    = 156,      //

    // CHN region
    CFG_COUNTRY_CHINA       = 160,      //

    // USA region
    CFG_COUNTRY_UAE         = 168,      //

    // EUR region
    CFG_COUNTRY_INDIA       = 169,      //

    // Undefined region
    CFG_COUNTRY_EGYPT       = 170,      //
    CFG_COUNTRY_OMAN,                   //
    CFG_COUNTRY_QATAR,                  //
    CFG_COUNTRY_KUWAIT,                 //

    // USA region
    CFG_COUNTRY_SAUDI_ARABIA = 174,     //

    // Undefined region
    CFG_COUNTRY_SYRIA       = 175,      //
    CFG_COUNTRY_BAHRAIN,                //
    CFG_COUNTRY_JORDAN,                 //

    // EUR region
    CFG_COUNTRY_SAN_MARINO  = 184,      //
    CFG_COUNTRY_VATICAN_CITY,           //

    CFG_COUNTRY_OTHERS      = 254,      //
    CFG_COUNTRY_UNKNOWN     = 255,      //

    CFG_COUNTRY_MAX
};

} // end of namespace CTR
} // end of namespace cfg
} // end of namespace nn

// Corresponding country code. Use an OR to combine the start position left-shifted by 16 bits and the end position
#define CFG_COUNTRY_MAPPING_JAPAN      (u32)( CFG_COUNTRY_JAPAN << 16       | CFG_COUNTRY_JAPAN )       //
#define CFG_COUNTRY_MAPPING_AMERICA    (u32)( CFG_COUNTRY_ANGUILLA << 16    | CFG_COUNTRY_VENEZUELA )   //
#define CFG_COUNTRY_MAPPING_EUROPE     (u32)( CFG_COUNTRY_ALBANIA << 16     | CFG_COUNTRY_MONACO )      //
#define CFG_COUNTRY_MAPPING_AUSTRALIA  (u32)( CFG_COUNTRY_ALBANIA << 16     | CFG_COUNTRY_MONACO )      //
#define CFG_COUNTRY_MAPPING_CHINA      (u32)( CFG_COUNTRY_CHINA << 16       | CFG_COUNTRY_CHINA )       //
#define CFG_COUNTRY_MAPPING_KOREA      (u32)( CFG_COUNTRY_SOUTH_KOREA << 16 | CFG_COUNTRY_SOUTH_KOREA ) //

#endif      // NN_CFG_CTR_CFG_COUNTRY_CODE_H_
