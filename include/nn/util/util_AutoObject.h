/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_AutoObject.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_AUTOOBJECT_H_
#define NN_UTIL_UTIL_AUTOOBJECT_H_

#include <nn/util/util_NonCopyable.h>
#include <nn/WithInitialize.h>
#include <memory>

namespace nn { namespace util {

namespace detail
{
    struct AutoObjectCoreAccess;
}

template <typename Int>
class ReferenceCounter
{
    friend struct detail::AutoObjectCoreAccess;
private:
    Int m_Value;
protected:
    ReferenceCounter() : m_Value(1) { NN_LOG_DEBUG("ctor0\n"); }
    ReferenceCounter(const ReferenceCounter&) : m_Value(1) { NN_LOG_DEBUG("copy\n"); }
    ~ReferenceCounter() { NN_TASSERT_(m_Value == 0);  NN_LOG_DEBUG("dtor\n"); }
    ReferenceCounter& operator=(const ReferenceCounter& rhs)
    {
        if (this != &rhs)
        {
            NN_TASSERT_(m_Value == 0);
            m_Value = 1;
        };
        return *this;
    }
private:
    void IncrementRefCount() { ++m_Value; NN_LOG_DEBUG("inc\n"); }
    bool DecrementRefCount() { NN_LOG_DEBUG("dec\n"); return --m_Value > 0; }
    bool TryDecrementRefCount() { return (m_Value > 1) && (--m_Value, NN_LOG_DEBUG("trydec\n"), true); }
public:
    Int GetReferenceCounter() const { return m_Value; }
};

namespace detail
{

struct AutoObjectCoreAccess
{
    template <typename ReferenceCounter>
    static void IncrementRefCount(ReferenceCounter& r) { r.IncrementRefCount(); }
    template <typename ReferenceCounter>
    static bool DecrementRefCount(ReferenceCounter& r) { return r.DecrementRefCount(); }
    template <typename ReferenceCounter>
    static bool TryDecrementRefCount(ReferenceCounter& r) { return r.TryDecrementRefCount(); }
};

template <class Self, class TObject>
class AutoObject
{
protected:

    typedef TObject Object;

    
    AutoObject() : m_P(0) {}
    
    AutoObject(const nn::WithInitialize&) : m_P(new Object()) {}
    
    template <class T>
    AutoObject(const T& x) : m_P(new Object(x)) {}
    
    AutoObject(const AutoObject& other) : m_P(other.m_P)
    {
        other.AssertNotUpdating();
        if (m_P)
        {
            detail::AutoObjectCoreAccess::IncrementRefCount(*m_P);
        }
    }
    
    ~AutoObject()
    {
        AssertNotUpdating();
        DecrementAndDelete();
    }
    
    Self& Assign(const Self& rhs)
    {
        AssertNotUpdating();
        rhs.AssertNotUpdating();
        if (this != &rhs && m_P != rhs.m_P)
        {
            DecrementAndDelete();
            this->m_P = rhs.m_P;
            if (m_P)
            {
                detail::AutoObjectCoreAccess::IncrementRefCount(*m_P);
            }
        }
        return static_cast<Self&>(*this);
    }
    
    void Clear()
    {
        AssertNotUpdating();
        DecrementAndDelete();
        this->m_P = 0;
    }
    
    const Object& operator*() const
    {
        NN_TASSERT_(IsValid());
        AssertNotUpdating();
        return *m_P;
    }
    
    const Object* operator->() const
    {
        NN_TASSERT_(IsValid());
        AssertNotUpdating();
        return m_P;
    }
    
    bool IsValid() const
    {
        return m_P != 0;
    }
    
    friend class Updater;
    
    class Updater
    {
    private:
    
        AutoObject& m_AutoObject;
        
#ifndef NN_SWITCH_DISABLE_ASSERT_WARNING
        Object* GetObject() { return reinterpret_cast<Object*>(reinterpret_cast<uptr>(m_AutoObject.m_P) & ~1); }
#else
        Object* GetObject() { return m_AutoObject.m_P; }
#endif
        
    public:
    
        Updater(AutoObject& autoObject) : m_AutoObject(autoObject)
        {
            NN_TASSERT_(autoObject.IsValid());
            if (detail::AutoObjectCoreAccess::DecrementRefCount(*autoObject.m_P))
            {
                autoObject.m_P = new Object(*autoObject);
            }
            else
            {
                detail::AutoObjectCoreAccess::IncrementRefCount(*autoObject.m_P);
            }
            autoObject.SetUpdating();
        }
        
        ~Updater() { m_AutoObject.UnsetUpdating(); }
    
        Object& operator*()
        {
            return *GetObject();
        }
        
        Object* operator->()
        {
            return GetObject();
        }
    };

    AutoObject(Object* p) : m_P(p) {}
    
    Object* Release()
    {
        AssertNotUpdating();
        Object* p = m_P;
        this->m_P = 0;
        if (!detail::AutoObjectCoreAccess::TryDecrementRefCount(*p))
        {
            return p;
        }
        else
        {
            return new Object(*p);
        }
    }

private:

    Object* m_P;
    
    void DecrementAndDelete()
    {
        if (m_P && !detail::AutoObjectCoreAccess::DecrementRefCount(*m_P))
        {
            delete m_P;
        }
    }
    
#ifndef NN_SWITCH_DISABLE_ASSERT_WARNING

    void AssertNotUpdating() const
    {
        NN_TASSERT_((reinterpret_cast<const uptr&>(m_P) & 1) == 0);
    }

    void SetUpdating()
    {
        AssertNotUpdating();
        reinterpret_cast<uptr&>(m_P) |= 1;
    }

    void UnsetUpdating()
    {
        reinterpret_cast<uptr&>(m_P) &= ~1;
    }

#else

    void AssertNotUpdating() const {}
    void SetUpdating() {}
    void UnsetUpdating() {}
    
#endif
    
};

}

}}

#define NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_DECL_T0(name, ...) \
    class name : public ::nn::util::detail::AutoObject<name, __VA_ARGS__ >

#define NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_DECL_T1(name, ...) \
    template <typename NN_UTIL_AUTOOBJECT_T0> \
    class name : public ::nn::util::detail::AutoObject<name<NN_UTIL_AUTOOBJECT_T0>, __VA_ARGS__ >

#define NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_BODY(name, ...) \
    { \
    private: \
        typedef ::nn::util::detail::AutoObject<name, __VA_ARGS__ > Base; \
        friend class ::nn::util::detail::AutoObject<name, __VA_ARGS__ >; \
        name(__VA_ARGS__* p) : Base(p) {} \
    public: \
        name(const name& other) : Base(static_cast<const Base&>(other)) {} \
        friend name Move(name& _this) { return _this.Release(); } \
        name& operator=(const name& rhs) \
        { \
            return Base::Assign(rhs); \
        } \
    private:

#define NN_UTIL_AUTOOBJECT_BEGIN_DEFINE(name, ...) \
    NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_DECL_T0(name, __VA_ARGS__) \
    NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_BODY(name, __VA_ARGS__)

#define NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_T1(name, ...) \
    NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_DECL_T1(name, __VA_ARGS__) \
    NN_UTIL_AUTOOBJECT_BEGIN_DEFINE_BODY(name, __VA_ARGS__)
        
#define NN_UTIL_AUTOOBJECT_END_DEFINE \
    };

#endif
