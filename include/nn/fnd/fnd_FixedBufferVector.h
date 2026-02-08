/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_FixedBufferVector.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_FND_FIXEDBUFFERVECTOR_H_
#define NN_FND_FND_FIXEDBUFFERVECTOR_H_

#include <nn/types.h>

#ifdef __cplusplus

namespace nn {
namespace fnd {

    template <typename T, int NUM_OF_T>
    class FixedBufferVector
    {
    public:
        FixedBufferVector()
        : m_Length(0)
        {
        }
        ~FixedBufferVector() {}

        const T& operator[](int index) const
        {
            return m_Buffer[index];
        }
        T& operator[](int index)
        {
            return m_Buffer[index];
        }
        
        void Add(T v)
        {
            *Add() = v;
        }
        T* Add()
        {
            NN_MAX_TASSERT_(m_Length, NUM_OF_T - 1);

            T* p = &m_Buffer[m_Length];
            m_Length++;
            return p;
        }

        void Remove(int index)
        {
            NN_MIN_TASSERT_(m_Length, 1);

            const int last = m_Length - 1;
            if( index != last )
            {
                m_Buffer[index] = m_Buffer[last];
            }
            m_Length--;
        }
        void Clear()
        {
            m_Length = 0;
        }

        T* GetBegin() { return &m_Buffer[0]; }
        T* GetEnd()   { return &m_Buffer[m_Length]; }
        const T* GetBegin() const { return &m_Buffer[0]; }
        const T* GetEnd()   const { return &m_Buffer[m_Length]; }
        s32 GetLength() const { return m_Length; }


    private:
        u16     m_Length;
        NN_PADDING2;
        NN_PADDING4;
        T       m_Buffer[NUM_OF_T];
    };

}}

#endif

#endif  // ifndef NN_FND_FND_FIXEDBUFFERVECTOR_H_
