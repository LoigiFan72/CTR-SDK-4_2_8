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

#ifndef NN_FND_ARMV6_FND_INTERLOCKED_H_
#define NN_FND_ARMV6_FND_INTERLOCKED_H_

#ifdef __cplusplus

#include <nn/types.h>
#include <nn/util/util_TypeTraits.h>

namespace nn {
    namespace fnd {
        namespace ARMv6
        {
            namespace detail
            {
                template <typename T>
                struct LoadStoreRegEx
                {
                    static T LoadRegEx (volatile T* ptr) { return __ldrex(ptr); }
                    static int StoreRegEx(T val, volatile T* ptr) { return __strex(val, ptr); }
                };
                template <>
                struct LoadStoreRegEx<s64>
                {
                    static s64 LoadRegEx (volatile s64* ptr) { return __ldrexd(ptr); }
                    static int StoreRegEx(s64 val, volatile s64* ptr) { return __strexd(val, ptr); }
                };
            }

            class Interlocked
            {
            private:
                
                template <typename T, typename = void> struct AtomicStorageSelecter;
                
                template <typename T> struct AtomicStorageSelecter<T, typename nn::util::enable_if<sizeof(T) == sizeof(s64)>::type>
                {
                    typedef s64 Type;
                };
                
                template <typename T> struct AtomicStorageSelecter<T, typename nn::util::enable_if<sizeof(T) == sizeof(s32)>::type>
                {
                    typedef s32 Type;
                };
                
                template <typename T> struct AtomicStorageSelecter<T, typename nn::util::enable_if<sizeof(T) == sizeof(s16)>::type>
                {
                    typedef s16 Type;
                };
                
                template <typename T> struct AtomicStorageSelecter<T, typename nn::util::enable_if<sizeof(T) == sizeof(s8)>::type>
                {
                    typedef s8 Type;
                };
            
            public:
                static s32 CompareAndSwap(s32* pTarget, s32 comp, s32 swap);
                static s32 Swap(s32* pTarget, s32 value);
                static s32 Increment(s32* pTarget);
                static s32 Decrement(s32* pTarget);
                static s32 Add(s32* pTarget, s32 value);
                static s32 Substract(s32* pTarget, s32 value);
                static s32 BitwiseOr(s32* pTarget, s32 value);
                static s32 BitwiseAnd(s32* pTarget, s32 value);
                static s32 BitwiseXor(s32* pTarget, s32 value);
                static s32 BitwiseNot(s32* pTarget);
                static s64 Read(s64* pTarget) { return *pTarget; }
                static u64 CompareAndSwap(u64* pTarget, const u64& comp, u64 swap);

                template <typename T>
                static T* CompareAndSwap(T** pTarget, T* comp, T* swap)
                {
                    return reinterpret_cast<T*>(
                        CompareAndSwap( reinterpret_cast<s32*>(pTarget),
                            reinterpret_cast<s32>(comp),
                            reinterpret_cast<s32>(swap) ));
                }

                template <typename T>
                static T* Swap(T** pTarget, T* value)
                {
                    return reinterpret_cast<T*>(
                        Swap( reinterpret_cast<s32*>(pTarget),
                            reinterpret_cast<s32>(value) ));
                }

                template <typename T, typename UpdateFunc>
                static bool AtomicUpdate(volatile T* p, UpdateFunc& update, typename nn::util::enable_if<sizeof(T) <= sizeof(s64)>::type* = 0)
                {
                    typedef typename AtomicStorageSelecter<T>::Type Storage;
                    typedef detail::LoadStoreRegEx<Storage> LoadStore;

                    // Use a union to guarantee that T can be used as a POD
                    union U  
                    {
                        T v;
                        Storage n;
                    };

                    U x;

                    for(;;)
                    {
                        x.n = LoadStore::LoadRegEx(reinterpret_cast<volatile Storage*&>(p));

                        if (!update(x.v))
                        {
                            __clrex();
                            return false;
                        }

                        if ( LoadStore::StoreRegEx(x.n, reinterpret_cast<volatile Storage*&>(p)) == 0 )
                        {
                            return true;
                        }
                    }
                }

                template <typename T>
                static int CompareAndSwapWeak(volatile T* p, T compValue, T setValue, typename nn::util::enable_if<sizeof(T) <= sizeof(s64)>::type* = 0)
                {
                    typedef typename AtomicStorageSelecter<T>::Type Storage;
                    typedef detail::LoadStoreRegEx<Storage> LoadStore;

                    // Use a union to guarantee that T can be used as a POD
                    union U  
                    {
                        T v;
                        Storage n;
                    };

                    U x;

                    x.n = LoadStore::LoadRegEx(reinterpret_cast<volatile Storage*&>(p));

                    int ret = 1;

                    if( x.v != compValue )
                    {
                        LoadStore::StoreRegEx(x.n, reinterpret_cast<volatile Storage*&>(p));
                    }
                    else
                    {
                        x.v = setValue;
                        ret = LoadStore::StoreRegEx(x.n, reinterpret_cast<volatile Storage*&>(p));
                    }

                    return ret;
                }
            };
        }
    }
}


#endif // __cplusplus

#endif  // NN_UTIL_MPCORE_INTERLOCKED_H_
