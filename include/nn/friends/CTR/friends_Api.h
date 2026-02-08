/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     friends_Api.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47424 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FRIENDS_CTR_FRIENDS_API_H_
#define NN_FRIENDS_CTR_FRIENDS_API_H_

/* Please see man pages for details 
    
*/

#include <nn/types.h>

#include <nn/friends/friends_Result.h>
#include <nn/friends/CTR/friends_Types.h>

#include <nn/uds/CTR/uds_Type.h>

#ifdef __cplusplus

namespace nn {
namespace friends {
namespace CTR {

    namespace detail
    {
        // Library initialization and finalization
        Result Initialize();
        Result Finalize();

        // Check library status
        bool IsInitialized();
        bool HasLoggedIn();

        // Manage connections
        Result Login( os::Event* pEvent );
        Result Logout();

        // Get local system information
        PrincipalId     GetMyPrincipalId();
        bool IsMyPreferenceValid();
        Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName, bool* pIsShowPlayedGame );
        Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName );
        Result GetMyProfile( Profile* pProfile );
        Result GetMyPresence( MyPresence* pMyPresence );
        Result GetMyScreenName( char16 screenName[SCREEN_NAME_SIZE] );
        Result GetMyMii( MiiData* pMiiData );

        // Get friend information
        Result GetFriendKeyList( FriendKey* pFriendKeyList, size_t* pNum, size_t offset, size_t size );
        Result GetFriendPresence( FriendPresence* pFriendPresenceList, const FriendKey* pFriendKeyList, size_t size );
        Result GetFriendPresence( FriendPresence* pFriendPresenceList, const PrincipalId* pPrincipalIdList, size_t size );
        Result GetFriendScreenName( char16 (*pScreenNameList)[SCREEN_NAME_SIZE], const FriendKey* pFriendKeyList, size_t size, bool replaceForeignCharacters, u8* pFontRegionList );
        Result GetFriendScreenName( char16 (*pScreenNameList)[SCREEN_NAME_SIZE], const PrincipalId* pPrincipalIdList, size_t size, bool replaceForeignCharacters, u8* pFontRegionList );
        Result GetFriendMii( MiiData* pMiiDataList, const FriendKey* pFriendKeyList, size_t size );
        Result GetFriendMii( MiiData* pMiiDataList, const PrincipalId* pPrincipalIdList, size_t size );
        Result GetFriendProfile( Profile* pProfileList, const FriendKey* pFriendKeyList, size_t size );
        Result GetFriendProfile( Profile* pProfileList, const PrincipalId* pPrincipalIdList, size_t size );
        Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const FriendKey* pFriendKeyList, size_t size );
        Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const PrincipalId* pPrincipalIdList, size_t size );
        Result UnscrambleLocalFriendCode( LocalFriendCode* pLocalFriendCodeList, const uds::CTR::ScrambledLocalFriendCode* pScrambledLocalFriendCodeList, size_t size );

        // Update local information
        Result UpdateGameModeDescription( const char16 description[MODE_DESCRIPTION_SIZE] );
        Result UpdateGameMode( const GameMode& gameMode, const char16 description[MODE_DESCRIPTION_SIZE] );

        // Get notification contents
        Result AttachToEventNotification( nn::os::Event* pEvent );
        Result SetNotificationMask( bit32 mask );
        u32 GetEventNotification( EventNotification* pEventNotificationList, size_t size, bool* pHasOverflowed );
        Result GetLastResponseResult();

        // Get error code
        u32 ResultToErrorCode( const Result& result );

        // Join-in
        bool IsFromFriendList( FriendKey* pFriendKey );

        // Friend registration
        Result GetMyApproachContext( ApproachContext* pApproachContext );
        Result AddFriendWithApproach( os::Event* pEvent, const ApproachContext& approachContext );
        Result GetApproachContextScreenName( char16 screenName[SCREEN_NAME_SIZE], const ApproachContext& approachContext, bool replaceForeignCharacters, u8* pFontRegion );
        Result GetApproachContextMii( MiiData* pMiiData, const ApproachContext& approachContext );
    }

    namespace
    {
        static const char PORT_NAME_USER[]  = "frd:u";
    }

    /*-------------------------------------------------------------------
    Library initialization/finalization
    -------------------------------------------------------------------*/

    /* Please see man pages for details 
    

    

    
    
    */
    Result Initialize();
    inline Result Initialize()
    {
        return detail::Initialize();
    }

    /* Please see man pages for details 
    

                    
                    
                    

    

    
    
    */
    Result Finalize();
    inline Result Finalize()
    {
        return detail::Finalize();
    }

    /* Please see man pages for details 
    

    

    
    
    */
    bool IsInitialized();
    inline bool IsInitialized()
    {
        return detail::IsInitialized();
    }

    /* Please see man pages for details 
    

                    

    
                    

    
    
    */
    bool HasLoggedIn();
    inline bool HasLoggedIn()
    {
        return detail::HasLoggedIn();
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

    

    

    
    
    
    
    
    
    */
    Result Login( os::Event* pEvent );
    inline Result Login( os::Event* pEvent )
    {
        return detail::Login( pEvent );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    

    

    
    
    
    */
    Result Logout();
    inline Result Logout()
    {
        return detail::Logout();
    }

    /* Please see man pages for details 
    

    
                    
                    

    
    
    */
    PrincipalId GetMyPrincipalId();
    inline PrincipalId GetMyPrincipalId()
    {
        return detail::GetMyPrincipalId();
    }

    /* Please see man pages for details 
    

    
                    

    
    
    */
    bool IsMyPreferenceValid();
    inline bool IsMyPreferenceValid()
    {
        return detail::IsMyPreferenceValid();
    }

    /* Please see man pages for details 
    
    

                    
                    

    
    
    

    

    
    
    
    
    */
    Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName, bool* pIsShowPlayedGame ) NN_ATTRIBUTE_DEPRECATED;
    inline Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName, bool* pIsShowPlayedGame )
    {
        return detail::GetMyPreference( pIsPublicMode, pIsShowGameName, pIsShowPlayedGame );
    }

    /* Please see man pages for details 
    

    
    

    

    
    
    
    
    */
    Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName );
    inline Result GetMyPreference( bool* pIsPublicMode, bool* pIsShowGameName )
    {
        return detail::GetMyPreference( pIsPublicMode, pIsShowGameName );
    }

    /* Please see man pages for details 
    

    

    

    
    
    
    
    */
    Result GetMyProfile( Profile* pProfile );
    inline Result GetMyProfile( Profile* pProfile )
    {
        return detail::GetMyProfile( pProfile );
    }

    /* Please see man pages for details 
    

    

    

    
    
    
    
    */
    Result GetMyPresence( MyPresence* pMyPresence );
    inline Result GetMyPresence( MyPresence* pMyPresence )
    {
        return detail::GetMyPresence( pMyPresence );
    }

    /* Please see man pages for details 
    

    

                    
                    

    

    
    
    
    
    */
    Result GetMyScreenName( char16 screenName[SCREEN_NAME_SIZE] );
    inline Result GetMyScreenName( char16 screenName[SCREEN_NAME_SIZE] )
    {
        return detail::GetMyScreenName( screenName );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    

    

    

    
    
    
    
    */
    Result GetMyMii( MiiData* pMiiData );
    inline Result GetMyMii( MiiData* pMiiData )
    {
        return detail::GetMyMii( pMiiData );
    }

    /* Please see man pages for details 
    

                    

    
    
    
    

    

    
    
    
    
    
    */
    Result GetFriendKeyList( FriendKey* pFriendKeyList, size_t* pNum, size_t offset = 0, size_t size = FRIEND_LIST_SIZE );
    inline Result GetFriendKeyList( FriendKey* pFriendKeyList, size_t* pNum, size_t offset, size_t size)
    {
        return detail::GetFriendKeyList( pFriendKeyList, pNum, offset, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendPresence( FriendPresence* pFriendPresenceList, const FriendKey* pFriendKeyList, size_t size = 1 );
    inline Result GetFriendPresence( FriendPresence* pFriendPresenceList, const FriendKey* pFriendKeyList, size_t size)
    {
        return detail::GetFriendPresence( pFriendPresenceList, pFriendKeyList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendPresence( FriendPresence* pFriendPresenceList, const PrincipalId* pPrincipalIdList, size_t size = 1 );
    inline Result GetFriendPresence( FriendPresence* pFriendPresenceList, const PrincipalId* pPrincipalIdList, size_t size)
    {
        return detail::GetFriendPresence( pFriendPresenceList, pPrincipalIdList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    

    
    
    
    
    

    

    
    
    
    
    
    */
    Result GetFriendScreenName(
        char16           (*pScreenNameList)[SCREEN_NAME_SIZE],
        const FriendKey* pFriendKeyList,
        size_t           size = 1,
        bool             replaceForeignCharacters = true,
        u8*              pFontRegionList = NULL
    );
    inline Result GetFriendScreenName(
        char16           (*pScreenNameList)[SCREEN_NAME_SIZE],
        const FriendKey* pFriendKeyList,
        size_t           size,
        bool             replaceForeignCharacters,
        u8*              pFontRegionList
    )
    {
        return detail::GetFriendScreenName( pScreenNameList, pFriendKeyList, size, replaceForeignCharacters, pFontRegionList );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    

    
    
    
    
    

    

    
    
    
    
    
    */
    Result GetFriendScreenName(
        char16             (*pScreenNameList)[SCREEN_NAME_SIZE],
        const PrincipalId* pPrincipalIdList,
        size_t             size = 1,
        bool               replaceForeignCharacters = true,
        u8*                pFontRegionList = NULL
    );
    inline Result GetFriendScreenName(
        char16             (*pScreenNameList)[SCREEN_NAME_SIZE],
        const PrincipalId* pPrincipalIdList,
        size_t             size,
        bool               replaceForeignCharacters,
        u8*                pFontRegionList
    )
    {
        return detail::GetFriendScreenName( pScreenNameList, pPrincipalIdList, size, replaceForeignCharacters, pFontRegionList );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendMii( MiiData* pMiiDataList, const FriendKey* pFriendKeyList, size_t size = 1 );
    inline Result GetFriendMii( MiiData* pMiiDataList, const FriendKey* pFriendKeyList, size_t size)
    {
        return detail::GetFriendMii( pMiiDataList, pFriendKeyList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendMii( MiiData* pMiiDataList, const PrincipalId* pPrincipalIdList, size_t size = 1);
    inline Result GetFriendMii( MiiData* pMiiDataList, const PrincipalId* pPrincipalIdList, size_t size)
    {
        return detail::GetFriendMii( pMiiDataList, pPrincipalIdList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    

                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendProfile( Profile* pProfileList, const FriendKey* pFriendKeyList, size_t size = 1 );
    inline Result GetFriendProfile( Profile* pProfileList, const FriendKey* pFriendKeyList, size_t size)
    {
        return detail::GetFriendProfile( pProfileList, pFriendKeyList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    

                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendProfile( Profile* pProfileList, const PrincipalId* pPrincipalIdList, size_t size = 1 );
    inline Result GetFriendProfile( Profile* pProfileList, const PrincipalId* pPrincipalIdList, size_t size)
    {
        return detail::GetFriendProfile( pProfileList, pPrincipalIdList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const FriendKey* pFriendKeyList, size_t size = 1 );
    inline Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const FriendKey* pFriendKeyList, size_t size)
    {
        return detail::GetFriendAttributeFlags( pAttributeFlagsList, pFriendKeyList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const PrincipalId* pPrincipalIdList, size_t size = 1 );
    inline Result GetFriendAttributeFlags( bit32* pAttributeFlagsList, const PrincipalId* pPrincipalIdList, size_t size)
    {
        return detail::GetFriendAttributeFlags( pAttributeFlagsList, pPrincipalIdList, size );
    }

    /* Please see man pages for details 
    

                    
                    

    
    
    

    

    
    
    
    
    
    */
    Result UnscrambleLocalFriendCode( LocalFriendCode* pLocalFriendCodeList, const uds::CTR::ScrambledLocalFriendCode* pScrambledLocalFriendCodeList, size_t size = 1);
    inline Result UnscrambleLocalFriendCode( LocalFriendCode* pLocalFriendCodeList, const uds::CTR::ScrambledLocalFriendCode* pScrambledLocalFriendCodeList, size_t size )
    {
        return detail::UnscrambleLocalFriendCode( pLocalFriendCodeList, pScrambledLocalFriendCodeList, size );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                      
                      
                      
                      
                    
                    
                    
                    
                    
                    
                    
                    

    

    

    
    
    
    
    
    */
    Result UpdateGameModeDescription( const char16 description[MODE_DESCRIPTION_SIZE] );
    inline Result UpdateGameModeDescription( const char16 description[MODE_DESCRIPTION_SIZE] )
    {
        return detail::UpdateGameModeDescription( description );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                      
                      
                      
                      
                    
                    
                    
                    
                    
                    

    
    

    
    */
    Result UpdateGameMode( const GameMode& gameMode, const char16 description[MODE_DESCRIPTION_SIZE] );
    inline Result UpdateGameMode( const GameMode& gameMode, const char16 description[MODE_DESCRIPTION_SIZE] )
    {
        return detail::UpdateGameMode( gameMode, description );
    }


    /* Please see man pages for details 
    

                    

    

    

    
    
    
    
    
    */
    Result AttachToEventNotification( nn::os::Event* pEvent );
    inline Result AttachToEventNotification( nn::os::Event* pEvent )
    {
        return detail::AttachToEventNotification( pEvent );
    }

    /* Please see man pages for details 
    

                    
                    

                    

    

    

    
    
    
    */
    Result SetNotificationMask( bit32 mask );
    inline Result SetNotificationMask( bit32 mask )
    {
        return detail::SetNotificationMask( mask );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    

    
    
    

    
    */
    u32 GetEventNotification(
        EventNotification* pEventNotificationList,
        size_t             size = 1,
        bool*              pHasOverflowed = NULL
    );
    inline u32 GetEventNotification(
        EventNotification* pEventNotificationList,
        size_t             size,
        bool*              pHasOverflowed
    )
    {
        return detail::GetEventNotification( pEventNotificationList, size, pHasOverflowed );
    }

    /* Please see man pages for details 
    

                    
                    
                    

    

    
    
    
    */
    Result GetLastResponseResult();
    inline Result GetLastResponseResult()
    {
        return detail::GetLastResponseResult();
    }

    /* Please see man pages for details 
    

    

    
                    
                    

    
    
    */
    u32 ResultToErrorCode( const Result& result );
    inline u32 ResultToErrorCode( const Result& result )
    {
        return detail::ResultToErrorCode( result );
    }


    /* Please see man pages for details 
    

                    

    

    

    
    
    */
    bool IsFromFriendList( FriendKey* pFriendKey );
    inline bool IsFromFriendList( FriendKey* pFriendKey )
    {
        return detail::IsFromFriendList( pFriendKey );
    }


    /* Please see man pages for details 
    

                    
                    
                    
                    

    

    

    
    
    
    
    
    
    
    */
    Result GetMyApproachContext( ApproachContext* pApproachContext );
    inline Result GetMyApproachContext( ApproachContext* pApproachContext )
    {
        return detail::GetMyApproachContext( pApproachContext );
    }

    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    

    
    

    

    
    
    
    
    
    
    
    
    
    */
    Result AddFriendWithApproach( os::Event* pEvent, const ApproachContext& approachContext );
    inline Result AddFriendWithApproach( os::Event* pEvent, const ApproachContext& approachContext )
    {
        return detail::AddFriendWithApproach( pEvent, approachContext );
    }

    /* Please see man pages for details 
    

    
    
    
    

    

    
    
    
    
    
    */
    Result GetApproachContextScreenName(
        char16                  screenName[SCREEN_NAME_SIZE],
        const ApproachContext&  approachContext,
        bool                    replaceForeignCharacters = true,
        u8*                     pFontRegion = NULL
    );
    inline Result GetApproachContextScreenName(
        char16                  screenName[SCREEN_NAME_SIZE],
        const ApproachContext&  approachContext,
        bool                    replaceForeignCharacters,
        u8*                     pFontRegion
    )
    {
        return detail::GetApproachContextScreenName( screenName, approachContext, replaceForeignCharacters, pFontRegion );
    }

    /* Please see man pages for details 
    

    
    

    

    
    
    
    
    
    */
    Result GetApproachContextMii( MiiData* pMiiData, const ApproachContext& approachContext );
    inline Result GetApproachContextMii( MiiData* pMiiData, const ApproachContext& approachContext )
    {
        return detail::GetApproachContextMii( pMiiData, approachContext );

    }

} // end of namespace CTR
} // end of namespace friends
} // end of namespace nn

#endif // __cplusplus

// Below is the C declaration

#include <nn/util/detail/util_CLibImpl.h>

/* Please see man pages for details 
    

    
*/



/*  

*/

#endif  // ifndef NN_FRIENDS_CTR_FRIENDS_API_H_
