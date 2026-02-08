/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dsp_Common.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_DSP_CTR_DSP_COMMON_H_
#define NN_DSP_CTR_DSP_COMMON_H_

/*---------------------------------------------------------------------------*
 * constants
 *---------------------------------------------------------------------------*/

// Constants for defining IN and OUT. (Generally defined as 0 : DSP->ARM, 1 : ARM->DSP)  
#ifdef NN_SYSTEM_PROCESS
#define NN_DSP_PIPE_INPUT              0
#define NN_DSP_PIPE_OUTPUT             1
#else
#define NN_DSP_PIPE_INPUT              1
#define NN_DSP_PIPE_OUTPUT             0
#endif
#define NN_DSP_PIPE_PEER_MAX           2

// Defined ports
#define NN_DSP_PIPE_CONSOLE            0   // DSP->ARM: Debugging console
#define NN_DSP_PIPE_DMA                1   // DSP<->ARM: Pseudo-DMA
#define NN_DSP_PIPE_AUDIO              2   // DSP<->ARM: General-purpose audio communications
#define NN_DSP_PIPE_BINARY             3   // DSP<->ARM: General-purpose binary
#define NN_DSP_PIPE_EPHEMERAL          4   // Free region that can be allocated with DSP_CreatePipe function
#define NN_DSP_PIPE_DSPSND             NN_DSP_PIPE_AUDIO

// System resources
#define NN_DSP_PIPE_PORT_MAX               8  // Maximum number of usable ports for pipes
#define NN_DSP_PIPE_DEFAULT_BUFFER_LENGTH  64 // Default ring buffer size

#define NN_DSP_PIPE_FLAG_INPUT         0x0000  // Input side
#define NN_DSP_PIPE_FLAG_OUTPUT        0x0001  // Output side
#define NN_DSP_PIPE_FLAG_PORTMASK      0x00FF  // Negative field for port numbers
#define NN_DSP_PIPE_FLAG_BOUND         0x0100  // Opened
#define NN_DSP_PIPE_FLAG_EOF           0x0200  // EOF

#define NN_DSP_PIPE_FLAG_EXIT_OS       0x8000  // Exit processing for the DSP's AHB master

#define NN_DSP_PIPE_COMMAND_REGISTER   2

// Command structures for DSP file I/O.
#define NN_DSP_PIPE_IO_COMMAND_OPEN    0
#define NN_DSP_PIPE_IO_COMMAND_CLOSE   1
#define NN_DSP_PIPE_IO_COMMAND_SEEK    2
#define NN_DSP_PIPE_IO_COMMAND_READ    3
#define NN_DSP_PIPE_IO_COMMAND_WRITE   4
#define NN_DSP_PIPE_IO_COMMAND_MEMMAP  5

#define NN_DSP_PIPE_IO_MODE_R          0x0001
#define NN_DSP_PIPE_IO_MODE_W          0x0002
#define NN_DSP_PIPE_IO_MODE_RW         0x0004
#define NN_DSP_PIPE_IO_MODE_TRUNC      0x0008
#define NN_DSP_PIPE_IO_MODE_CREATE     0x0010

#define NN_DSP_PIPE_IO_SEEK_SET        0
#define NN_DSP_PIPE_IO_SEEK_CUR        1
#define NN_DSP_PIPE_IO_SEEK_END        2

#ifndef CTR_DSP
/*---------------------------------------------------------------------------*
 * includes
 *---------------------------------------------------------------------------*/
#include <nn/types.h>
#include <nn/dsp/CTR/Common/dsp_Types.h>

/*---------------------------------------------------------------------------*
 * namespaces
 *---------------------------------------------------------------------------*/

namespace nn {
namespace dsp {
namespace CTR {

typedef enum
{
    INTERRUPT_TYPE_REPLY0 = 0,
    INTERRUPT_TYPE_REPLY1 = 1,
    INTERRUPT_TYPE_PIPE   = 2
} InterruptType;

#endif // CTR_DSP

//----------------------------------------------------------------
// Move from dsp_Pipe.h
//----------------------------------------------------------------
// Pipe structures.
// Because there is no method to directly access ARM from the DSP. Accordingly, control the buffer in the DSP from ARM using APBP-FIFO. 
// 
// It will be treated as a ring buffer in the absence of a particular specification.
typedef struct DSPPipe
{
    DSPAddr address;    // Starting address of the buffer
    DSPByte length;     // Buffer size
    DSPByte rpos;       // First unread region
    DSPByte wpos;       // Last appended region
    u16     flags;      // Attribute flags
}
DSPPipe, * pDSPPipe;

/*---------------------------------------------------------------------------*/
/* Declarations */

// Pipe information maintained by the DSP and accessed by an ARM processor.
typedef struct DSPPipeMonitor
{
    DSPPipe pipe[NN_DSP_PIPE_PORT_MAX][NN_DSP_PIPE_PEER_MAX];
}
DSPPipeMonitor;

#ifndef CTR_DSP
} // namespace nn {
} // namespace dsp {
} // namespace CTR {
#endif // CTR_DSP

#endif  // ifndef NN_DSP_CTR_DSP_COMMON_H_

