/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Crc.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_CRC_H_
#define NN_UTIL_UTIL_CRC_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn { namespace util {

const size_t CRC_TABLE_SIZE = 256;

//----------------------------------------------------------------------------
// CRC-8
//----------------------------------------------------------------------------

//
class Crc8 {

public:

    //
    Crc8();

    /* Please see man pages for details 
        
        
     */
    void InitializeContext(u8 context = CRC8_STANDARD_INIT);

    //
    //
    //
    void Update(const void* input, size_t length);

    //
    //
    u8 GetHash();

    /* Please see man pages for details 
        

        

        
        
        

        
     */
    static u8 Calculate(const void* input, size_t length, u8 context = CRC8_STANDARD_INIT);

private:
    //
    static const u8 CRC8_STANDARD_POLY = 0x07;

    //
    static const u8 CRC8_STANDARD_INIT = 0;

    //
    typedef u8 Context;

    //
    struct Table
    {
        u8      table[CRC_TABLE_SIZE];
    };

    //
    Context m_Context;

    //
    Table   m_Table;

    //
    //
    void InitializeTable(u8 poly);

};

//----------------------------------------------------------------------------
// CRC-16
//----------------------------------------------------------------------------

//
class Crc16 {

public:
    //
    Crc16();

    //
    //
    void InitializeContext(u16 context = CRC16_STANDARD_INIT);

    //
    //
    //
    void Update(const void* input, size_t length);

    //
    //
    u16 GetHash();

    /* Please see man pages for details 
        

        

        
        
        

        
     */
    static u16 Calculate(const void* input, size_t length, u16 context = CRC16_STANDARD_INIT);

private:
    //
    static const u16 CRC16_STANDARD_POLY = 0xa001;      // Items that execute bit inversion also invert generated polynomials.

    //
    static const u16 CRC16_STANDARD_INIT = 0;

    //
    typedef u16 Context;

    //
    struct Table
    {
        u16      table[CRC_TABLE_SIZE];
    };

    //
    Context m_Context;

    //
    Table   m_Table;

    //
    //
    void InitializeTable(u16 poly);

};

//----------------------------------------------------------------------------
// CRC-16/CCITT
//----------------------------------------------------------------------------

//
class Crc16Ccitt {

public:

    //
    Crc16Ccitt();

    //
    //
    void InitializeContext(u16 context = CRC16_CCITT_INIT);

    //
    //
    //
    void Update(const void* input, size_t length);

    //
    //
    u16 GetHash();

    /* Please see man pages for details 
        

        

        
        
        

        
     */
    static u16 Calculate(const void* input, size_t length, u16 context = CRC16_CCITT_INIT);

private:
    //
    static const u16 CRC16_CCITT_POLY = 0x1021;

    //
    static const u16 CRC16_CCITT_INIT = 0xffff;

    //
    typedef u16 Context;

    //
    struct Table
    {
        u16      table[CRC_TABLE_SIZE];
    };

    //
    Context m_Context;

    //
    Table   m_Table;


    //
    //
    void InitializeTable(u16 poly);

};

//----------------------------------------------------------------------------
// CRC-32
//----------------------------------------------------------------------------

//
class Crc32 {

public:

    //
    Crc32();

    //
    //
    void InitializeContext(u32 context = CRC32_STANDARD_INIT);

    //
    //
    //
    void Update(const void* input, size_t length);

    //
    //
    u32 GetHash();

    /* Please see man pages for details 
        

        

        
        
        

        
     */
    static u32 Calculate(const void* input, size_t length, u32 context = CRC32_STANDARD_INIT);

private:
    //
    static const u32 CRC32_STANDARD_POLY = 0xedb88320;  // Items that execute bit inversion also invert generated polynomials.

    //
    static const u32 CRC32_STANDARD_INIT = 0xffffffff;

    //
    typedef u32 Context;

    //
    struct Table
    {
        u32      table[CRC_TABLE_SIZE];
    };

    //
    Context m_Context;

    //
    Table   m_Table;


    //
    //
    void InitializeTable(u32 poly);

};

//----------------------------------------------------------------------------
// CRC-32/POSIX
//----------------------------------------------------------------------------

//
class Crc32Posix {

public:

    //
    Crc32Posix();

    //
    //
    void InitializeContext(u32 context = CRC32_POSIX_INIT);

    //
    //
    //
    void Update(const void* input, size_t length);

    //
    //
    u32 GetHash();

    /* Please see man pages for details 
        

        

        
        
        

        
     */
    static u32 Calculate(const void* input, size_t length, u32 context = CRC32_POSIX_INIT);

private:
    //
    static const u32 CRC32_POSIX_POLY = 0x04c11db7;

    //
    static const u32 CRC32_POSIX_INIT = 0;

    //
    typedef u32 Context;

    //
    struct Table
    {
        u32      table[CRC_TABLE_SIZE];
    };

    //
    Context m_Context;

    //
    Table   m_Table;


    //
    //
    void InitializeTable(u32 poly);

};

}}

#endif // __cplusplus

#endif // ifndef NN_UTIL_UTIL_CRC_H_
