/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ro_Result.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_RO_RO_RESULT_H_
#define NN_RO_RO_RESULT_H_

#include <nn/Handle.h>
#include <nn/Result.h>
#include <nn/types.h>



namespace nn {
namespace ro {

    enum Description
    {
        DESCRIPTION_ALREADY_LOADED = 1,
        DESCRIPTION_ATEXIT_NOT_FOUND,
        DESCRIPTION_BROKEN_OBJECT,
        DESCRIPTION_CONTROL_OBJECT_NOT_FOUND,
        DESCRIPTION_EIT_NODE_NOT_FOUND,
        DESCRIPTION_INVALID_LIST,
        DESCRIPTION_INVALID_OFFSET_RANGE,
        DESCRIPTION_INVALID_REGION,
        DESCRIPTION_INVALID_SIGN,
        DESCRIPTION_INVALID_SIGN2,
        DESCRIPTION_INVALID_STRING,
        DESCRIPTION_INVALID_TARGET,
        DESCRIPTION_NOT_LOADED,
        DESCRIPTION_NOT_REGISTERED,
        DESCRIPTION_OUT_OF_SPACE,
        DESCRIPTION_RANGE_ERROR_AT_EXPORT,
        DESCRIPTION_RANGE_ERROR_AT_HEADER,
        DESCRIPTION_RANGE_ERROR_AT_IMPORT,
        DESCRIPTION_RANGE_ERROR_AT_INDEX_EXPORT,
        DESCRIPTION_RANGE_ERROR_AT_INDEX_IMPORT,
        DESCRIPTION_RANGE_ERROR_AT_INTERNAL_RELOCATION,
        DESCRIPTION_RANGE_ERROR_AT_OFFSET_EXPORT,
        DESCRIPTION_RANGE_ERROR_AT_OFFSET_IMPORT,
        DESCRIPTION_RANGE_ERROR_AT_REFERENCE,
        DESCRIPTION_RANGE_ERROR_AT_SECTION,
        DESCRIPTION_RANGE_ERROR_AT_SYMBOL_EXPORT,
        DESCRIPTION_RANGE_ERROR_AT_SYMBOL_IMPORT,
        DESCRIPTION_REGISTRATION_NOT_FOUND,
        DESCRIPTION_RW_NOT_SUPPORTED,
        DESCRIPTION_STATIC_MODULE,
        DESCRIPTION_TOO_SMALL_SIZE,
        DESCRIPTION_TOO_SMALL_TARGET,
        DESCRIPTION_UNKNOWN_OBJECT_CONTROL,
        DESCRIPTION_UNKNOWN_RELOCATION_TYPE,
        DESCRIPTION_VENEER_REQUIRED,
        DESCRIPTION_VERIFICATION_FAILED,

        DESCRIPTION_MAX_BIT = (1u << 31)
    };


#define NN_RO_DEFINE_RESULT_CONST(name, level, summary, description) NN_DEFINE_RESULT_CONST(name, Result::LEVEL_##level, Result::SUMMARY_##summary, Result::MODULE_NN_RO, description)
    NN_RO_DEFINE_RESULT_CONST( ResultAlreadyInitialized,               USAGE,     INVALID_STATE,    Result::DESCRIPTION_ALREADY_INITIALIZED        );
    NN_RO_DEFINE_RESULT_CONST( ResultAlreadyInitializedInternal,       PERMANENT, INTERNAL,         Result::DESCRIPTION_ALREADY_INITIALIZED        );
    NN_RO_DEFINE_RESULT_CONST( ResultAtexitNotFound,                   PERMANENT, INVALID_ARGUMENT, DESCRIPTION_ATEXIT_NOT_FOUND                   );
    NN_RO_DEFINE_RESULT_CONST( ResultBrokenObject,                     PERMANENT, INVALID_ARGUMENT, DESCRIPTION_BROKEN_OBJECT                      );
    NN_RO_DEFINE_RESULT_CONST( ResultControlObjectNotFound,            PERMANENT, INVALID_ARGUMENT, DESCRIPTION_CONTROL_OBJECT_NOT_FOUND           );
    NN_RO_DEFINE_RESULT_CONST( ResultEitNodeNotFound,                  STATUS,    INTERNAL,         DESCRIPTION_EIT_NODE_NOT_FOUND                 );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidHandle,                    USAGE,     INTERNAL,         Result::DESCRIPTION_INVALID_HANDLE             );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidList,                      PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_INVALID_LIST                       );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidRegion,                    PERMANENT, INVALID_STATE,    DESCRIPTION_INVALID_REGION                     );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidSize,                      PERMANENT, WRONG_ARGUMENT,   Result::DESCRIPTION_INVALID_SIZE               );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidString,                    PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_INVALID_STRING                     );
    NN_RO_DEFINE_RESULT_CONST( ResultInvalidTarget,                    USAGE,     INVALID_ARGUMENT, DESCRIPTION_INVALID_TARGET                     );
    NN_RO_DEFINE_RESULT_CONST( ResultMissAlignedAddress,               PERMANENT, WRONG_ARGUMENT,   Result::DESCRIPTION_MISALIGNED_ADDRESS         );
    NN_RO_DEFINE_RESULT_CONST( ResultMissAlignedSize,                  PERMANENT, WRONG_ARGUMENT,   Result::DESCRIPTION_MISALIGNED_SIZE            );
    NN_RO_DEFINE_RESULT_CONST( ResultNotAuthorized,                    PERMANENT, WRONG_ARGUMENT,   Result::DESCRIPTION_NOT_AUTHORIZED             );
    NN_RO_DEFINE_RESULT_CONST( ResultNotInitialized,                   USAGE,     INVALID_STATE,    Result::DESCRIPTION_NOT_INITIALIZED            );
    NN_RO_DEFINE_RESULT_CONST( ResultNotInitializedInternal,           PERMANENT, INTERNAL,         Result::DESCRIPTION_NOT_INITIALIZED            );
    NN_RO_DEFINE_RESULT_CONST( ResultNotLoaded,                        PERMANENT, INVALID_STATE,    DESCRIPTION_NOT_LOADED                         );
    NN_RO_DEFINE_RESULT_CONST( ResultNotRegistered,                    PERMANENT, INVALID_ARGUMENT, DESCRIPTION_NOT_REGISTERED                     );
    NN_RO_DEFINE_RESULT_CONST( ResultOutOfSpace,                       USAGE,     INTERNAL,         DESCRIPTION_OUT_OF_SPACE                       );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtExport,               PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_EXPORT              );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtHeader,               PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_HEADER              );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtImport,               PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_IMPORT              );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtIndexExport,          PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_INDEX_EXPORT        );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtIndexImport,          PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_INDEX_IMPORT        );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtInternalRelocation,   PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_INTERNAL_RELOCATION );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtOffsetExport,         PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_OFFSET_EXPORT       );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtOffsetImport,         PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_OFFSET_IMPORT       );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtReference,            PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_REFERENCE           );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtSection,              PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_SECTION             );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtSymbolExport,         PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_SYMBOL_EXPORT       );
    NN_RO_DEFINE_RESULT_CONST( ResultRangeErrorAtSymbolImport,         PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_RANGE_ERROR_AT_SYMBOL_IMPORT       );
    NN_RO_DEFINE_RESULT_CONST( ResultRegistrationNotFound,             PERMANENT, INVALID_ARGUMENT, DESCRIPTION_REGISTRATION_NOT_FOUND             );
    NN_RO_DEFINE_RESULT_CONST( ResultRwNotSupported,                   USAGE,     INTERNAL,         DESCRIPTION_RW_NOT_SUPPORTED                   );
    NN_RO_DEFINE_RESULT_CONST( ResultStaticModule,                     PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_STATIC_MODULE                      );
    NN_RO_DEFINE_RESULT_CONST( ResultTooSmallSize,                     USAGE,     INVALID_ARGUMENT, DESCRIPTION_TOO_SMALL_SIZE                     );
    NN_RO_DEFINE_RESULT_CONST( ResultTooSmallTarget,                   USAGE,     INVALID_ARGUMENT, DESCRIPTION_TOO_SMALL_TARGET                   );
    NN_RO_DEFINE_RESULT_CONST( ResultUnknownObjectControl,             PERMANENT, INVALID_ARGUMENT, DESCRIPTION_UNKNOWN_OBJECT_CONTROL             );
    NN_RO_DEFINE_RESULT_CONST( ResultUnknownRelocationType,            PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_UNKNOWN_RELOCATION_TYPE            );
    NN_RO_DEFINE_RESULT_CONST( ResultVeneerRequired,                   PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_VENEER_REQUIRED                    );
    NN_RO_DEFINE_RESULT_CONST( ResultVerificationFailed,               PERMANENT, WRONG_ARGUMENT,   DESCRIPTION_VERIFICATION_FAILED                );
#undef NN_RO_DEFINE_RESULT_CONST



} // end of namespace ro
} // end of namespace nn



#endif  // ifndef NN_RO_RO_RESULT_H_
