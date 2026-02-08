/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds_ScanResultReader.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47172 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
*/

#ifndef LIBRARIES_UDS_CTR_UDS_SCAN_RESULT_READER_H_
#define LIBRARIES_UDS_CTR_UDS_SCAN_RESULT_READER_H_

#include <nn/uds/CTR/uds_Type.h>
#include <nn/uds/CTR/uds_Result.h>
#include <nn/uds/CTR/uds_InfoElement.h>
#include <nn/uds/CTR/uds_NetworkDescription.h>

namespace nn {
namespace uds {
namespace CTR {


/* Please see man pages for details 
    
    
    
*/
class NetworkDescriptionReader
{
public:
    NetworkDescriptionReader(const u8* pBuffer):m_pBuffer(pBuffer){}
    virtual ~NetworkDescriptionReader() {}

/* Please see man pages for details 
  

  
  
*/
    NetworkDescription::CompareResult CompareWith(const NetworkDescription& networkDescription) const;

/* Please see man pages for details 
   
  

  
*/
    void GetBssid(bit8 bssid[MAC_ADDRESS_SIZE]) const;

    
/* Please see man pages for details 
  

  

  
  
  
  
*/
    nn::Result GetNetworkDescription ( NetworkDescription* pNetworkDescription );

/* Please see man pages for details 
  

  

  
  
  
  
  
  
*/
    nn::Result GetNodeInformationList( NodeInformation pNodeInfo[NODE_MAX] );

/* Please see man pages for details 
  

  

  
  
  

*/
    nn::Result GetRadioStrength( LinkLevel* pLinkLevel );

    inline const u8* GetBufferAddress() { return m_pBuffer; }

private:
    const u8* m_pBuffer;
};

/* Please see man pages for details 

    
    
    
*/
class ScanResultReader
{
public:
/* Please see man pages for details 
  
  
  
*/
    ScanResultReader(const void* pBuffer) : m_pBuffer(pBuffer), m_pNext(NULL){}

/* Please see man pages for details 
    
    
    

    
*/
    ScanResultReader(const void* pBuffer, size_t bufferSize);

    virtual ~ScanResultReader() {}

/* Please see man pages for details 
  
  
*/
    u32   GetCount() const;

/* Please see man pages for details 
  
  

*/      const NetworkDescriptionReader GetFirstDescription();

/* Please see man pages for details 
  
  

*/      const NetworkDescriptionReader GetNextDescription();

private:
    const void* m_pBuffer;
    bit8*       m_pNext;
};

/*  

*/
} // end of namespace CTR
} // end of namespace uds
} // end of namespace nn

#endif /* LIBRARIES_UDS_CTR_UDS_SCAN_RESULT_READER_H_ */
