/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_NonCopyable.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus

#ifndef NN_UTIL_UTIL_NONCOPYABLE_H_
#define NN_UTIL_UTIL_NONCOPYABLE_H_

namespace nn { namespace util {

/* =======================================================================
        Dummy for reference use
   ======================================================================== */
#ifdef NN_BUILD_DOCUMENT

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
template <typename T>
class NonCopyable {};



/* =======================================================================
        Definition entity
   ======================================================================== */
#else
namespace ADLFireWall
{
    template <typename T>
    class NonCopyable
    {
    protected:
        NonCopyable () {}
        ~NonCopyable () {}

    private: 
        // Copy constructor and assignment operator are made private
        NonCopyable (const NonCopyable &);
        NonCopyable & operator = (const NonCopyable &);
    };
}
#endif


using ADLFireWall::NonCopyable;

}}


#endif /* NN_UTIL_NONCOPYABLE_H_ */

#endif // __cplusplus
