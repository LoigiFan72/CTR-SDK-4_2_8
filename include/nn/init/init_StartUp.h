/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_StartUp.h

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
#ifndef NN_INIT_INIT_STARTUP_H_
#define NN_INIT_INIT_STARTUP_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Please see man pages for details 
    

    

    
    
*/

/* Please see man pages for details 
    

    

    

    

    

    
*/


/* Please see man pages for details 
    

    
    

    

    
    
    

    
    

    

    
*/
void nnMain(void);

/* Please see man pages for details 
    

    
    

    
    
    
    

    
    
    

    
    
    

    

    
    

    

    
*/
void nninitStartUp(void);

/*  

*/




typedef void (*nninitStaticInitFunc)(void);

void nninitCallStaticInitializers(void);
void nninitSetup(void);
void nninitSetupDaemons(void);
void nninitSystem(void);


#ifdef __cplusplus
}   // extern "C"
#endif

#endif // NN_INIT_INIT_STARTUP_H_
