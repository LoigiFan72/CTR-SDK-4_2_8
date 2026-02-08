/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     font.h

  Copyright (C)2009-2012 Nintendo Co., Ltd./HAL Laboratory, Inc.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48191 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FONT_H_
#define NN_FONT_H_

/* Please see man pages for details 
    
    
*/

/* Please see man pages for details 
    
    
                
*/

#include <nn/font/font_CharStrmReader.h>
#include <nn/font/font_Font.h>
#include <nn/font/font_ResFont.h>
#include <nn/font/font_ArchiveFont.h>
#include <nn/font/font_PackedFont.h>

#if defined(NN_PLATFORM_CTR)
    #include <nn/font/CTR/font_TagProcessorBase.h>
    #include <nn/font/CTR/font_TagProcessor.h>
    #include <nn/font/CTR/font_WideTagProcessor.h>

    #include <nn/font/CTR/font_CharWriter.h>
    #include <nn/font/CTR/font_TextWriterBase.h>
    #include <nn/font/CTR/font_TextWriter.h>
    #include <nn/font/CTR/font_WideTextWriter.h>
    #include <nn/font/CTR/font_RectDrawer.h>
    #include <nn/font/CTR/font_DispStringBuffer.h>
    namespace nn {
        namespace font {
            using namespace nn::font::CTR;
        }
    }
#else
    #error no platform selected
#endif

/* NN_FONT_H_ */
#endif
