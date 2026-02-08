/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailList.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_FND_DETAIL_FND_DETAIL_LIST_H_
#define NN_FND_DETAIL_FND_DETAIL_LIST_H_

#include <stddef.h>
#include <nn/types.h>
#include <nn/assert.h>
#include <nn/fnd/detail/fnd_DetailHeapHead.h>

#ifdef __cplusplus

namespace nn { namespace fnd { namespace detail {
//

/*---------------------------------------------------------------------------*
  Name:         NN_OS_INIT_LIST
  Description:  Macro to initialize list structures. The actual initialization is performed by the NNSFndInitList function.
                
                With this macro, the offset is found using the "offsetof" macro from the specified structure name and NNSFndLink type member variable name and passed to the NNSFndInitList function.
                
                
  Arguments:    list:       Pointer to the link structure.
                structName: Structure name of object you wish to link in the list.
                linkName:   The NNSFndLink type member variable name used in this object link.
                            
  Returns:      None.
 *---------------------------------------------------------------------------



*/

#define NN_OS_INIT_LIST(list, structName, linkName) \
            InitList(list, offsetof(structName, linkName))


/*---------------------------------------------------------------------------*
    Function Prototypes
 *---------------------------------------------------------------------------
*/

void    InitList(
                NNSFndList*             list,
                u16                     offset);

void    AppendListObject(
                NNSFndList*             list,
                void*                   object);

void    PrependListObject(
                NNSFndList*             list,
                void*                   object);

void    InsertListObject(
                NNSFndList*             list,
                void*                   target,
                void*                   object);

void    RemoveListObject(
                NNSFndList*             list,
                void*                   object);

void*   GetNextListObject(
                const NNSFndList*       list,
                const void*             object);

void*   GetPrevListObject(
                const NNSFndList*       list,
                const void*             object);

void*   GetNthListObject(
                const NNSFndList*       list,
                u16                     index);


/*---------------------------------------------------------------------------*
  Name:         GetListSize
  Description:  Gets the number of objects registered to the list specified by the argument.
                
  Arguments:    list: Pointer to the list structure.
  Returns:      Returns the number of objects registered to the specified list.
 *---------------------------------------------------------------------------


*/
inline u16
GetListSize( const NNSFndList* list )
{
    NN_TASSERT_( list );
    
    return list->numObjects;
}

/* NN_OS_LIST_H_ */
//
}}} // namespace nn::os

#endif // __cplusplus

#endif

