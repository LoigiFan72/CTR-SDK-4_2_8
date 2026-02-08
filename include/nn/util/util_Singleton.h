/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_Singleton.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_UTIL_SINGLETON_H_
#define NN_UTIL_UTIL_SINGLETON_H_

#ifdef __cplusplus

#include <nn/assert.h>
#include <nn/util/util_Result.h>
#include <nn/util/util_NonCopyable.h>

namespace nn { namespace util {

//---------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//---------------------------------------------------------------------------
template <class Derived>
class Singleton : private nn::util::NonCopyable<Singleton<Derived> >
{
public:
    static Derived& GetInstance(void)
    { 
        NN_TASSERT_(ms_Singleton);
        return(*ms_Singleton);
    }

protected:
    Singleton()
    {
        NN_TASSERTMSG_(ms_Singleton == 0, "This singleton constructor is called twice.");
        ms_Singleton = static_cast<Derived*>(this);
    }
    
    ~Singleton()
    {
        NN_TASSERT_(ms_Singleton);
        ms_Singleton = 0;
    }

private:
    static Derived* ms_Singleton;
};

template <class Derived> Derived* Singleton <Derived>::ms_Singleton = 0;

}}

#endif // __cplusplus

#endif /* NN_UTIL_SINGLETON_H_ */
