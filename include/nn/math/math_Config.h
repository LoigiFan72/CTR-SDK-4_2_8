/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Config.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_MATH_CONFIG_H_
#define NN_MATH_CONFIG_H_

#include <nn/types.h>

#define NN_MATH_WARNING NN_WARNING
#define NN_MATH_REPORT NN_LOG

// When NN_SWITCH_ENABLE_MEMBER_NAME_SHORTCUT is defined, NN_MATH_USE_ANONYMOUS_STRUCT is enabled.

#if defined(NN_SWITCH_ENABLE_MEMBER_NAME_SHORTCUT)
  #define NN_MATH_USE_ANONYMOUS_STRUCT
#endif

#ifndef NN_MATH_MINMAXLT_ASSERT
#define NN_MATH_MINMAXLT_ASSERT(exp, min, max) \
            NN_ASSERTMSG( (exp) >= (min) && (exp) < (max), #exp " is out of bounds(%d)\n%d <= "#exp" < %d not satisfied.", static_cast<int>(exp), static_cast<int>(min), static_cast<int>(max))
#endif

#define NN_MATH_AS_INLINE

#if defined(NN_MATH_AS_INLINE)
  #define NN_MATH_INLINE inline
#else
  #define NN_MATH_INLINE 
#endif


/*
#if defined( NN_HARDWARE_CTR ) && ! defined( NN_BUILD_NOOPT )

#if ! defined( NN_MATH_UNUSE_ASM ) && ! defined( NN_MATH_USE_ASM )
  #define NN_MATH_USE_ASM
#endif

#endif
*/

//#define D_BENCH_FUNC      // Use C code with API call during configuration, use with function individual measurements
                            // Use fastest code with API call when not configured, use with API measurement
#define D_MEASURE_SWITCH    // Switch source when compile switch exists in the function
                            // Measure the target function during configuration with "C_FAST"
                            // Measure the target function when not configured with "C_FAST_ALGO"

//------------------------------------------------------------------------------
#define D_ORG               (1) // Original source code
#define D_FAST_C            (2) // Optimized code with C 
#define D_FAST_ASM          (3) // Optimized code by assembler
#define D_FAST_C_ALGO       (4) // Optimized code by modifying algorithms
#define D_FAST_ASM_ALGO     (5) // Optimized code by assembling and modifying algorithms

#if defined( D_BENCH_FUNC ) || defined( NN_BUILD_NOOPT )
//-----------------------------------------------------------------------------
// Set benchmark measurements
#define HERMITE_5_CONFIG                                    D_ORG
#define HERMITE_6_CONFIG                                    D_ORG
#define MTX33COPY_CONFIG                                    D_ORG
#define MTX33MADD_CONFIG                                    D_ORG
#define MTX33MULT_CONFIG                                    D_ORG
#define MTX33TOMTX34_CONFIG                                 D_ORG
#define MTX34ADD_CONFIG                                     D_ORG
#define MTX34CAMERAROTATE_CONFIG                            D_ORG
#define MTX34COPY_CONFIG                                    D_ORG
#define MTX34INVERSE_CONFIG                                 D_ORG
#define MTX34INVTRANSPOSE_34TO34_CONFIG                     D_ORG
#define MTX34LOOKAT_VEC3_CONFIG                             D_ORG
#define MTX34LOOKAT_F32_CONFIG                              D_ORG
#define MTX34MADD_CONFIG                                    D_ORG
#define MTX34MULT_34_CONFIG                                 D_ORG
#define MTX34MULT_F32_CONFIG                                D_ORG
#define MTX34MULTSCALE_RIGHT_CONFIG                         D_ORG
#define MTX34MULTSCALE_LEFT_CONFIG                          D_ORG
#define MTX34MULTTRANSLATE_RIGHT_CONFIG                     D_ORG
#define MTX34MULTTRANSLATE_LEFT_CONFIG                      D_ORG
#define MTX34ROTXYZFIDX_CONFIG                              D_ORG
#define MTX34SCALE_CONFIG                                   D_ORG
#define MTX34TOMTX33_CONFIG                                 D_ORG
#define MTX34TOQUAT_CONFIG                                  D_ORG
#define MTX34TRANSLATE_CONFIG                               D_ORG
#define MTX34TRANSPOSE_34TO34_CONFIG                        D_ORG
#define MTX34TRANSPOSE_34TO43_CONFIG                        D_ORG
#define MTX43ADD_CONFIG                                     D_ORG
#define MTX43COPY_CONFIG                                    D_ORG
#define MTX43MULT_43_CONFIG                                 D_ORG
#define MTX43MULT_F32_CONFIG                                D_ORG
#define MTX43TRANSPOSE_CONFIG                               D_ORG
#define MTX44ADD_ASM_CONFIG                                 D_ORG
#define MTX44COPY_CONFIG                                    D_ORG
#define MTX44FRUSTUM_CONFIG                                 D_ORG
#define MTX44INVERSE_CONFIG                                 D_ORG
#define MTX44MULT_44_CONFIG                                 D_ORG
#define MTX44MULT_F32_CONFIG                                D_ORG
#define MTX44MULTSCALE_RIGHT_CONFIG                         D_ORG
#define MTX44MULTSCALE_LEFT_CONFIG                          D_ORG
#define MTX44MULTTRANSLATE_RIGHT_CONFIG                     D_ORG
#define MTX44MULTTRANSLATE_LEFT_CONFIG                      D_ORG
#define MTX44ORTHO_CONFIG                                   D_ORG
#define MTX44ROTXYZFIDX_CONFIG                              D_ORG
#define MTX44TEXTUREMATRIXFORMAX_CONFIG                     D_ORG
#define MTX44TEXTUREMATRIXFORMAYA_CONFIG                    D_ORG
#define MTX44TEXTUREMATRIXFORSOFTIMAGE_CONFIG               D_ORG
#define MTX44SCALE_CONFIG                                   D_ORG
#define MTX44TRANSLATE_CONFIG                               D_ORG
#define MTX44TRANSPOSE_44_CONFIG                            D_ORG
#define QUATINVERSE_CONFIG                                  D_ORG
#define QUATMULT_CONFIG                                     D_ORG
#define QUATNORMALIZE_CONFIG                                D_ORG
#define QUATTOMTX34_CONFIG                                  D_ORG
#define VEC3NORMALIZE__CONFIG                               D_ORG
#define VEC3TRANSFORM_33XVEC3_CONFIG                        D_ORG
#define VEC3TRANSFORM_34XVEC3_CONFIG                        D_ORG
#define VEC3TRANSFORM_44XVEC3_CONFIG                        D_ORG
#define MTX44PIVOT_CONFIG                                   D_ORG
#define TRIANGULAR_SINCOSIDX_CONFIG                         D_ORG

#ifdef D_MEASURE_SWITCH
#define MTX34ROTAXISRAD__CONFIG                             D_ORG
#define MTX44PERSPECTIVERAD_CONFIG                          D_ORG
#define MTX44ROTAXISRAD__CONFIG                             D_ORG
#else
#define MTX34ROTAXISRAD__CONFIG                             D_FAST_C_ALGO
#define MTX44PERSPECTIVERAD_CONFIG                          D_FAST_C_ALGO
#define MTX44ROTAXISRAD__CONFIG                             D_FAST_C_ALGO

#endif

//-----------------------------------------------------------------------------

#else
//-----------------------------------------------------------------------------
// Set fastest
#define HERMITE_5_CONFIG                                    D_FAST_C
#define HERMITE_6_CONFIG                                    D_FAST_C
#define MTX33COPY_CONFIG                                    D_FAST_ASM
#define MTX33MADD_CONFIG                                    D_FAST_ASM
#define MTX33MULT_CONFIG                                    D_FAST_ASM
#define MTX33TOMTX34_CONFIG                                 D_FAST_C
#define MTX34ADD_CONFIG                                     D_FAST_ASM
#define MTX34CAMERAROTATE_CONFIG                            D_FAST_C
#define MTX34COPY_CONFIG                                    D_FAST_ASM
#define MTX34INVERSE_CONFIG                                 D_FAST_ASM
#define MTX34INVTRANSPOSE_34TO34_CONFIG                     D_FAST_ASM
#define MTX34LOOKAT_VEC3_CONFIG                             D_FAST_C
#define MTX34LOOKAT_F32_CONFIG                              D_FAST_C
#define MTX34MADD_CONFIG                                    D_FAST_ASM
#define MTX34MULT_34_CONFIG                                 D_FAST_ASM
#define MTX34MULT_F32_CONFIG                                D_FAST_ASM
#define MTX34MULTSCALE_RIGHT_CONFIG                         D_FAST_ASM
#define MTX34MULTSCALE_LEFT_CONFIG                          D_FAST_ASM
#define MTX34MULTTRANSLATE_RIGHT_CONFIG                     D_FAST_ASM
#define MTX34MULTTRANSLATE_LEFT_CONFIG                      D_FAST_ASM
#define MTX34ROTXYZFIDX_CONFIG                              D_FAST_C
#define MTX34SCALE_CONFIG                                   D_FAST_C
#define MTX34TOMTX33_CONFIG                                 D_FAST_ASM
#define MTX34TOQUAT_CONFIG                                  D_FAST_C
#define MTX34TRANSLATE_CONFIG                               D_FAST_C
#define MTX34TRANSPOSE_34TO34_CONFIG                        D_FAST_ASM
#define MTX34TRANSPOSE_34TO43_CONFIG                        D_FAST_ASM
#define MTX43ADD_CONFIG                                     D_FAST_ASM
#define MTX43COPY_CONFIG                                    D_FAST_ASM
#define MTX43MULT_43_CONFIG                                 D_FAST_ASM
#define MTX43MULT_F32_CONFIG                                D_FAST_ASM
#define MTX43TRANSPOSE_CONFIG                               D_FAST_ASM
#define MTX44ADD_ASM_CONFIG                                 D_FAST_ASM
#define MTX44COPY_CONFIG                                    D_FAST_ASM
#define MTX44FRUSTUM_CONFIG                                 D_FAST_C
#define MTX44INVERSE_CONFIG                                 D_FAST_C_ALGO
#define MTX44MULT_44_CONFIG                                 D_FAST_ASM
#define MTX44MULT_F32_CONFIG                                D_FAST_ASM
#define MTX44MULTSCALE_RIGHT_CONFIG                         D_FAST_ASM
#define MTX44MULTSCALE_LEFT_CONFIG                          D_FAST_ASM
#define MTX44MULTTRANSLATE_RIGHT_CONFIG                     D_FAST_ASM
#define MTX44MULTTRANSLATE_LEFT_CONFIG                      D_FAST_ASM
#define MTX44ORTHO_CONFIG                                   D_FAST_C
#define MTX44ROTXYZFIDX_CONFIG                              D_FAST_C
#define MTX44SCALE_CONFIG                                   D_FAST_C
#define MTX44TEXTUREMATRIXFORMAX_CONFIG                     D_FAST_C
#define MTX44TEXTUREMATRIXFORMAYA_CONFIG                    D_FAST_C
#define MTX44TEXTUREMATRIXFORSOFTIMAGE_CONFIG               D_FAST_C
#define MTX44TRANSLATE_CONFIG                               D_FAST_C
#define MTX44TRANSPOSE_44_CONFIG                            D_FAST_ASM
#define QUATINVERSE_CONFIG                                  D_FAST_C
#define QUATMULT_CONFIG                                     D_FAST_C
#define QUATNORMALIZE_CONFIG                                D_FAST_C
#define QUATTOMTX34_CONFIG                                  D_FAST_C
#define VEC3NORMALIZE__CONFIG                               D_FAST_C
#define VEC3TRANSFORM_33XVEC3_CONFIG                        D_FAST_ASM
#define VEC3TRANSFORM_34XVEC3_CONFIG                        D_FAST_ASM
#define VEC3TRANSFORM_44XVEC3_CONFIG                        D_FAST_ASM
#define MTX44PIVOT_CONFIG                                   D_FAST_C
#define TRIANGULAR_SINCOSIDX_CONFIG                         D_FAST_ASM

#define MTX34ROTAXISRAD__CONFIG                             D_FAST_C_ALGO
#define MTX44PERSPECTIVERAD_CONFIG                          D_FAST_C_ALGO
#define MTX44ROTAXISRAD__CONFIG                             D_FAST_C_ALGO

//-----------------------------------------------------------------------------
#endif

/* NN_MATH_CONFIG_H_ */
#endif
