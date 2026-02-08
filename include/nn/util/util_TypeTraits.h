/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_TypeTraits.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/


#ifndef NN_UTIL_UTIL_TYPETRAITS_H_
#define NN_UTIL_UTIL_TYPETRAITS_H_

#ifdef __cplusplus

#include <nn/types.h>
#include <nn/util/util_StaticAssert.h>

// C++0x <type_traits> prefetch.
//   Implement as needed.
//   Items that are commented out have not been implemented.
//   Some items need compiler support, others are not defined unless they are C++0x.

//   To maintain compatibility, do not add other elements to this header other than <type_traits>.
 

namespace nn { namespace util {
  
//   Declarations
//   Remove the implemented items from comments.
//   Do not write implementation here.
  
//   [20.4.3] helper class:
template <class T, T v> struct integral_constant;
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// [20.4.4.1] primary type categories:
template <class T> struct is_void;
//template <class T> struct is_integral;
//template <class T> struct is_floating_point;
//template <class T> struct is_array;
//template <class T> struct is_pointer;
//template <class T> struct is_lvalue_reference;
//template <class T> struct is_rvalue_reference;
//template <class T> struct is_member_object_pointer;
//template <class T> struct is_member_function_pointer;
//template <class T> struct is_enum;
//template <class T> struct is_union;
//template <class T> struct is_class;
//template <class T> struct is_function;

// [20.4.4.2] composite type categories:
//template <class T> struct is_reference;
//template <class T> struct is_arithmetic;
//template <class T> struct is_fundamental;
//template <class T> struct is_object;
//template <class T> struct is_scalar;
//template <class T> struct is_compound;
//template <class T> struct is_member_pointer;

// [20.4.4.3] type properties:
//template <class T> struct is_const;
//template <class T> struct is_volatile;
//template <class T> struct is_trivial;
//template <class T> struct is_standard_layout;
//template <class T> struct is_pod;
//template <class T> struct is_empty;
//template <class T> struct is_polymorphic;
//template <class T> struct is_abstract;
//template <class T> struct has_trivial_default_constructor;
//template <class T> struct has_trivial_copy_constructor;
//template <class T> struct has_trivial_assign;
//template <class T> struct has_trivial_destructor;
//template <class T> struct has_nothrow_default_constructor;
//template <class T> struct has_nothrow_copy_constructor;
//template <class T> struct has_nothrow_assign;
//template <class T> struct has_virtual_destructor;
//template <class T> struct is_signed;
//template <class T> struct is_unsigned;
template <class T> struct alignment_of;
//template <class T> struct rank;
//template <class T, unsigned I = 0> struct extent;

// [20.4.5] type relations:
template <class T, class U> struct is_same;
template <class Base, class Derived> struct is_base_of;
template <class From, class To> struct is_convertible;

// [20.4.6.1] const-volatile modifications:
//template <class T> struct remove_const;
//template <class T> struct remove_volatile;
//template <class T> struct remove_cv;
//template <class T> struct add_const;
//template <class T> struct add_volatile;
//template <class T> struct add_cv;

// [20.4.6.2] reference modifications:
//template <class T> struct remove_reference;
//template <class T> struct add_lvalue_reference;
//template <class T> struct add_rvalue_reference;

// [20.4.6.3] sign modifications:
//template <class T> struct make_signed;
//template <class T> struct make_unsigned;

// [20.4.6.4] array modifications:
//template <class T> struct remove_extent;
//template <class T> struct remove_all_extents;

// [20.4.6.5] pointer modifications:
//template <class T> struct remove_pointer;
//template <class T> struct add_pointer;

// [20.4.7] other transformations:
template <size_t Len, size_t Align> struct aligned_storage;
//template <size_t Len, class... Types> struct aligned_union;
//template <class T> struct decay;
template <bool, class T = void> struct enable_if;
//template <bool, class T, class F> struct conditional;


// Implementation starts here


// template <class T, T v> struct integral_constant; implementation

template <class T, T v>
struct integral_constant
{
    typedef integral_constant<T, v> type;
    typedef T value_type;
    static const value_type value = v;
};


// template <class T> struct is_void; implementation

template <class>
struct is_void : public false_type {};

template <>
struct is_void<void> : public true_type {};


//template <class T> struct alignment_of; implementation

#ifdef NN_COMPILER_RVCT

template <class T>
struct alignment_of : public integral_constant<size_t, __alignof__(T)> {};

#else

namespace detail
{
    template <class T>
    class AlignmentHack
    {
        char c;
        T x;
    };
}

template <class T>
struct alignment_of : public integral_constant<size_t, sizeof(detail::AlignmentHack<T>) - sizeof(T)> {};

#endif

//template <size_t Len, size_t Align> struct aligned_storage; implementation

namespace detail
{
    template <size_t>
    struct AlignmentType {};
    
    template <>
    struct AlignmentType<1>
    {
        typedef u8 type;
    };
    
    template <>
    struct AlignmentType<2>
    {
        typedef u16 type;
    };
    
    template <>
    struct AlignmentType<4>
    {
        typedef u32 type;
    };
    
    template <>
    struct AlignmentType<8>
    {
        typedef u64 type;
    };
}

template <size_t Size, size_t Align>
struct aligned_storage
{
private:
    
    union UnionType
    {
        char c[Size];
        typename detail::AlignmentType<Align>::type a;
    };
    
public:
    typedef UnionType type;
};


// template <bool b, class T = void> struct enable_if; implementation

template <bool, class>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };


// template <class From, class To> struct is_convertible; implementation

template <class From, class To>
struct is_convertible
{
private:
    
    typedef char T1;
    struct T2 { char dummy[2]; };
    static T1 IsConvertibleTest(To);
    static T2 IsConvertibleTest(...);
    static From MakeFrom();
    
public:
    
   typedef bool value_type;
    static const bool value = sizeof(IsConvertibleTest(MakeFrom())) == sizeof(T1);
    
};


// template <class T, class U> struct is_same; implementation

template <class T, class U>
struct is_same : public false_type {};

template <class T>
struct is_same<T, T> : public true_type {};


// template <class Base, class Derived> struct is_base_of; implementation

template <class Base, class Derived>
struct is_base_of : public integral_constant<bool, is_convertible<const Derived*, const Base*>::value && !is_same<const Base*, const void*>::value> {};

}}

#endif // __cplusplus

#endif /* NN_UTIL_STATICASSERT_H_ */
