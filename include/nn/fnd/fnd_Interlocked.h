/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Interlocked.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

/* 
  
*/

#ifndef NN_FND_FND_INTERLOCKED_H_
#define NN_FND_FND_INTERLOCKED_H_

#ifdef __cplusplus

#include <nn/types.h>

#if     defined(NN_PROCESSOR_ARM_V4) || defined(NN_PROCESSOR_ARM_V5)
    #include <nn/fnd/ARMv4/fnd_Interlocked.h>
    namespace nn {
        namespace fnd {
            using ARMv4::Interlocked;
        }
    }
#elif   defined(NN_PROCESSOR_ARM_V6)
    #include <nn/fnd/ARMv6/fnd_Interlocked.h>
    namespace nn {
        namespace fnd {
            using ARMv6::Interlocked;
        }
    }
#else
    #error processor not selected
#endif

namespace nn { namespace fnd {

/*
    

           
*/
template <typename T>
class InterlockedVariable
{
private:
    template <typename U, typename = void> struct StorageSelecter;
    
    template <typename U> struct StorageSelecter<U, typename nn::util::enable_if<sizeof(U) == sizeof(s64)>::type>
    {
        typedef s64 Type;
    };
    
    template <typename U> struct StorageSelecter<U, typename nn::util::enable_if<sizeof(U) == sizeof(s32)>::type>
    {
        typedef s32 Type;
    };
    
    template <typename U> struct StorageSelecter<U, typename nn::util::enable_if<sizeof(U) == sizeof(s16)>::type>
    {
        typedef s16 Type;
    };
    
    template <typename U> struct StorageSelecter<U, typename nn::util::enable_if<sizeof(U) == sizeof(s8)>::type>
    {
        typedef s8 Type;
    };

private:
    volatile T m_v; //

    // Definitions for AtomicUpdateConditional function object

    template <class Converter>
    struct ConvertFunc
    {
        Converter& m_converter;
        ConvertFunc(Converter converter) : m_converter(converter) {}
        bool operator()(T& x) { x = m_converter(x); return true; }
    };

#define NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(F, op)                       \
    struct F                                                                \
    {                                                                       \
        T m_operand;                                                        \
        template <typename U> F(const U& operand) : m_operand(operand) {}   \
        bool operator()(T& x) { x op m_operand; return true; }              \
    };

    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(AssignFunc, =)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(PlusFunc, +=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(MinusFunc, -=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(OrFunc, |=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(AndFunc, &=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC(XorFunc, ^=)

#undef NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_FUNC

#define NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC(F, preop, postop) \
    struct F                                                    \
    {                                                           \
        T result;                                               \
        bool operator()(T& x) { result = preop x postop; return true; }   \
    };

    NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC(PreIncFunc,  ++,   )
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC(PreDecFunc,  --,   )
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC(PostIncFunc,   , ++)
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC(PostDecFunc,   , --)

#undef NN_UTIL_INTERLOCKED_DEFINE_UNARY_FUNC

    struct CompareAndSwapFunc
    {
        T m_comparand;
        T m_value;
        T m_result;
        bool operator()(T& x)
        {
            m_result = x;
            if (x == m_comparand)
            {
                x = m_value;
                return true;
            }
            else
            {
                return false;
            }
        }
        CompareAndSwapFunc(T comparand, T value) : m_comparand(comparand), m_value(value) {}
    };

public:
    /*
        

        
    */
    InterlockedVariable() : m_v() {}
    InterlockedVariable(T v) : m_v(v) {}

    operator T() const
    {
        typename StorageSelecter<T>::Type x = reinterpret_cast<const volatile typename StorageSelecter<T>::Type&>(m_v);
        return reinterpret_cast<T&>(x);
    }
    T operator ->()
    {
        typename StorageSelecter<T>::Type x = reinterpret_cast<const volatile typename StorageSelecter<T>::Type&>(m_v);
        return reinterpret_cast<T&>(x);
    }

    /*
        

        
    */
    T Read() const { return *this; }

    /*
        

        
    */
    void WriteNotAtomic (T v) { m_v = v; }

    /*
        

        

        
    */
    template <class Updater>
    bool AtomicUpdateConditional(Updater& updater) { return Interlocked::AtomicUpdate(&m_v, updater); }

    /*
        

        
        

        
    */
    T CompareAndSwap(T comparand, T value)
    {
        CompareAndSwapFunc f(comparand, value);
        AtomicUpdateConditional(f);
        return f.m_result;
    }

    /*
        

        
        

        
    */
    int CompareAndSwapWeak(T comparand, T value)
    {
        return Interlocked::CompareAndSwapWeak(&m_v, comparand, value);
    }

    /*
        

        
        
    */
    void CompareAndSpinWaitAndSwap(T cmpValue, T newValue)
    {
        for(;;)
        {
            if( m_v == cmpValue )
            {
                if( CompareAndSwapWeak(cmpValue, newValue) == 0 )
                {
                    break;
                }
            }
        }
    }

    // Overloaded operators

#define NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(F, op)                                       \
    template <typename V>                                                                       \
    void operator op(V v) { F f(v); AtomicUpdateConditional(f); }

    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(AssignFunc, =)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(PlusFunc, +=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(MinusFunc, -=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(OrFunc, |=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(AndFunc, &=)
    NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR(XorFunc, ^=)

#undef NN_UTIL_INTERLOCKED_DEFINE_ASSIGN_OPERATOR

#define NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR(F, op, premarker)                                     \
    InterlockedVariable operator op(premarker) { F f; AtomicUpdateConditional(f); return f.result; }    \

    NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR(PreIncFunc,  ++,    )
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR(PreDecFunc,  --,    )
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR(PostIncFunc, ++, int)
    NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR(PostDecFunc, --, int)

#undef NN_UTIL_INTERLOCKED_DEFINE_UNARY_OPERATOR
};

}}

#endif // __cplusplus

#endif  // NN_UTIL_INTERLOCKED_H_
