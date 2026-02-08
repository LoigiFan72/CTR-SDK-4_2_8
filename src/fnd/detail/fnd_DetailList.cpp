/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     fnd_DetailList.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include "./fnd_DetailList.h"

namespace nn { namespace fnd { namespace detail {
    
#define OBJ_TO_LINK(list,obj)   ((NNSFndLink*)(((u32)(obj))+(list)->offset))

/*---------------------------------------------------------------------------*
  Name:         InitList
  Description:  Initializes list structure.
  Arguments:    list:   Pointer to the list structure.
                offset: Specifies the offset in the member variable structure of the NNSFndLink type that exists in the structure to be linked in the list.
                        
                        This is convenient when using the offsetof macro defined in stddef.h.
                        
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
InitList(NNSFndList* list, u16 offset)
{
    NN_TASSERT_(list);

    list->headObject = NULL;
    list->tailObject = NULL;
    list->numObjects = 0;
    list->offset     = offset;
}

/*---------------------------------------------------------------------------*
  Name:         SetFirstObject                                      [static]
  Description:  Adds the first object to the list.
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to the object you want to add to the list.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
static void
SetFirstObject(NNSFndList* list, void* object)
{
    NNSFndLink* link;

    NN_TASSERT_(list  );
    NN_TASSERT_(object);

    link = OBJ_TO_LINK(list, object);

    link->nextObject = NULL;
    link->prevObject = NULL;
    list->headObject = object;
    list->tailObject = object;
    list->numObjects++;
}

/*---------------------------------------------------------------------------*
  Name:         AppendListObject
  Description:  Adds an object to the end of the list.
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to the object you want to add to the list.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
AppendListObject(NNSFndList* list, void* object)
{
    NN_TASSERT_(list  );
    NN_TASSERT_(object);

    if (list->headObject == NULL)
    {
        // When the list is empty
        SetFirstObject(list, object);
    }
    else
    {
        NNSFndLink* link = OBJ_TO_LINK(list, object);

        link->prevObject = list->tailObject;
        link->nextObject = NULL;

        OBJ_TO_LINK(list, list->tailObject)->nextObject = object;
        list->tailObject = object;
        list->numObjects++;
    }
}

/*---------------------------------------------------------------------------*
  Name:         PrependListObject
  Description:  Inserts object at the head of the list.
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to the object you want to add to the list.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
PrependListObject(NNSFndList* list, void* object)
{
    NN_TASSERT_(list  );
    NN_TASSERT_(object);

    if (list->headObject == NULL)
    {
        // When the list is empty
        SetFirstObject(list, object);
    }
    else
    {
        NNSFndLink* link = OBJ_TO_LINK(list, object);

        link->prevObject = NULL;
        link->nextObject = list->headObject;

        OBJ_TO_LINK(list, list->headObject)->prevObject = object;
        list->headObject = object;
        list->numObjects++;
    }
}

/*---------------------------------------------------------------------------*
  Name:         InsertListObject
  Description:  Inserts object in the specified location. Object is inserted before the object specified by "target". If no insert target is specified, ("target" is NULL) the object is added to the end of the list. 
               
                
                
  Arguments:    list:   Pointer to the list structure.
                target: Pointer to the object at the position where you want to insert an object.
                object: Pointer to the object you want to add to the list.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
InsertListObject(NNSFndList* list, void* target, void* object)
{
    NN_TASSERT_(list  );
    NN_TASSERT_(object);

    if (target == NULL)
    {
        // When the target is not specified, same as AppendListObject function.
        AppendListObject(list, object);
    }
    else if (target == list->headObject)
    {
        // When target is the head of the list, same as the PrependListObject function.
        PrependListObject(list, object);
    }
    else
    {
        NNSFndLink* link    = OBJ_TO_LINK(list, object);
        void*       prevObj = OBJ_TO_LINK(list, target)->prevObject;
        NNSFndLink* prevLnk = OBJ_TO_LINK(list, prevObj);

        link->prevObject    = prevObj;
        link->nextObject    = target;
        prevLnk->nextObject = object;
        OBJ_TO_LINK(list, target)->prevObject = object;
        list->numObjects++;
    }
}

/*---------------------------------------------------------------------------*
  Name:         RemoveListObject
  Description:  Deletes object from the list.
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to the object you want to delete from the list.
  Returns:      None.
 *---------------------------------------------------------------------------


*/
void
RemoveListObject(NNSFndList* list, void* object)
{
    NNSFndLink* link;

    NN_TASSERT_(list  );
    NN_TASSERT_(object);

    link = OBJ_TO_LINK(list, object);

    if (link->prevObject == NULL)
    {
        list->headObject = link->nextObject;
    }
    else
    {
        OBJ_TO_LINK(list, link->prevObject)->nextObject = link->nextObject;
    }
    if (link->nextObject == NULL)
    {
        list->tailObject = link->prevObject;
    }
    else
    {
        OBJ_TO_LINK(list, link->nextObject)->prevObject = link->prevObject;
    }
    link->prevObject = NULL;
    link->nextObject = NULL;
    list->numObjects--;
}

/*---------------------------------------------------------------------------*
  Name:         GetNextListObject
  Description:  Returns the object next in the list after the object specified by 'object.' When NULL is specified for "object", the object at the head of the list is returned.
                
                
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to object in list.
  Returns:      Returns a pointer to the object next in the last after the specified object. If there is no next object, returns NULL. 
                 
 *---------------------------------------------------------------------------


*/
void*
GetNextListObject(const NNSFndList* list, const void* object)
{
    NN_TASSERT_(list);

    if (object == NULL)
    {
        return list->headObject;
    }
    return OBJ_TO_LINK(list, object)->nextObject;
}

/*---------------------------------------------------------------------------*
  Name:         GetPrevListObject
  Description:  Returns the object linked in front of the object specified by 'object.'
                
                When NULL is specified for "object", the object linked to the tail of the list is returned.
  Arguments:    list:   Pointer to the list structure.
                object: Pointer to object in list.
  Returns:      Returns a pointer to the previous object before the specified object.
                 If there is no object in front, returns NULL.
 *---------------------------------------------------------------------------


*/
void*
GetPrevListObject(const NNSFndList* list, const void* object)
{
    NN_TASSERT_(list);

    if (object == NULL)
    {
        return list->tailObject;
    }
    return OBJ_TO_LINK(list, object)->prevObject;
}

/*---------------------------------------------------------------------------*
  Name:         GetNthListObject
  Description:  Returns a pointer to the object linked nth on the list.
                Because the list is traversed in order from the head, objects deeper in the list take more time.
                
  Arguments:    index:  Object index.
  Returns:      Returns pointer to object. If there is no object for the specified index, NULL is returned.
                
 *---------------------------------------------------------------------------


*/
void*
GetNthListObject(const NNSFndList* list, u16 index)
{
    int         count  = 0;
    NNSFndLink* object = NULL;

    NN_TASSERT_(list);

//    while ((object = GetNextListObject(list, object)) != NULL)
//  for Horizon
    while ((object = reinterpret_cast<NNSFndLink*>(
                    GetNextListObject(list, object))) != NULL)
    {
        if (index == count)
        {
            return object;
        }
        count++;
    }
    return NULL;
}

}}} // namespace nn::os::fnd

