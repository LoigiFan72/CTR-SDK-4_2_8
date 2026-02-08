/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     friends_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FRIENDS_CTR_FRIENDS_TYPES_H_
#define NN_FRIENDS_CTR_FRIENDS_TYPES_H_

#include <nn/types.h>
#include <nn/fnd.h>

/* Please see man pages for details 
  
  
*/

#define NN_FRIENDS_INVALID_PRINCIPAL_ID             (0)     //
#define NN_FRIENDS_INVALID_LOCAL_FRIEND_CODE        (0ULL)  //

#define NN_FRIENDS_SCREEN_NAME_SIZE                 (11)    //
#define NN_FRIENDS_MODE_DESCRIPTION_SIZE            (128)   //
#define NN_FRIENDS_MII_SIZE                         (96)    //
#define NN_FRIENDS_APPLICATION_ARG_SIZE             (20)
#define NN_FRIENDS_FRIEND_LIST_SIZE                 (100)   //
#define NN_FRIENDS_APPROACH_CONTEXT_SIZE            (512)

#define NN_FRIENDS_INVALID_GAME_ID                  (0)
#define NN_FRIENDS_INVALID_GROUP_ID                 (0)

#define NN_FRIENDS_JOIN_AVAILABILITY_NOT_JOINABLE_BIT   (0x80000000U)

/* Please see man pages for details 
  
*/
enum nnfriendsPlatformCode
{
    NN_FRIENDS_PLATFORM_CTR = 2        //
};
typedef enum nnfriendsPlatformCode nnfriendsPlatformCode;

/* Please see man pages for details 
  
*/
enum nnfriendsAttributeFlag
{
    NN_FRIENDS_ATTRIBUTE_FLAG_ESTABLISHED           = 1 << 0,   //
    NN_FRIENDS_ATTRIBUTE_FLAG_REMOTE_ACCESSIBLE     = 1 << 1    //
};
typedef enum nnfriendsAttributeFlag nnfriendsAttributeFlag;

/* Please see man pages for details 
  
*/
enum nnfriendsNotificationType
{
    NN_FRIENDS_NOTIFICATION_NONE = 0,                   //
    NN_FRIENDS_NOTIFICATION_ONLINE,                     //
    NN_FRIENDS_NOTIFICATION_OFFLINE,                    //
    NN_FRIENDS_NOTIFICATION_FRIEND_ONLINE,              //
    NN_FRIENDS_NOTIFICATION_FRIEND_PRESENCE,            //
    NN_FRIENDS_NOTIFICATION_FRIEND_MII,                 //
    NN_FRIENDS_NOTIFICATION_FRIEND_PROFILE,             //
    NN_FRIENDS_NOTIFICATION_FRIEND_OFFLINE,             //
    NN_FRIENDS_NOTIFICATION_BECOME_FRIEND,              //
    NN_FRIENDS_NOTIFICATION_INVITATION                  //
};
typedef enum nnfriendsNotificationType nnfriendsNotificationType;

/* Please see man pages for details 
  
*/
enum nnfriendsNotificationMask
{
    NN_FRIENDS_NOTIFICATION_MASK_ONLINE                  = 1 << 0,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_OFFLINE                 = 1 << 1,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_FRIEND_ONLINE           = 1 << 2,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_FRIEND_PRESENCE         = 1 << 3,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_FRIEND_MII              = 1 << 4,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_FRIEND_PROFILE          = 1 << 5,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_FRIEND_OFFLINE          = 1 << 6,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_BECOME_FRIEND           = 1 << 7,                                                  //
    NN_FRIENDS_NOTIFICATION_MASK_INVITATION              = 1 << 8,                                                  //

    NN_FRIENDS_NOTIFICATION_MASK_DEFAULT                 = NN_FRIENDS_NOTIFICATION_MASK_ONLINE          |
                                                           NN_FRIENDS_NOTIFICATION_MASK_OFFLINE         |
                                                           NN_FRIENDS_NOTIFICATION_MASK_FRIEND_ONLINE   |
                                                           NN_FRIENDS_NOTIFICATION_MASK_FRIEND_MII      |
                                                           NN_FRIENDS_NOTIFICATION_MASK_FRIEND_PROFILE  |
                                                           NN_FRIENDS_NOTIFICATION_MASK_FRIEND_OFFLINE  |
                                                           NN_FRIENDS_NOTIFICATION_MASK_BECOME_FRIEND               //
};
typedef enum nnfriendsNotificationMask nnfriendsNotificationMask;

enum nnfriendsFontRegion
{
    NN_FRIENDS_FONT_REGION_JP_US_EU,
    NN_FRIENDS_FONT_REGION_CHINA,
    NN_FRIENDS_FONT_REGION_KOREA,
    NN_FRIENDS_FONT_REGION_TAIWAN,

    NN_FRIENDS_FONT_REGION_UNKNOWN = 255
};
typedef enum nnfriendsFontRegion nnfriendsFontRegion;

/* Please see man pages for details 
  
*/
enum nnfriendsJoinAvailability
{
    NN_FRIENDS_JOIN_AVAILABILITY_JOINABLE          = 0,                                                     //
    NN_FRIENDS_JOIN_AVAILABILITY_JOINABLE_APP_ONLY = 1,                                                     //
    NN_FRIENDS_JOIN_AVAILABILITY_NOT_JOINABLE      = (NN_FRIENDS_JOIN_AVAILABILITY_NOT_JOINABLE_BIT | 0)    //
};
typedef enum nnfriendsJoinAvailability nnfriendsJoinAvailability;

/* Please see man pages for details 
  
*/
enum nnfriendsMatchmakeSystemType
{
    NN_FRIENDS_MATCHMAKE_SYSTEM_TYPE_INVALID = 0,       //
    NN_FRIENDS_MATCHMAKE_SYSTEM_TYPE_ANYBODY,           //
    NN_FRIENDS_MATCHMAKE_SYSTEM_TYPE_FRIEND,            //
    NN_FRIENDS_MATCHMAKE_SYSTEM_TYPE_FRIEND_INVITED,    //
    NN_FRIENDS_MATCHMAKE_SYSTEM_TYPE_INVITED            //
};
typedef enum nnfriendsMatchmakeSystemType nnfriendsMatchmakeSystemType;

/////////////////////////////////////////////////////////////////////////

/* Please see man pages for details */
typedef u32 nnfriendsPrincipalId;
/* Please see man pages for details */
typedef u64 nnfriendsLocalFriendCode;

/* Please see man pages for details 
  
*/
struct nnfriendsFriendKey
{
    nnfriendsPrincipalId     principalId;           //
    NN_PADDING4;                                    //
    nnfriendsLocalFriendCode localFriendCode;       //

#ifdef __cplusplus
    inline void initialize()
    {
        this->principalId     = NN_FRIENDS_INVALID_PRINCIPAL_ID;
        this->localFriendCode = NN_FRIENDS_INVALID_LOCAL_FRIEND_CODE;
    }

    inline void initialize( nnfriendsPrincipalId principalId )
    {
        this->principalId     = principalId;
        this->localFriendCode = NN_FRIENDS_INVALID_LOCAL_FRIEND_CODE;
    }

    inline void initialize( nnfriendsLocalFriendCode localFriendCode )
    {
        this->principalId     = NN_FRIENDS_INVALID_PRINCIPAL_ID;
        this->localFriendCode = localFriendCode;
    }

    inline void initialize( nnfriendsPrincipalId principalId, nnfriendsLocalFriendCode localFriendCode )
    {
        this->principalId     = principalId;
        this->localFriendCode = localFriendCode;
    }

    inline nnfriendsFriendKey() {}
    inline nnfriendsFriendKey( nnfriendsPrincipalId     principalId )     { initialize(principalId);     }
    inline nnfriendsFriendKey( nnfriendsLocalFriendCode localFriendCode ) { initialize(localFriendCode); }
    inline nnfriendsFriendKey( nnfriendsPrincipalId principalId, nnfriendsLocalFriendCode localFriendCode ) { initialize(principalId, localFriendCode); }
#endif
};
typedef struct nnfriendsFriendKey nnfriendsFriendKey;

/* Please see man pages for details 
  
*/
struct nnfriendsProfile
{
    u8 region;      //
    u8 country;     //
    u8 area;        //
    u8 language;    //
    u8 platform;    //
    NN_PADDING3;    //
};
typedef struct nnfriendsProfile nnfriendsProfile;

/* Please see man pages for details 
  

         
*/
struct nnfriendsMiiData
{
    union {
        u8  data[NN_FRIENDS_MII_SIZE];                      //
        u32 value32[NN_FRIENDS_MII_SIZE / sizeof(u32)];     //
    };
};
typedef struct nnfriendsMiiData nnfriendsMiiData;

/* Please see man pages for details 
  
*/
struct nnfriendsGameMode
{
    u32                  joinAvailabilityFlag;                              //
    u32                  matchmakeSystemType;                               //
    u32                  joinGameId;                                        //
    u32                  joinGameMode;                                      //
    nnfriendsPrincipalId ownerPrincipalId;                                  //
    u32                  joinGroupId;                                       //
    u8                   applicationArg[NN_FRIENDS_APPLICATION_ARG_SIZE];   //
};
typedef struct nnfriendsGameMode nnfriendsGameMode;

/* Please see man pages for details 
  
*/
struct nnfriendsMyPresence
{
    nnfriendsGameMode gameMode;                                             //
    char16            modeDescription[NN_FRIENDS_MODE_DESCRIPTION_SIZE];    //
};
typedef struct nnfriendsMyPresence nnfriendsMyPresence;

/* Please see man pages for details 
  
*/
struct nnfriendsFriendPresence
{
    nnfriendsGameMode gameMode;                                 //
    bool              isOnline;                                 //
    bool              isInvitingMe;                             //
    bool              isValid;                                  //
    NN_PADDING1;                                                //

#ifdef __cplusplus
    /* Please see man pages for details 
    

                    
                    
                    
                    
                    
                    

    

    
                    
                    
    */
    bool IsJoinable( bit64 joinGameModeMask ) const;

    /* Please see man pages for details 
    
    

                    

    
    

    
                    
                    
    */
    bool IsJoinable( u32 joinGameId, bit64 joinGameModeMask ) const;
#endif
};
typedef struct nnfriendsFriendPresence nnfriendsFriendPresence;

/* Please see man pages for details 
  
*/
struct nnfriendsEventNotification
{
    u8                 type;            //
    NN_PADDING3;                        //
    NN_PADDING4;                        //
    nnfriendsFriendKey friendKey;       //
};
typedef struct nnfriendsEventNotification nnfriendsEventNotification;

/* Please see man pages for details 
  
*/
struct nnfriendsApproachContext
{
    union
    {
        u8  data[NN_FRIENDS_APPROACH_CONTEXT_SIZE];                     //
        u32 data32[NN_FRIENDS_APPROACH_CONTEXT_SIZE / sizeof(u32)];     //
    };
};
typedef struct nnfriendsApproachContext nnfriendsApproachContext;

/*  

*/

#ifdef __cplusplus

namespace nn {
namespace friends {
namespace CTR {

    namespace detail {

    } // end of namespace detail

    /* Please see man pages for details */
    typedef ::nnfriendsPrincipalId                    PrincipalId;
    /* Please see man pages for details */
    typedef ::nnfriendsLocalFriendCode                LocalFriendCode;

    static const PrincipalId     INVALID_PRINCIPAL_ID         = NN_FRIENDS_INVALID_PRINCIPAL_ID;            //
    static const LocalFriendCode INVALID_LOCAL_FRIEND_CODE    = NN_FRIENDS_INVALID_LOCAL_FRIEND_CODE;       //

    static const u32 SCREEN_NAME_SIZE         = NN_FRIENDS_SCREEN_NAME_SIZE;        //
    static const u32 MODE_DESCRIPTION_SIZE    = NN_FRIENDS_MODE_DESCRIPTION_SIZE;   //
    static const u32 MII_SIZE                 = NN_FRIENDS_MII_SIZE;                //
    static const u32 APPLICATION_ARG_SIZE     = NN_FRIENDS_APPLICATION_ARG_SIZE;
    static const u32 FRIEND_LIST_SIZE         = NN_FRIENDS_FRIEND_LIST_SIZE;        //
    static const u32 APPROACH_CONTEXT_SIZE    = NN_FRIENDS_APPROACH_CONTEXT_SIZE;

    static const u32 INVALID_GAME_ID          = NN_FRIENDS_INVALID_GAME_ID;
    static const u32 INVALID_GROUP_ID         = NN_FRIENDS_INVALID_GROUP_ID;

    static const u32 JOIN_AVAILABILITY_NOT_JOINABLE_BIT = NN_FRIENDS_JOIN_AVAILABILITY_NOT_JOINABLE_BIT;

    /////////////////////////////////////////////////////////////////////////

    /* Please see man pages for details 
      
    */
    enum PlatformCode
    {
        PLATFORM_CTR = 2        //
    };
    typedef enum PlatformCode PlatformCode;

    /* Please see man pages for details 
      
    */
    enum AttributeFlag
    {
        ATTRIBUTE_FLAG_ESTABLISHED          = 1 << 0,   //
        ATTRIBUTE_FLAG_REMOTE_ACCESSIBLE    = 1 << 1    //
    };
    typedef enum AttributeFlag AttributeFlag;

    /* Please see man pages for details 
      
    */
    enum NotificationType
    {
        NOTIFICATION_NONE = 0,                  //
        NOTIFICATION_ONLINE,                    //
        NOTIFICATION_OFFLINE,                   //
        NOTIFICATION_FRIEND_ONLINE,             //
        NOTIFICATION_FRIEND_PRESENCE,           //
        NOTIFICATION_FRIEND_MII,                //
        NOTIFICATION_FRIEND_PROFILE,            //
        NOTIFICATION_FRIEND_OFFLINE,            //
        NOTIFICATION_BECOME_FRIEND,             //
        NOTIFICATION_INVITATION                 //
    };
    typedef enum NotificationType NotificationType;

    /* Please see man pages for details 
      
    */
    enum NotificationMask
    {
        NOTIFICATION_MASK_ONLINE                  = 1 << 0,                                         //
        NOTIFICATION_MASK_OFFLINE                 = 1 << 1,                                         //
        NOTIFICATION_MASK_FRIEND_ONLINE           = 1 << 2,                                         //
        NOTIFICATION_MASK_FRIEND_PRESENCE         = 1 << 3,                                         //
        NOTIFICATION_MASK_FRIEND_MII              = 1 << 4,                                         //
        NOTIFICATION_MASK_FRIEND_PROFILE          = 1 << 5,                                         //
        NOTIFICATION_MASK_FRIEND_OFFLINE          = 1 << 6,                                         //
        NOTIFICATION_MASK_BECOME_FRIEND           = 1 << 7,                                         //
        NOTIFICATION_MASK_INVITATION              = 1 << 8,                                         //

        NOTIFICATION_MASK_DEFAULT                 = NOTIFICATION_MASK_ONLINE          |
                                                    NOTIFICATION_MASK_OFFLINE         |
                                                    NOTIFICATION_MASK_FRIEND_ONLINE   |
                                                    NOTIFICATION_MASK_FRIEND_MII      |
                                                    NOTIFICATION_MASK_FRIEND_PROFILE  |
                                                    NOTIFICATION_MASK_FRIEND_OFFLINE  |
                                                    NOTIFICATION_MASK_BECOME_FRIEND                 //
    };
    typedef enum NotificationMask NotificationMask;

    enum FontRegion
    {
        FONT_REGION_JP_US_EU,
        FONT_REGION_CHINA,
        FONT_REGION_KOREA,
        FONT_REGION_TAIWAN,

        FONT_REGION_UNKNOWN = 255
    };
    typedef enum FontRegion FontRegion;

    /* Please see man pages for details 
      
    */
    enum JoinAvailability
    {
        JOIN_AVAILABILITY_JOINABLE          = 0,                                        //
        JOIN_AVAILABILITY_JOINABLE_APP_ONLY = 1,                                        //
        JOIN_AVAILABILITY_NOT_JOINABLE      = (JOIN_AVAILABILITY_NOT_JOINABLE_BIT | 0)  //
    };
    typedef enum JoinAvailability JoinAvailability;

    /* Please see man pages for details 
      
    */
    enum MatchmakeSystemType
    {
        MATCHMAKE_SYSTEM_TYPE_INVALID = 0,      //
        MATCHMAKE_SYSTEM_TYPE_ANYBODY,          //
        MATCHMAKE_SYSTEM_TYPE_FRIEND,           //
        MATCHMAKE_SYSTEM_TYPE_FRIEND_INVITED,   //
        MATCHMAKE_SYSTEM_TYPE_INVITED           //
    };
    typedef enum MatchmakeSystemType MatchmakeSystemType;

    /* Please see man pages for details */
    typedef ::nnfriendsFriendKey               FriendKey;
    /* Please see man pages for details */
    typedef ::nnfriendsProfile                 Profile;
    /* Please see man pages for details 

               */
    typedef ::nnfriendsMiiData                 MiiData;

    /* Please see man pages for details */
    typedef ::nnfriendsGameMode                GameMode;
    /* Please see man pages for details */
    typedef ::nnfriendsMyPresence              MyPresence;
    /* Please see man pages for details */
    typedef ::nnfriendsFriendPresence          FriendPresence;

    /* Please see man pages for details */
    typedef ::nnfriendsEventNotification       EventNotification;

    /* Please see man pages for details */
    typedef ::nnfriendsApproachContext         ApproachContext;

} // end of namespace CTR
} // end of namespace friends
} // end of namespace nn

#endif // __cplusplus

#endif  // NN_FRIENDS_CTR_FRIENDS_TYPES_H_
