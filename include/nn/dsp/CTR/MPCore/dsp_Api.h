/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     dsp_Api.h

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
#ifndef NN_DSP_CTR_DSP_API_H_
#define NN_DSP_CTR_DSP_API_H_

#include <nn/Handle.h>

namespace nn {
namespace dsp {
namespace CTR {

namespace detail
{
    nn::Result InitializeBase(Handle* pSession, const char* name);
    nn::Result FinalizeBase  (Handle* pSession);
}

namespace
{
    const char PORT_NAME_DSP[]    = "dsp::DSP";
}

inline nn::Result InitializeIpc(Handle* pSession)    { return detail::InitializeBase(pSession, PORT_NAME_DSP); }
inline nn::Result FinalizeIpc  (Handle* pSession)    { return detail::FinalizeBase  (pSession); }

/* Please see man pages for details 
    
    
 */

/* Please see man pages for details 
    

    
 */
nn::Result    Initialize( void );

/* Please see man pages for details 
    
 */
void          Finalize( void );

/* Please see man pages for details 
    
    
    
    
    
    
    
    
    
 */
nn::Result    LoadComponent( const u8 pComponent[], size_t size, bit16 maskPram = 0xff, bit16 maskDram = 0xff ) ;
nn::Result    LoadComponentCore( const u8 pComponent[], size_t size, bit16 maskPram = 0xff, bit16 maskDram = 0xff ) ;

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result    LoadDefaultComponent( void );

/* Please see man pages for details 
    
    
    
 */
nn::Result    UnloadComponent( void );
nn::Result    UnloadComponentCore( void );

/*  

*/

/* Please see man pages for details 
    
    
 */

/* Please see man pages for details 
    
    
    
    
    
    
    
 */
nn::Result RegisterInterruptEvents(nn::Handle handle, s32 type, s32 port = 0);

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result RecvData( u16 regNo, u16 *pValue );

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result SendData( u16 regNo, u16 value );

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result RecvDataIsReady( u16 regNo, bool* pStatus );

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result SendDataIsEmpty( u16 regNo, bool * pStatus );

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result GetVirtualAddress(uptr physicalAddress, uptr * pVirtualAddress);

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result GetPhysicalAddress(uptr address, uptr * pPhysicalAddress);

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result ConvertProcessAddressFromDspDram(uptr addressOnDsp, uptr * pAddressOnHost);

/* Please see man pages for details 
    
    
    
    
    
    
    
    
 */
nn::Result ReadPipeIfPossible( int port, void* buffer, u16 length, u16* pLengthRead );

/* Please see man pages for details 
    
    
    
    
    
    
    
 */
nn::Result WriteProcessPipe( int port, const void *buffer, u32 length );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result CheckSemaphoreRequest( bool* pIsRequested );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result ClearSemaphore( u16 mask );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result MaskSemaphore( u16 mask );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result GetSemaphore( u16* pMask );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result SetSemaphore( u16 mask );

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result GetSemaphoreEventHandle ( nn::Handle *);

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result SetSemaphoreEventMask ( bit16 );

/*  

*/

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result FlushDataCache( uptr addr, size_t size );

/* Please see man pages for details 
    
    
    
    
    
    
 */
nn::Result InvalidateDataCache( uptr addr, size_t size );

/* Please see man pages for details 
    
    
 */
bool IsComponentLoaded(void);

/* Please see man pages for details 
    
    
 */
bool Sleep(void);

/* Please see man pages for details 
    
    
 */
void WakeUp(void);

/* Please see man pages for details 
    
 */
void Awake();

/* Please see man pages for details 
    
 */
void OrderToWaitForFinalize();

/* Please see man pages for details 
    
    
    
    
    
 */
bool RegisterSleepWakeUpCallback(
    void (*sleepCallback)(),
    void (*wakeUpCallback)(),
    void (*orderToWaitForFinalizeCallback)() = NULL
);

/* Please see man pages for details 
    
    
    
    
    
 */
bool ClearSleepWakeUpCallback(
    void (*sleepCallback)(),
    void (*wakeUpCallback)(),
    void (*orderToWaitForFinalizeCallback)() = NULL
);

/* Please see man pages for details 
    
    
    
    
    
 */
nn::Result GetHeadphoneStatus(bool* isConnected);

/* Please see man pages for details 
    
    
    
    
    
 */
Result ForceHeadphoneOut(bool forceout);

/* Please see man pages for details 
    
    
    
    
 */
bool IsDspOccupied(void);

} // namespace CTR {
} // namespace dsp {
} // namespace nn  {

#endif  // ifndef NN_DSP_CTR_DSP_API_H_
