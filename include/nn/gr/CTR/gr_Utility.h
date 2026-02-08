/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     gr_Utility.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 49793 $
 *---------------------------------------------------------------------------*/

#ifndef NN_GR_UTILITY_H_
#define NN_GR_UTILITY_H_

#include <nn/types.h>
#include <nn/math.h>
#include <nn/nstd.h>
#include <nn/gx.h>
#include <nn/gx/CTR/gx_CommandAccess.h>

#include <nn/gr/CTR/gr_Prefix.h>

namespace nn
{
    namespace gr
    {
        namespace CTR
        {
            //------------------------------------------------------------------------------

            /* Please see man pages for details 
                
            */
            class CommandBufferJumpHelper
            {
            public:
                /* Please see man pages for details 
                    

                    
                */
                CommandBufferJumpHelper(bit32* address);
                //
                ~CommandBufferJumpHelper();

                /* Please see man pages for details 
                    

                    
                */
                inline size_t GetSize() const { return GetOffsetFromPtr(m_StartPtr, m_CurrentPtr); }

                /* Please see man pages for details 
                    

                    
                */
                inline size_t GetSizeToFirstJump() const { return m_SizeToFirstJump; }

                /* Please see man pages for details 
                    

                    
                */
                inline bit32* GetStartPtr() { return m_StartPtr; }

                /* Please see man pages for details 
                    

                    
                */
                inline bit32* GetCurrentPtr() { return m_CurrentPtr; }

                /* Please see man pages for details 
                    

                    
                */
                void Put(bit32* address) {
                    NN_MIN_ASSERT(reinterpret_cast<u32*>(address), reinterpret_cast<u32*>(m_CurrentPtr));
                    m_CurrentPtr = address;
                }

                /* Please see man pages for details 
                    

                    
                */
                void Put(uptr address)
                {
                    NN_MIN_ASSERT(reinterpret_cast<u32*>(address), reinterpret_cast<u32*>(m_CurrentPtr));
                    m_CurrentPtr = reinterpret_cast<bit32*>(address);
                }

                /* Please see man pages for details 
                    

                    
                    
                */
                void CopyFrom(const bit32* begin, const bit32* end)
                {
                    CopyFrom(begin, end - begin);
                }
                /* Please see man pages for details 
                    

                    
                    
                */
                void CopyFrom(const bit32* begin, int count)
                {
                    nstd::MemCpy(m_CurrentPtr, begin, count * sizeof(bit32));
                    m_CurrentPtr += count;
                }

                /* Please see man pages for details 
                    

                    
                    
                */
                void Jump(uptr subroutine, size_t subroutineSize );

                /* Please see man pages for details 
                    

                    
                */
                void FinalizeJump(bit32* endAddress);

            private:
                //
                bit32* m_CurrentPtr;
                //
                bit32* m_StartPtr;
                //
                bit32* m_ReturnPtr;
                //
                uptr   m_CmdSizePtr;
                //
                u32    m_SizeToFirstJump;

                //
                inline size_t GetOffsetFromPtr( bit32* start, bit32* end ) const
                {
                    return (end - start) * sizeof(bit32);
                }
            };

            /* Please see man pages for details 
                

                
                

                
            */
            bit32* AddDummyDataForCommandBuffer( bit32* command, const size_t addSize );

            //------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
            */
            void CopyMtx34WithHeader(
                f32*  dst,
                const nn::math::MTX34* src,
                bit32   header );

            /* Please see man pages for details 
                

                
                
                
            */
            void CopyMtx44WithHeader(
                f32* dst,
                const nn::math::MTX44* src,
                bit32 header );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                 

                 
                 
                 

                 
             */
            inline bit32* MakeUniformCommandVS( bit32* command, u8 location, const nn::math::MTX34& mtx34 )
            {
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_FLOAT_ADDR );
                CopyMtx34WithHeader( reinterpret_cast<f32*>( command ), &mtx34, PICA_CMD_HEADER_VS_F32( 3 ) );
                return command + 14;
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
             */
            inline bit32* MakeUniformCommandVS( bit32* command, u8 location, const nn::math::MTX44& mtx44 )
            {
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_FLOAT_ADDR );
                CopyMtx44WithHeader( reinterpret_cast<f32*>( command ), &mtx44, PICA_CMD_HEADER_VS_F32( 4 ) );
                return command + 18;
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
             */
            inline bit32* MakeUniformCommandVS( bit32* command, u8 location, const nn::math::VEC4& vec4 )
            {
                // 0x2c0
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_VS_FLOAT_ADDR, 5 );
                // 0x2c1-0x2c4
                *command++ = nn::math::F32AsU32( vec4.w );
                *command++ = nn::math::F32AsU32( vec4.z );
                *command++ = nn::math::F32AsU32( vec4.y );
                *command++ = nn::math::F32AsU32( vec4.x );
                return command;
            }

            
            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                
                
                
                
                
                

                
             */
            inline bit32* MakeUniformCommandVS( bit32* command, u8 location, const nn::math::VEC4 vec4[], const int num )
            {
                const u32 MAX_VS_F32_VEC4_NUM = 64;
                NN_GR_ASSERT( num <= MAX_VS_F32_VEC4_NUM );

                NN_UNUSED_VAR( MAX_VS_F32_VEC4_NUM );

                // 0x2c0
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_FLOAT_ADDR );
                
                // 0x2c1
                *command++ = nn::math::F32AsU32( vec4[0].w );
                *command++ = PICA_CMD_HEADER_VS_F32( num );
                *command++ = nn::math::F32AsU32( vec4[0].z );
                *command++ = nn::math::F32AsU32( vec4[0].y );
                *command++ = nn::math::F32AsU32( vec4[0].x );

                for ( int i = 1; i < num; ++i )
                {
                    *command++ = nn::math::F32AsU32( vec4[i].w );
                    *command++ = nn::math::F32AsU32( vec4[i].z );
                    *command++ = nn::math::F32AsU32( vec4[i].y );
                    *command++ = nn::math::F32AsU32( vec4[i].x );
                }

                *command++ = 0; // Padding
                
                return command;
            }
            
            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
                
                

                
             */
            inline bit32* MakeUniformCommandVS( bit32* command, u8 location, u8 x, u8 y, u8 z )
            {
                *command++ = PICA_CMD_DATA_VS_INT( x, y, z );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_VS_INT0 + location );
                return command;
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
             */
            inline bit32* MakeUniformCommandGS( bit32* command, u8 location, const nn::math::MTX34& mtx34 )
            {
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_FLOAT_ADDR );
                CopyMtx34WithHeader( reinterpret_cast<f32*>( command ), &mtx34, PICA_CMD_HEADER_GS_F32( 3 ) );
                return command + 14;
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
             */
            inline bit32* MakeUniformCommandGS( bit32* command, u8 location, const nn::math::MTX44& mtx44 )
            {
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_FLOAT_ADDR );
                CopyMtx44WithHeader( reinterpret_cast<f32*>( command ), &mtx44, PICA_CMD_HEADER_GS_F32( 4 ) );
                return command + 18;
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                
                
                
                
                

                
             */
            inline bit32* MakeUniformCommandGS( bit32* command, u8 location, const nn::math::VEC4& vec4 )
            {
                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_BURSTSEQ( PICA_REG_GS_FLOAT_ADDR, 5 );
                *command++ = nn::math::F32AsU32( vec4.w ); // a
                *command++ = nn::math::F32AsU32( vec4.z ); // b
                *command++ = nn::math::F32AsU32( vec4.y ); // g
                *command++ = nn::math::F32AsU32( vec4.x ); // r
                return command;
            }
            
            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
                

                
             */
            inline bit32* MakeUniformCommandGS( bit32* command, u8 location, const nn::math::VEC4 vec4[], const int num )
            {
                const u32 MAX_GS_F32_VEC4_NUM = 64;
                NN_GR_ASSERT( num <= MAX_GS_F32_VEC4_NUM );
                
                NN_UNUSED_VAR( MAX_GS_F32_VEC4_NUM );

                *command++ = 0x80000000 | location;
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_FLOAT_ADDR );
                *command++ = nn::math::F32AsU32( vec4[0].w );
                *command++ = PICA_CMD_HEADER_GS_F32( num );
                *command++ = nn::math::F32AsU32( vec4[0].z );
                *command++ = nn::math::F32AsU32( vec4[0].y );
                *command++ = nn::math::F32AsU32( vec4[0].x );

                for ( int i = 1; i < num; ++i )
                {
                    *command++ = nn::math::F32AsU32( vec4[i].w );
                    *command++ = nn::math::F32AsU32( vec4[i].z );
                    *command++ = nn::math::F32AsU32( vec4[i].y );
                    *command++ = nn::math::F32AsU32( vec4[i].x );
                }

                *command++ = 0; // Padding
                
                return command;
            }
            
            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
                
                

                
             */
            inline bit32* MakeUniformCommandGS( bit32* command, u8 location, u8 x, u8 y, u8 z )
            {
                *command++ = PICA_CMD_DATA_GS_INT( x, y, z );
                *command++ = PICA_CMD_HEADER_SINGLE( PICA_REG_GS_INT0 + location );
                return command;
            }
            
            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                

                
            */
            inline u8 FloatToUnsignedByte(
                f32 val
                )
            {
                return ( u8 )( 0.5f + ( val < 0.f ? 0.f : ( 1.f < val ? 1.f : val ) )  * ( 0xff ) );
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u8 FloatToUnsignedByteNoClamp(
                f32 val
                )
            {
                return ( u8 )( 0.5f + val * 0xff );
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u16 Float32ToFloat16( f32 val )
            {
                static const int bias_ = 128 - (1 << (5 - 1));

                u32 uval_ = *( reinterpret_cast<u32*>( &val ) );
                int e_ = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;
                if (e_ >= 0)
                {
                    return ( u16 )( ((uval_ & 0x7fffff) >> (23 - 10)) | (e_ << 10) | ((uval_ >> 31) << (10 + 5)) );
                }
                return ( u16 )((uval_ >> 31) << (10 + 5));
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFloat24( f32 val )
            {
                static const int bias_ = 128 - (1 << (7 - 1));
                u32 uval_   = *( reinterpret_cast<unsigned*>( &val ) );
                s32 e_      = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;

                return e_ >= 0 ? ((uval_ & 0x7fffff) >> (23 - 16)) | (e_ << 16) | ((uval_ >> 31) << (16 + 7)) : ((uval_ >> 31) << (16 + 7));
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFloat20( f32 val )
            {
                static const int bias_ = 128 - (1 << (7 - 1));
                u32 uval_   = *( reinterpret_cast<unsigned*>( &val ) );
                s32 e_      = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;

                return e_ >= 0 ? ((uval_ & 0x7fffff) >> (23 - 12)) | (e_ << 12) | ((uval_ >> 31) << (12 + 7)) : ((uval_ >> 31) << (12 + 7));
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFloat31( f32 val )
            {
                unsigned uval_, m_;
                int e_;
                float f_ = val;
                static const int bias_ = 128 - (1 << (7 - 1));
                uval_ = *( reinterpret_cast<unsigned*>( &f_ ) );
                e_ = (uval_ & 0x7fffffff) ? (((uval_ >> 23) & 0xff) - bias_) : 0;
                m_ = (uval_ & 0x7fffff) >> (23 - 23);
                return e_ >= 0 ? m_ | (e_ << 23) | ((uval_ >> 31) << (23 + 7)) : ((uval_ >> 31) << (23 + 7));
            }

            //------------------------------------------------------------------------------------            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToUnsignedFix24( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

                if (val <= 0 || (v_ & 0x7f800000) == 0x7f800000)
                {
                    return 0;
                }
                else
                {
                    val *= 1 << (24 - 0);

                    if ( val >= (1 << 24) )
                    {
                        return (1 << 24) - 1;
                    }
                    else
                    {
                        return (unsigned)(val);
                    }
                }
            }

            //------------------------------------------------------------------------------------            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToUnsignedFix16( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val) );

                if (val <= 0 || (v_ & 0x7f800000) == 0x7f800000)
                {
                    return 0;
                }
                else
                {
                    val *= 1 << (16 - 0);
                    if ( val >= (1 << 16) )
                    {
                                return (1 << 16) - 1;
                    }
                    else
                    {
                                return (unsigned)( val );
                    }
                }
            }

            //------------------------------------------------------------------------------------            
            /* Please see man pages for details 
                

                

                
            */
            inline u16 Float32ToFix16( f32 val )
            {                
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

                if ( (val == 0.f) || ( (v_ & 0x7f800000) == 0x7f800000 ) )
                {
                    return 0;
                }
                else
                {
                    val += 0.5f * (1 << 4);
                    val *= 1 << (16 - 4);
                    if (val < 0)
                    {
                        val = 0;
                    }
                    else if (val >= (1 << 16))
                    {
                        val = (1 << 16) - 1;
                    }

                    if (val >= (1 << (16 - 1)))
                    {
                        return (unsigned)(val - (1 << (16 - 1)));
                    }
                    else
                    {
                        return (unsigned)(val + (1 << (16 - 1)));
                    }
                }
            }

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToUnsignedFix12( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
                {
                    return 0;
                }
                else
                {
                    unsigned uval_;

                    val *= 1 << (12 - 0);
                    if (val >= (1 << 12))
                    {
                        uval_ = (1 << 12) - 1;
                    }
                    else
                    {
                        uval_ = (unsigned)(val);
                    }

                    return uval_;
                }
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFix12( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                if( val == 0.f || (v_ & 0x7f800000) == 0x7f800000 )
                    return 0;

                int ret;

                val *= (1 << (12 - 1));

                if( val < 0 )
                {
                    ret = 1 << (12 - 1);
                    val = -val;
                }
                else
                    ret = 0;

                if( val >= (1 << (12 - 1)) )
                    val  = (1 << (12 - 1)) - 1;

                ret |= (unsigned)(val);
                return ret;
            }

            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFix12Fraction11( f32 val )
            {                                
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );

                if (val == 0.f || (v_ & 0x7f800000) == 0x7f800000)
                {
                    return 0;
                }
                else
                {
                    val += 0.5f * (1 << 1);
                    val *= 1 << (12 - 1);
                    
                    if (val < 0)
                    {
                        val = 0;
                    }
                    else if (val >= (1 << 12))
                    {
                            val = (1 << 12) - 1;
                    }

                    if (val >= (1 << (12 - 1)))
                    {
                        return (unsigned)(val - (1 << (12 - 1)));
                    }
                    else
                    {
                        return (unsigned)(val + (1 << (12 - 1)));
                    }
                }
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFix13Fraction8( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                if ( ( val == 0.0f ) || 
                     ( (v_ & 0x7f800000) == 0x7f800000 ) )
                {
                    return 0;
                }

                val += 0.5f * (1 << 5);
                val *= 1 << (13 - 5);
                if (val < 0)
                {
                    val = 0;
                }
                else if (val >= (1 << 13))
                {
                    val = (1 << 13) - 1;
                }

                return (val >= (1 << (13 - 1))) ? (unsigned)(val - (1 << (13 - 1))) : (unsigned)(val + (1 << (13 - 1)));
            }

            //------------------------------------------------------------------------------------
           
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToFix13Fraction11( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                if( val == 0.f || (v_ & 0x7f800000) == 0x7f800000 )
                    return 0;

                val += 0.5f * (1 << 2);
                val *= 1 << (13 - 2);
                if (val < 0)
                    val = 0;
                else if (val >= (1 << 13))
                    val = (1 << 13) - 1;

                return (val >= (1 << (13 - 1))) ? (unsigned)(val - (1 << (13 - 1))) : (unsigned)(val + (1 << (13 - 1)));
            }

            //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                

                

                
            */
            inline u32 Float32ToUnsignedFix11( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                if( val <= 0 || (v_ & 0x7f800000) == 0x7f800000 )
                    return 0;

                unsigned uval_;

                val *= 1 << (11 - 0);
                if (val >= (1 << 11))
                    uval_ = (1 << 11) - 1;
                else
                    uval_ = (unsigned)(val);

                return uval_;
            }

             //------------------------------------------------------------------------------------
            
            /* Please see man pages for details 
                
                
                

                
            */
            inline u8 Float32ToFix8Fraction7( f32 val )
            {
                unsigned v_ = *( reinterpret_cast<unsigned*>( &val ) );
                
                if (val == 0.f || (v_ & 0x7f800000) == 0x7f800000)
                {
                    return 0;
                }
                else
                {
                    val += 0.5f * (1 << 1);
                    val *= 1 << (8 - 1);
                    
                    if (val < 0)
                    {
                        val = 0;
                    }
                    else if (val >= (1 << 8))
                    {
                        val = (1 << 8) - 1;
                    }
                    
                    if (val >= (1 << (8 - 1)))
                    {
                        return (unsigned)(val - (1 << (8 - 1)));
                    }
                    else
                    {
                        return (unsigned)(val + (1 << (8 - 1)));
                    }
                }
            }

            //------------------------------------------------------------------------------------
            /* Please see man pages for details 
                

                

                
            */
            inline u32 PicaDataVertexAttrTypeToByteSize( const PicaDataVertexAttrType type )
            {
                switch ( type )
                {
                    case PICA_DATA_SIZE_1_BYTE          : return 1 * sizeof(  s8 );
                    case PICA_DATA_SIZE_1_UNSIGNED_BYTE : return 1 * sizeof(  u8 );
                    case PICA_DATA_SIZE_1_SHORT         : return 1 * sizeof( s16 );
                    case PICA_DATA_SIZE_1_FLOAT         : return 1 * sizeof( f32 );
                    case PICA_DATA_SIZE_2_BYTE          : return 2 * sizeof(  s8 );
                    case PICA_DATA_SIZE_2_UNSIGNED_BYTE : return 2 * sizeof(  u8 );
                    case PICA_DATA_SIZE_2_SHORT         : return 2 * sizeof( s16 );
                    case PICA_DATA_SIZE_2_FLOAT         : return 2 * sizeof( f32 );
                    case PICA_DATA_SIZE_3_BYTE          : return 3 * sizeof(  s8 );
                    case PICA_DATA_SIZE_3_UNSIGNED_BYTE : return 3 * sizeof(  u8 );
                    case PICA_DATA_SIZE_3_SHORT         : return 3 * sizeof( s16 );
                    case PICA_DATA_SIZE_3_FLOAT         : return 3 * sizeof( f32 );
                    case PICA_DATA_SIZE_4_BYTE          : return 4 * sizeof(  s8 );
                    case PICA_DATA_SIZE_4_UNSIGNED_BYTE : return 4 * sizeof(  u8 );
                    case PICA_DATA_SIZE_4_SHORT         : return 4 * sizeof( s16 );
                    case PICA_DATA_SIZE_4_FLOAT         : return 4 * sizeof( f32 );
                }
                return 0;
            }


            //------------------------------------------------------------------------------------

            /* Please see man pages for details 


                

                

                
            */
            bit32* MakeDisableAllCommand( bit32* command );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                
            */
            enum CommandBufferChannel
            {
                //
                CMD_BUF_CH0 = 0x0,
                //
                CMD_BUF_CH1 = 0x1
            };

            /* Please see man pages for details 
                

                
                

                
            */
            bit32* MakeChannelKickCommand( bit32* command, const CommandBufferChannel channel );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
                

                
            */
            bit32* MakeChannel0SubroutineCommand( bit32* command, uptr* bufferSizePtr, const uptr commandBufferPtr, const size_t commandBufferSize );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                
                

                
            */
            bit32* MakeChannel1SubroutineCommand( bit32* command, uptr* bufferSizePtr, const uptr commandBufferPtr, const size_t commandBufferSize );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
            */
            bit32* MakeChannel0JumpCommand( bit32* command, const uptr commandBufferPtr, const size_t commandBufferSize );

            //------------------------------------------------------------------------------------

            /* Please see man pages for details 
                

                
                
                

                
            */
            bit32* MakeChannel1JumpCommand( bit32* command, const uptr commandBufferPtr, const size_t commandBufferSize );

            /* Please see man pages for details 
                
            */
            enum PostVertexCacheEntryType
            {
                //
                POST_VERTEX_CACHE_ENTRY_TYPE_32 = 0x0,
                //
                POST_VERTEX_CACHE_ENTRY_TYPE_16 = 0x1
            };

            /* Please see man pages for details 
                

                
                

                
            */
            bit32* MakePostVertexCacheEntryTypeCommand( bit32* command, const PostVertexCacheEntryType type );

            //------------------------------------------------------------------------------------

            inline void CommandBufferJumpHelper::Jump(uptr subroutine, size_t subroutineSize )
            {
                if ( !subroutine )
                    return;

                // Use of nn::gr::MakeChannel0SubroutineCommand is presumed, the size of commands being added is assumed to be 24 bytes.
                m_CurrentPtr = AddDummyDataForCommandBuffer(m_CurrentPtr, GetOffsetFromPtr(m_ReturnPtr, m_CurrentPtr) + 24);

                uptr cmdSizePtr;
                m_CurrentPtr = MakeChannel0SubroutineCommand(m_CurrentPtr, &cmdSizePtr, subroutine, subroutineSize);

                if ( m_CmdSizePtr )
                {
                    *(reinterpret_cast<u32*>(m_CmdSizePtr)) = GetOffsetFromPtr(m_ReturnPtr, m_CurrentPtr) >> 3;
                }
                m_CmdSizePtr = cmdSizePtr;
                m_ReturnPtr  = m_CurrentPtr;

                if ( m_SizeToFirstJump == 0 )
                {
                    m_SizeToFirstJump = GetOffsetFromPtr(m_StartPtr, m_CurrentPtr);
                }
            }
        } // namespace CTR
    } // namespace gr
} // namespace nn

#endif // NN_GR_UTILITY_H_
