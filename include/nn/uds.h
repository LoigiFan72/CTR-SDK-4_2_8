/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     uds.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
    
    
    
    
*/

#ifndef NN_UDS_H_
#define NN_UDS_H_

/* Please see man pages for details 
    
    
*/
/* Please see man pages for details 
    
    
           
*/

#if defined(NN_PLATFORM_CTR)

    #ifdef  __cplusplus
        #include <nn/uds/CTR/uds_Api.h>
        #include <nn/uds/CTR/uds_Type.h>
        #include <nn/uds/CTR/uds_Result.h>
        #include <nn/uds/CTR/uds_InfoElement.h>
        #include <nn/uds/CTR/uds_ScanResultReader.h>
        #include <nn/uds/CTR/uds_NetworkDescription.h>

        namespace nn {
            namespace uds {
                using namespace nn::uds::CTR;
            }
        }
    #endif // __cplusplus
#else //defined(NN_PLATFORM_CTR)
    #error no platform selected
#endif

#endif /* NN_UDS_H_ */
