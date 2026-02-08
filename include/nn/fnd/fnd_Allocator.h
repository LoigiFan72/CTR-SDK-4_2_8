/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_Allocator.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law. They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47798 $
 *---------------------------------------------------------------------------*/

/* Please see man pages for details 
  

*/
#ifndef NN_FND_ALLOCATOR_H_
#define NN_FND_ALLOCATOR_H_

#ifdef __cplusplus

#include <new>
#include <limits>
#include <nn/util.h>
#include <nn/util/util_TypeTraits.h>

namespace nn { namespace fnd {

/* Please see man pages for details 
    

    
*/
class IAllocator
{
public:

    /* Please see man pages for details 
        
        
        
        
        
        
    */
    virtual void* Allocate(size_t size, s32 alignment) = 0;
    
    /* Please see man pages for details 
        
        
        
    */
    virtual void Free(void* p) = 0;
    
    virtual ~IAllocator() {}
};

template <typename Allocator, typename Tag>
class StdAllocatorAdapterHolder
{
public:

    static void SetAllocator(Allocator allocator) { s_Allocator = allocator; }
    static Allocator GetAllocator() { return s_Allocator; }

private:
    static Allocator s_Allocator;
};

template <typename Allocator, typename T, typename Tag = void>
class StdAllocatorAdapter : public StdAllocatorAdapterHolder<Allocator, Tag>
{
public:

    typedef size_t size_type;
    typedef sptr difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    template <class U> struct rebind { typedef StdAllocatorAdapter<Allocator, U, Tag> other; };
    StdAllocatorAdapter() throw() {}
    StdAllocatorAdapter(const StdAllocatorAdapter&) throw() {}
    template <class U> StdAllocatorAdapter(const StdAllocatorAdapter<Allocator, U, Tag>&) throw() {}
    ~StdAllocatorAdapter() throw() {}
    pointer address(reference& x) const { return &x; }
    const_pointer address(const_reference& x) const { return &x; }
    pointer allocate(size_type n, void* = 0) { return static_cast<T*>(StdAllocatorAdapterHolder<Allocator, Tag>::GetAllocator()->Allocate(n * sizeof(T), nn::util::alignment_of<T>::value)); }
    void deallocate(pointer p, size_type) { StdAllocatorAdapterHolder<Allocator, Tag>::GetAllocator()->Free(static_cast<void*>(p)); }
    size_type max_size() const throw() { return ::std::numeric_limits<size_type>::max() / sizeof(T); }
    void construct(pointer p, const T& val) { new (static_cast<void*>(p)) T(val); }
    void destroy(pointer p) { p->~T(); }
    
};

template <typename Allocator, typename T, typename Tag = void>
class StdUnitAllocatorAdapter
{
public:

    static void SetAllocator(Allocator allocator) { s_Allocator = allocator; }
    static Allocator GetAllocator() { return s_Allocator; }

    typedef size_t size_type;
    typedef sptr difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    template <class U> struct rebind { typedef StdUnitAllocatorAdapter<Allocator, U, Tag> other; };
    StdUnitAllocatorAdapter() throw() {}
    StdUnitAllocatorAdapter(const StdUnitAllocatorAdapter&) throw() {}
    template <class U> StdUnitAllocatorAdapter(const StdUnitAllocatorAdapter<Allocator, U, Tag>&) throw() {}
    ~StdUnitAllocatorAdapter() throw() {}
    pointer address(reference& x) const { return &x; }
    const_pointer address(const_reference& x) const { return &x; }
    pointer allocate(size_type n, void* = 0) { return static_cast<T*>(s_Allocator->Allocate(n * sizeof(T), nn::util::alignment_of<T>::value)); }
    void deallocate(pointer p, size_type) { s_Allocator->Free(static_cast<void*>(p)); }
    size_type max_size() const throw() { return ::std::numeric_limits<size_type>::max() / sizeof(T); }
    void construct(pointer p, const T& val) { new (static_cast<void*>(p)) T(val); }
    void destroy(pointer p) { p->~T(); }

private:
    static Allocator s_Allocator;
};

template <typename Allocator, typename Tag>
Allocator StdAllocatorAdapterHolder<Allocator, Tag>::s_Allocator;

template <typename Allocator, typename T, typename Tag>
Allocator StdUnitAllocatorAdapter<Allocator, T, Tag>::s_Allocator;

}}	// end of namespace nn

#endif // __cplusplus

#endif
