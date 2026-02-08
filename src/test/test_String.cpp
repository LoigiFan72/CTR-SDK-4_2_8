/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_String.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/test/test_String.h>
#include <cstring>
#include <cstdio>
namespace nn{ namespace test{
    String::String()
    {
        Initialize(NULL);
    }

    String::String(const char* pBuffer)
    {
        Initialize(pBuffer);
    }
    
    String::String(const String& other)
    {
        Initialize(other.GetBuffer());
    }
    
    String::String(int num)
    {
        char buf[11]; 
        ::std::sprintf(buf, "%d", num);
        Initialize(buf);
    }

    String& String::operator=(const char* pBuffer)
    {
        Finalize();
        Initialize(pBuffer);
        return *this;
    }

    String& String::operator =(const String& other)
    {
        return *this = other.GetBuffer();
    }

    bool    String::operator==(String& other)
    {
        return other == m_pBuffer;
    }

    bool    String::operator==(const char* pBuffer)
    {
        return ::std::strcmp(pBuffer, m_pBuffer) == 0;
    }
    
    String& String::operator+=(const char* pBuffer)
    {
        int newLen = ::std::strlen(m_pBuffer) + ::std::strlen(pBuffer) + 1;
        char* pNewBuffer = new char[newLen];
        ::std::strcpy(pNewBuffer, m_pBuffer);
        ::std::strcat(pNewBuffer, pBuffer);
        delete [] m_pBuffer;
        m_pBuffer = pNewBuffer;
        return *this;
    }
    
    String& String::operator+=(const String& other)
    {
        return (*this += other.GetBuffer());
    }
    
    void    String::Finalize()
    {
        delete [] m_pBuffer;
    }
    
    void    String::Initialize(const char* pBuffer)
    {
        if(pBuffer == NULL)
        {
            m_pBuffer = new char[1];
            m_pBuffer[0] = '\0';
        }
        else
        {
            m_pBuffer = new char[::std::strlen(pBuffer) + 1];
            ::std::strcpy(m_pBuffer, pBuffer);
        }
    }
    
    String::~String()
    {
        delete[] m_pBuffer;
    }
}}

