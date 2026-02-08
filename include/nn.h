/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     nn.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_H_
#define NN_H_

/* Please see man pages for details 
    

    
    
*/



/* Please see man pages for details 













*/
#include <nn/config.h>
#include <nn/types.h>
#include <nn/assert.h>

#include <nn/Result.h>
#include <nn/Handle.h>

#include <nn/init.h>
#include <nn/dbg.h>
#include <nn/os.h>
#include <nn/util.h>
#include <nn/nstd.h>


#if     defined(NN_PLATFORM_CTR)
    #if     defined(NN_SYSTEM_PROCESS)
        #include <nn/fnd.h>
        #include <nn/math.h>

        #if     defined(NN_PROCESSOR_ARM_V6)
            #if     ! defined(NN_HARDWARE_CTR_LEGACY)
                #include <nn/camera.h>
                #include <nn/crypto.h>
                #include <nn/dsp.h>
                #include <nn/fs.h>
                #include <nn/gx.h>
                #include <nn/hid.h>
                #include <nn/mic.h>

                #if defined(__cplusplus) && !defined(NN_H_NOT_INCLUDE_ALL)
                    #include <nn/ro.h>

                    #include <nn/cx.h>
                    #include <nn/jpeg.h>
                    #include <nn/enc.h>

                    #include <nn/applet.h>
                    #include <nn/ptm.h>
                    #include <nn/pl.h>
                    #include <nn/news.h>
                    #include <nn/cfg.h>

                    #include <nn/hio.h>
                    #include <nn/midi.h>

                    #include <nn/gd.h>
                    #include <nn/gr.h>
                    #include <nn/ulcd.h>
                    #include <nn/tpl.h>
                    #include <nn/font.h>

                    #include <nn/snd.h>

                    #include <nn/y2r.h>

                    #include <nn/uds.h>
                    #include <nn/rdt.h>
                    #include <nn/dlp.h>
                    #include <nn/cec.h>
                    #include <nn/boss.h>
                    #include <nn/ac.h>
                    #include <nn/ir.h>

                    #include <nn/ndm.h>
                    #include <nn/friends.h>
                    #include <nn/ngc.h>
                    #include <nn/ubl.h>

                    #include <nn/erreula.h>
                    #include <nn/swkbd.h>
                    #include <nn/phtsel.h>
                    #include <nn/voicesel.h>
                    #include <nn/extrapad.h>

                    #include <nn/err.h>
                    #include <nn/http_Initialize.h>
                    #include <nn/socket_Initialize.h>
                #endif
            #endif
        #endif
    #endif
#else
    #error NN_PLATFORM_ not specified
#endif


#endif
