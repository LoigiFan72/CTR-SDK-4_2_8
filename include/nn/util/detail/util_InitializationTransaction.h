/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     util_InitializationTransaction.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_UTIL_DETAIL_UTIL_INITIALIZATIONTRANSACTION_H_
#define NN_UTIL_DETAIL_UTIL_INITIALIZATIONTRANSACTION_H_

#define NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN_(X, Y) NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN1_(X, Y)
#define NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN1_(X, Y) X##Y

#define NN_UTIL_DETAIL_BEGIN_INITIALIZATION_TRANSACTION(transaction) \
{ \
    bool transaction = false; \
    {

#define NN_UTIL_DETAIL_REGISTER_INITIALIZATION_TRANSACTION(transaction, T, object, f) \
        class NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN_(nn_util_detail_initialtransaction_class_, __LINE__) \
        { \
        private: \
            T& m_Object; \
            bool& m_Transaction; \
        public: \
            NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN_(nn_util_detail_initialtransaction_class_, __LINE__)(bool& transaction, T& object) : m_Object(object), m_Transaction(transaction) {} \
            ~NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN_(nn_util_detail_initialtransaction_class_, __LINE__)() \
            { \
                if (!m_Transaction) \
                { \
                    m_Object.f(); \
                } \
            } \
        } NN_UTIL_DETAIL_INITIALIZATIONTRANSACTION_H_STRING_JOIN_(nn_util_detail_initialtransaction_object_, __LINE__) (transaction, object)

#define NN_UTIL_DETAIL_END_INITIALIZATION_TRANSACTION(transaction) \
        transaction = true; \
    } \
}

#endif
