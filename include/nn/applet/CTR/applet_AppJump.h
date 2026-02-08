/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     applet_AppJump.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_APPLET_CTR_APPLET_APPJUMP_H_
#define NN_APPLET_CTR_APPLET_APPJUMP_H_

#include <nn/applet/CTR/applet_Parameters.h>

/* Please see man pages for details 
    
*/
namespace nn {
namespace applet {
namespace CTR {
namespace detail {

    // Call System Settings
    Result JumpToInternetSetting(void);
    Result JumpToParentalControls( AppletParentalControlsScene scene );
    Result JumpToDataManagement( AppletDataManagementScene scene );
    bool IsFromMset( AppletMsetScene* pScene=NULL );
}
}
}
}

namespace nn {
namespace applet {
namespace CTR {

    using namespace nn::applet::CTR;

/* Please see man pages for details 
    
    
 */
    /* Please see man pages for details 
        
        
     */
    inline Result JumpToInternetSetting(void)
    {
        return detail::JumpToInternetSetting();
    }
    /* Please see man pages for details 
        
        
        
     */
    inline Result JumpToParentalControls( AppletParentalControlsScene scene=nn::applet::CTR::PARENTAL_CONTROLS_TOP )
    {
        return detail::JumpToParentalControls( scene );
    }
    /* Please see man pages for details 
        
        
        
     */
    inline Result JumpToDataManagement( AppletDataManagementScene scene=nn::applet::CTR::DATA_MANAGEMENT_STREETPASS )
    {
        return detail::JumpToDataManagement( scene );
    }

    /* Please see man pages for details 
        
        
        
     */
    inline bool IsFromMset( AppletMsetScene* pScene=NULL )
    {
        return detail::IsFromMset( pScene );
    }
/*  

*/

}
}
}

#endif  // ifndef NN_APPLET_CTR_APPLET_APPJUMP_H_
