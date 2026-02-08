/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     cec_Control.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47112 $
 *---------------------------------------------------------------------------*/

#ifndef NN_CEC_CTR_CEC_CONTROL_H_
#define NN_CEC_CTR_CEC_CONTROL_H_
#include <nn/fnd.h>
#include <nn/cec/CTR/cec_MessageBox.h>

namespace nn {
namespace cec {
namespace CTR {

//------------------------------------------------------------
// For notification

/* Please see man pages for details 
    
    

                
*/
struct CecNotificationParam
{
    nn::fnd::DateTimeParameters     recvDate;       //
    u32                             cecTitleId;     //
    u8                              messageId[CEC_SIZEOF_MESSAGEID];    //
};

/* Please see man pages for details 
    
    

                
*/
struct CecNotificationData
{
    size_t  num;                //
    s32     count;              //
    CecNotificationParam param[MESSAGE_BOX_NUM_MAX];    //
};


/* Please see man pages for details 
    
    

           
           
           
           
           
           
           
           
           
*/

class CecControl {

public:

    enum ChangeDaemonState
    {
        DAEMON_CHANGE_STATE_READY ,
        DAEMON_CHANGE_STATE_STARTSCAN ,
        DAEMON_CHANGE_STATE_STOP,
        DAEMON_CHANGE_STATE_STOP_DAEMON,
        DAEMON_CHANGE_STATE_START_DAEMON,
        DAEMON_CHANGE_STATE_RESET_FILTER,

        DAEMON_CHANGE_STATE_NDM_RESUME,
        DAEMON_CHANGE_STATE_NDM_SUSPEND
        
    };

    /* Please see man pages for details 
        
    */
    enum DaemonState
    {
        DAEMON_STATE_STOP,          //
        DAEMON_STATE_IDLE,          //
        DAEMON_STATE_BUSY,          //
        DAEMON_STATE_SCAN,          //
        DAEMON_STATE_READY,         //
        DAEMON_STATE_COMMUNICATING  //
    };


    explicit  CecControl(size_t bufSize);
    CecControl();
    ~CecControl();

    /* Please see man pages for details 
    
     
     
     */
    static nn::Result  Initialize();
    static nn::Result  Initialize(nn::fnd::IAllocator& cecAllocFunc);
    static nn::Result  Initialize(uptr bufferAddress, size_t bufferSize);
    static nn::Result  InitializeWithoutNdm();
    
    /* Please see man pages for details 
    
     
     
     */
    static nn::Result  Finalize();

    static bool IsInitialized();

    /* Please see man pages for details 
     
     
                   
     
     */
    static nn::Result  ReadyDaemon();

    /* Please see man pages for details 
     

                    
                    
                    
                    

     
                                  
                                  

     
     
     
     
     */
    static nn::Result  StartScanning(bool reset = false);

    /* Please see man pages for details 
     
     

     
     
     
     
     */
    static nn::Result  Suspend();

    /* Please see man pages for details 
     

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

     
     
     
     
     
     
     */
    static nn::Result  StopScanning(bool b_Immediate = false, bool b_Async = false);

    /* Please see man pages for details 
     
     
                   

                   
     
     */
    static nn::Result  StopDaemon();

    /* Please see man pages for details 
     
     
                   
     
     */
    static nn::Result  StartDaemon();

    /* Please see man pages for details 
     
     
     
     
     
     
     */
    static nn::Result GetCecInfoBuffer(  u32 cecTitleId, u8 pCecInfoBuffer[], size_t size );
    static nn::Result GetCecInfoBuffer(  u8 pCecInfoBuffer[], size_t size )
    {
        return GetCecInfoBuffer(  0, pCecInfoBuffer, size );
    };

    /* Please see man pages for details 
     
     
     
     
     */
    static nn::Result GetCecState( DaemonState* state );
    static nn::Result GetCecState( u32* state );

    static bool IsDaemonBusy(void);
    
    /* Please see man pages for details 
     
     
     
     
     */
    static nn::Result GetCecRecvEventHandle( nn::os::Event* event );

    /* Please see man pages for details 
     
     
     
     
     
     
     */
    static nn::Result GetExchangeCount( s32* count );


    static nn::Result GetChangeStateEventHandle( nn::os::Event& event );

    static nn::cec::CTR::TitleId MakeCecTitleId(bit32 id, bit8 variation = 0x0);

    /* */
    static nn::Result FormatSaveData();

    /* Please see man pages for details 
     
     
                    
                    
                    

                    
                    
     
     */
    static nn::Result   EnterExclusiveState();

    /* Please see man pages for details 
     
     
     */
    static nn::Result   LeaveExclusiveState();

    static bool                s_Initialized;
    static bool                s_NdmInitialized;
    static bool                s_NdmSuspended;
    static bool                s_EnterExclusiveState;
private:
    static nn::os::CriticalSection    m_Cs;

};




//
//


/* Please see man pages for details 
 

                
                
                
                                    
 
 
 
 
 */
nn::Result  Initialize(nn::fnd::IAllocator& cecAllocFunc);

/* Please see man pages for details 
 
                

                
                
                

 
 
 
 */
nn::Result  Initialize() NN_ATTRIBUTE_DEPRECATED;

/* Please see man pages for details 
 
 

 
 
 
                                    
                                    
                                    
 
 */
nn::Result  Initialize(uptr bufferAddress, size_t bufferSize);

inline nn::Result  Initialize()
{
    return CecControl::Initialize();
}

nn::Result  Initialize(nn::fnd::IAllocator& cecAllocFunc);

inline nn::Result  Initialize(nn::fnd::IAllocator& cecAllocFunc)
{
    return CecControl::Initialize(cecAllocFunc);
}

inline nn::Result  Initialize(uptr bufferAddress, size_t bufferSize)
{
    return CecControl::Initialize(bufferAddress, bufferSize);
}

/* Please see man pages for details 
 
 
 
                
                
                

 
 
 
 */
nn::Result  InitializeForGetState();

inline nn::Result  InitializeForGetState()
{
    return CecControl::InitializeWithoutNdm();
}

/* Please see man pages for details 
 
 
 
                
                
                

 
 
 
 */
nn::Result  InitializeWithoutNdm();

inline nn::Result  InitializeWithoutNdm()
{
    return CecControl::InitializeWithoutNdm();
}

/* Please see man pages for details 
 
 
 
 
 */
nn::Result  Finalize();

inline nn::Result  Finalize()
{
    return CecControl::Finalize();
}

//

//
//

/* Please see man pages for details 
 

                
                
                
                
                
                
 
 
 
 
 */
nn::Result GetCecRecvEventHandle( nn::os::Event* event );
inline nn::Result GetCecRecvEventHandle( nn::os::Event* event )
{
    return CecControl::GetCecRecvEventHandle( event );
}

/* Please see man pages for details 
 

                
                
                
                
                
                
 
 
 
 
 */
nn::Result GetCecEvent( nn::os::Event* event );
inline nn::Result GetCecEvent( nn::os::Event* event )
{
    return CecControl::GetCecRecvEventHandle( event );
}


/* Please see man pages for details 
 

                
                
                
                
                
                
                
                
                
                
                
  
 
 
 
 
 
 */
nn::Result GetCecInfoBuffer( u32 cecTitleId, u8 pCecInfoBuffer[], size_t size );
nn::Result GetCecInfoBuffer( u8 pCecInfoBuffer[], size_t size );

inline nn::Result GetCecInfoBuffer( u32 cecTitleId, u8 pCecInfoBuffer[], size_t size )
{
    return CecControl::GetCecInfoBuffer(cecTitleId, pCecInfoBuffer, size );
}

inline nn::Result GetCecInfoBuffer( u8 pCecInfoBuffer[], size_t size )
{
    return CecControl::GetCecInfoBuffer(0, pCecInfoBuffer, size );
}

//

/* Please see man pages for details 
 
 
 
 
 
 
 */
nn::Result GetExchangeCount( s32* count );
inline nn::Result GetExchangeCount( s32* count )
{
    return CecControl::GetExchangeCount( count );
}


/* Please see man pages for details 
  
                

                
                
                
                

  
                        
  
 
*/
nn::cec::CTR::TitleId MakeCecTitleId(bit32 id, bit8 variation = 0x0);
inline nn::cec::CTR::TitleId MakeCecTitleId(bit32 id, bit8 variation)
{
    return CecControl::MakeCecTitleId(id, variation);
}

} // end of namespace CTR
} // end of namespace cec
} // end of namespace nn



#endif  // ifndef NN_CEC_CTR_CEC_CONTROL_H_
