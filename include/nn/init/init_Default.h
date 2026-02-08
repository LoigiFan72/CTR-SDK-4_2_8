/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     init_Default.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46852 $
 *---------------------------------------------------------------------------*/

#ifndef NN_INIT_INIT_DEFAULT_H_
#define NN_INIT_INIT_DEFAULT_H_

#ifdef __cplusplus
extern "C" {
#endif

    void nninitStartUpDefault(void);
    bool nninitIsStartUpDefaultUsing(void);
    void nninitSetupDefault(void);
    void nninitSetupDefaultWithSettingExitHandler(void);

#ifdef __cplusplus
}   // extern "C"
#endif

#endif // NN_INIT_INIT_DEFAULT_H_
