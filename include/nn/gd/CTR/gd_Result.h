/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gd_Result.h

  Copyright (C)2011 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef NN_GD_CTR_GD_RESULT_H_
#define NN_GD_CTR_GD_RESULT_H_

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
  
*/
#else
/* Please see man pages for details 
  
*/
#endif

#include <nn/Result.h>
    
namespace nn {
namespace gd {
namespace CTR {

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
typedef enum
{
    // Generic
    GD_RESULT_SUCCESS = 0,
    GD_RESULT_INVALID_PARAMETER,
    GD_RESULT_NULL_PARAMETER,
    GD_RESULT_OUT_OF_RANGE,
    GD_RESULT_OUT_OF_MEMORY,
    GD_RESULT_EXT_MEMORY_ALLOCATION_FAILED,
    GD_RESULT_INVALID_MEMORY_REGION,
    GD_RESULT_INVALID_FUNCTION_CALL,
    GD_RESULT_ALREADY_RELEASED,

    // InputLayout
    GD_RESULT_INPUTLAYOUT_INVALID_STREAM_SLOTS,

    // Texture 2D
    GD_RESULT_TEXTURE2D_INVALID_RESOLUTION,
    GD_RESULT_TEXTURE2D_INVALID_SUBREGION_RESOLUTION,
    GD_RESULT_TEXTURE2D_INVALID_FORMAT,
    GD_RESULT_TEXTURE2D_INVALID_MEMORY_LAYOUT,
    GD_RESULT_TEXTURE2D_INVALID_MEMORY_LOCATION,
    GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX,
    GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX_FOR_MIPMAP_AUTOGENERATION,
    GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_RENDER_TARGET,
    GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_DEPTH_STENCIL_TARGET,
    GD_RESULT_DIFFERENT_RENDER_TARGET_AND_DEPTH_STENCIL_TARGET_RESOLUTION,
    GD_RESULT_TEXTURE2D_INVALID_TEXTURE_UNIT_ID,
    GD_RESULT_TEXTURE2D_INVALID_OFFSET,
    GD_RESULT_RESOURCE_ALREADY_MAPPED,
    GD_RESULT_RESOURCE_WAS_NOT_MAPPED,
    GD_RESULT_NO_TEXTURE_BOUND,
    GD_RESULT_NO_TEXTURE_COORDINATES,

    // Shader
    GD_RESULT_INVALID_SHADER_UNIFORM_NAME,
    GD_RESULT_INVALID_SHADER_UNIFORM,
    GD_RESULT_INVALID_SHADER_SIGNATURE,
    GD_RESULT_INVALID_SHADER_OPERATION,

    //System
    GD_RESULT_GEOMETRY_SHADER_INCOMPATIBLE_WITH_IMMEDIATE_DRAW,
    GD_RESULT_SYSTEM_NO_CMD_LIST_BIND,
    GD_RESULT_SYSTEM_INVALID_CMD_LIST_BIND,
    GD_RESULT_SYSTEM_RECEIVE_ERROR_FROM_GLGETERROR,
    GD_RESULT_SYSTEM_NO_PACKET_TO_RECORD,
    GD_RESULT_SYSTEM_NO_PACKET_RECORDED,
    GD_RESULT_SYSTEM_A_PACKET_IS_ALREADY_BEING_RECORDED,
    GD_RESULT_SYSTEM_INVALID_PACKET_ID,
    GD_RESULT_SYSTEM_REQUEST_LIST_INSERTION_INCOMPATIBLE_WITH_JUMP,

    // Last element. This must be at the end just before GD_RESULT_RESERVED_MAX_U32
    GD_RESULT_LAST,

    // Force enum to be 32bits
    GD_RESULT_RESERVED_MAX_U32 = 0xffffffffu
} gdResult;

// Strings corresponding to the error codes

/* Please see man pages for details */
#define GD_RESULT_SUCCESS_DESCRIPTION                                                      NULL
/* Please see man pages for details */
#define GD_RESULT_INVALID_PARAMETER_DESCRIPTION                                            "ResultInvalidParameter: A parameter is invalid"
/* Please see man pages for details */
#define GD_RESULT_NULL_PARAMETER_DESCRIPTION                                               "ResultNullParameter: A parameter is NULL"
/* Please see man pages for details */
#define GD_RESULT_OUT_OF_RANGE_DESCRIPTION                                                 "ResultOutOfRangeParameter: A parameter is out of range"
/* Please see man pages for details */
#define GD_RESULT_OUT_OF_MEMORY_DESCRIPTION                                                "ResultOutOfMemory: ResultOutOfMemory: Not enough main memory (FCRAM) available"
/* Please see man pages for details */
#define GD_RESULT_EXT_MEMORY_ALLOCATION_FAILED_DESCRIPTION                                 "ResultOutOfMemoryExt: Not enough external memory (VRAM) available"
/* Please see man pages for details */
#define GD_RESULT_INVALID_MEMORY_REGION_DESCRIPTION                                        "ResultInvalidMemoryRegion: Invalid memory region"
/* Please see man pages for details */
#define GD_RESULT_INVALID_FUNCTION_CALL_DESCRIPTION                                        "ResultInvalidFunctionCall: Invalid function call"
/* Please see man pages for details */
#define GD_RESULT_ALREADY_RELEASED_DESCRIPTION                                             "ResultAlreadyReleased: The object has already been released"
/* Please see man pages for details */
#define GD_RESULT_INPUTLAYOUT_INVALID_STREAM_SLOTS_DESCRIPTION                             "ResultInputLayoutInvalidStreamSlots: The input layout stream slots are invalid (must start from 0 and increase 1 by 1)"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_RESOLUTION_DESCRIPTION                                 "ResultInvalidTextureResolution: Invalid texture 2D resolution"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_SUBREGION_RESOLUTION_DESCRIPTION                       "ResultInvalidSubRegionResolution: Invalid area (subregion) resolution"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_FORMAT_DESCRIPTION                                     "ResultInvalidTextureFormat: Invalid texture 2D format"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_MEMORY_LAYOUT_DESCRIPTION                              "ResultInvalidMemoryLayout: Invalid memory layout"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_MEMORY_LOCATION_DESCRIPTION                            "ResultInvalidMemoryLocation: Invalid memory location"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX_DESCRIPTION                             "ResultInvalidTextureMipLevelIndex: Invalid texture 2D mipLevel index"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX_FOR_MIPMAP_AUTOGENERATION_DESCRIPTION   "ResultInvalidTextureMipLevelIndexForMipmapAutoGeneration: Invalid texture 2D mipLevel index for mipmap auto generation"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_RENDER_TARGET_DESCRIPTION          "ResultInvalidTextureFormatForCreatingRenderTarget: Invalid texture 2D format for creating a RenderTarget"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_DEPTH_STENCIL_TARGET_DESCRIPTION   "ResultInvalidTextureFormatForCreatingDepthStencilTarget: Invalid texture 2D format for creating a DepthStencilTarget"
/* Please see man pages for details */
#define GD_RESULT_DIFFERENT_RENDER_TARGET_AND_DEPTH_STENCIL_TARGET_RESOLUTION_DESCRIPTION  "ResultDifferentRenderTargetAndDepthStencilTargetResolution: RenderTarget and DepthStencilTarget resolution are not compatible"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_TEXTURE_UNIT_ID_DESCRIPTION                            "ResultInvalidTextureUnitId: The texture unit id is not valid"
/* Please see man pages for details */
#define GD_RESULT_TEXTURE2D_INVALID_OFFSET_DESCRIPTION                                     "ResultInvalidTextureOffset: The texture 2D resource offset is not valid"
/* Please see man pages for details */
#define GD_RESULT_RESOURCE_ALREADY_MAPPED_DESCRIPTION                                      "ResultResourceAlreadyMapped: The resource is already mapped"
/* Please see man pages for details */
#define GD_RESULT_RESOURCE_WAS_NOT_MAPPED_DESCRIPTION                                      "ResultResourceNotMapped: The resource is not mapped"
/* Please see man pages for details */
#define GD_RESULT_NO_TEXTURE_BOUND_DESCRIPTION                                             "ResultNoTextureBound: A texture unit is activated, but no texture is bound"
/* Please see man pages for details */
#define GD_RESULT_NO_TEXTURE_COORDINATES_DESCRIPTION                                       "ResultNoTextureCoordinates: A texture unit is activated, but has no texture coordinates associated"
/* Please see man pages for details */
#define GD_RESULT_INVALID_SHADER_UNIFORM_NAME_DESCRIPTION                                  "ResultInvalidShaderUniformName: Invalid shader uniform name"
/* Please see man pages for details */
#define GD_RESULT_INVALID_SHADER_UNIFORM_DESCRIPTION                                       "ResultInvalidShaderUniform: Invalid shader uniform"
/* Please see man pages for details */
#define GD_RESULT_INVALID_SHADER_SIGNATURE_DESCRIPTION                                     "ResultInvalidShaderSignature: Invalid shader signature"
/* Please see man pages for details */
#define GD_RESULT_INVALID_SHADER_OPERATION_DESCRIPTION                                     "ResultInvalidShaderOperation: Invalid shader operation"
/* Please see man pages for details */
#define GD_RESULT_GEOMETRY_SHADER_INCOMPATIBLE_WITH_IMMEDIATE_DRAW_DESCRIPTION             "ResultSystemGeometryShaderIncompatibleWithImmediateDraw: The current geometry shader is incompatible with immediate draw"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_NO_CMD_LIST_BIND_DESCRIPTION                                      "ResultSystemNoCmdListBind: No command list bind"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_INVALID_CMD_LIST_BIND_DESCRIPTION                                 "ResultSystemInvalidCmdListBind: Invalid command list bind"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_RECEIVE_ERROR_FROM_GLGETERROR_DESCRIPTION                         "ResultSystemReceiveErrorFromGlGetError: glGetError function returned an error (might be caused by previous nngx/Gd function call)"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_NO_PACKET_TO_RECORD_DESCRIPTION                                   "ResultSystemNoPacketToRecord: No packet to record"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_NO_PACKET_RECORDED_DESCRIPTION                                    "ResultSystemNoPacketRecorded: No packet recorded"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_A_PACKET_IS_ALREADY_BEING_RECORDED_DESCRIPTION                    "ResultSystemAPacketIsAlreadyBeingRecorded: A packet is already being recorded"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_INVALID_PACKET_ID_DESCRIPTION                                     "ResultSystemInvalidPacketId: The packetId is not valid"
/* Please see man pages for details */
#define GD_RESULT_SYSTEM_REQUEST_LIST_INSERTION_INCOMPATIBLE_WITH_JUMP_DESCRIPTION         "ResultSystemRequestListInsertionIncompatibleWithJump: The insertion of any requests into the request list is incompatible with the jump recording"


/* Please see man pages for details 
  
  
*/

// Generic
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSuccess, nn::Result::LEVEL_SUCCESS, nn::Result::SUMMARY_SUCCESS, nn::Result::MODULE_NN_GD, GD_RESULT_SUCCESS);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultOutOfMemory, nn::Result::LEVEL_PERMANENT, nn::Result::SUMMARY_OUT_OF_RESOURCE, nn::Result::MODULE_NN_GD, GD_RESULT_OUT_OF_MEMORY);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultOutOfMemoryExt, nn::Result::LEVEL_PERMANENT, nn::Result::SUMMARY_OUT_OF_RESOURCE, nn::Result::MODULE_NN_GD, GD_RESULT_EXT_MEMORY_ALLOCATION_FAILED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidParameter, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_PARAMETER);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultNullParameter, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_NULL_PARAMETER);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultOutOfRangeParameter, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_OUT_OF_RANGE);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidMemoryRegion, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_MEMORY_REGION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidFunctionCall, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_FUNCTION_CALL);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultAlreadyReleased, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_ALREADY_RELEASED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInputLayoutInvalidStreamSlots, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INPUTLAYOUT_INVALID_STREAM_SLOTS);

// Texture
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureResolution, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_RESOLUTION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidSubRegionResolution, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_SUBREGION_RESOLUTION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureFormat, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_FORMAT);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidMemoryLayout, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_MEMORY_LAYOUT);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidMemoryLocation, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_MEMORY_LOCATION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureMipLevelIndex, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureMipLevelIndexForMipmapAutoGeneration, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_MIPLEVEL_INDEX_FOR_MIPMAP_AUTOGENERATION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureFormatForCreatingRenderTarget, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_RENDER_TARGET);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureFormatForCreatingDepthStencilTarget, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_FORMAT_FOR_CREATING_DEPTH_STENCIL_TARGET);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultDifferentRenderTargetAndDepthStencilTargetResolution, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_DIFFERENT_RENDER_TARGET_AND_DEPTH_STENCIL_TARGET_RESOLUTION);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureUnitId, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_TEXTURE_UNIT_ID);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidTextureOffset, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_TEXTURE2D_INVALID_OFFSET);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultResourceAlreadyMapped, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_RESOURCE_ALREADY_MAPPED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultResourceNotMapped, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_RESOURCE_WAS_NOT_MAPPED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultNoTextureBound, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_NO_TEXTURE_BOUND);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultNoTextureCoordinates, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_NO_TEXTURE_COORDINATES);

// Shader
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidShaderUniformName, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_SHADER_UNIFORM_NAME);

// Shader
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidShaderUniform, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_SHADER_UNIFORM);

// Shader
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidShaderSignature, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_SHADER_SIGNATURE);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultInvalidShaderOperation, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_INVALID_SHADER_OPERATION);

//System
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemGeometryShaderIncompatibleWithImmediateDraw, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_GEOMETRY_SHADER_INCOMPATIBLE_WITH_IMMEDIATE_DRAW);

//System
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemNoCmdListBind, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_NO_CMD_LIST_BIND);

//System
#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemInvalidCmdListBind, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_INVALID_CMD_LIST_BIND);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemReceiveErrorFromGlGetError, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_RECEIVE_ERROR_FROM_GLGETERROR);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemNoPacketToRecord, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_NO_PACKET_TO_RECORD);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemNoPacketRecorded, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_NO_PACKET_RECORDED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemAPacketIsAlreadyBeingRecorded, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_A_PACKET_IS_ALREADY_BEING_RECORDED);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemInvalidPacketId, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_INVALID_PACKET_ID);

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details 
    
    
*/
#else
/* Please see man pages for details 
    
    
*/
#endif
NN_DEFINE_RESULT_CONST(ResultSystemRequestListInsertionIncompatibleWithJump, nn::Result::LEVEL_USAGE, nn::Result::SUMMARY_INVALID_ARGUMENT, nn::Result::MODULE_NN_GD, GD_RESULT_SYSTEM_REQUEST_LIST_INSERTION_INCOMPATIBLE_WITH_JUMP);


/*  

*/

#if NN_GD_DOCUMENT_TYPE == ENGLISH
/* Please see man pages for details */
#else
/* Please see man pages for details */
#endif
#define GD_NNRESULT_IS_FAILURE(nnResult) ((nnResult.value & 0x80000000u) != 0)

}  // namespace CTR
}  // namespace gd
}  // namespace nn

#endif // NN_GD_CTR_GD_RESULT_H_
