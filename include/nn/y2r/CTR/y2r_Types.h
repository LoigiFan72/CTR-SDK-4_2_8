/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     y2r_Types.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_Y2R_CTR_Y2R_Y2RTYPES_H_
#define NN_Y2R_CTR_Y2R_Y2RTYPES_H_

#include <nn/Result.h>

namespace nn {
namespace y2r {
namespace CTR {

    /* Please see man pages for details 
      
    */
    enum InputFormat
    {
        INPUT_YUV422_INDIV_8  = 0, //
        INPUT_YUV420_INDIV_8  = 1, //
        INPUT_YUV422_INDIV_16 = 2, //
        INPUT_YUV420_INDIV_16 = 3, //
        INPUT_YUV422_BATCH    = 4  //
        
    };

    /* Please see man pages for details 
      
    */
    enum OutputFormat
    {
        OUTPUT_RGB_32     = 0, //
        OUTPUT_RGB_24     = 1, //
        OUTPUT_RGB_16_555 = 2, //
        OUTPUT_RGB_16_565 = 3  //
    };

    /* Please see man pages for details 
      
    */
    enum Rotation
    {
        ROTATION_NONE          = 0, //
        ROTATION_CLOCKWISE_90  = 1, //
        ROTATION_CLOCKWISE_180 = 2, //
        ROTATION_CLOCKWISE_270 = 3  //
    };

    /* Please see man pages for details 
      
    */
    enum BlockAlignment
    {
        BLOCK_LINE   = 0, //
        BLOCK_8_BY_8 = 1  //
    };

    /* Please see man pages for details 
      

                    

                
                
                
                
    */
    struct CoefficientParams
    {
        u16  Y_A;
        u16  R_V;
        u16  G_V;
        u16  G_U;
        u16  B_U;
        u16  R_Offset;
        u16  G_Offset;
        u16  B_Offset;
    };

    /* Please see man pages for details 
      
    */
    enum StandardCoefficient
    {
        COEFFICIENT_ITU_R_BT_601 = 0,       //
        COEFFICIENT_ITU_R_BT_709,           //
        COEFFICIENT_ITU_R_BT_601_SCALING,   //
        COEFFICIENT_ITU_R_BT_709_SCALING,   //

        COEFFICIENT_MAX
    };

    /* Please see man pages for details 
      

                
                
                
    */
    struct DitheringWeightParams
    {
        u16   w0_xEven_yEven; //
        u16   w0_xOdd_yEven;  //
        u16   w0_xEven_yOdd;  //
        u16   w0_xOdd_yOdd;   //

        u16   w1_xEven_yEven; //
        u16   w1_xOdd_yEven;  //
        u16   w1_xEven_yOdd;  //
        u16   w1_xOdd_yOdd;   //

        u16   w2_xEven_yEven; //
        u16   w2_xOdd_yEven;  //
        u16   w2_xEven_yOdd;  //
        u16   w2_xOdd_yOdd;   //

        u16   w3_xEven_yEven; //
        u16   w3_xOdd_yEven;  //
        u16   w3_xEven_yOdd;  //
        u16   w3_xOdd_yOdd;   //
    };

    /* Please see man pages for details 
      
    */
    struct PackageParameter
    {
        util::SizedEnum1<InputFormat>             inputFormat;            //
        util::SizedEnum1<OutputFormat>            outputFormat;           //
        util::SizedEnum1<Rotation>                rotation;               //
        util::SizedEnum1<BlockAlignment>          blockAlignment;         //
        s16                                      inputLineWidth;         //
        s16                                      inputLines;             //
        util::SizedEnum1<StandardCoefficient>     standardCoefficientNo;  //
        NN_PADDING1;
        s16                                      alpha;                  //
    };

} // namespace CTR
} // namespace y2r
} // namespace nn

#endif //NN_Y2R_CTR_Y2R_Y2RTYPES_H_
