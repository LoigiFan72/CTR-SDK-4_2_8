/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ro_SectionTable.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_RO_RO_SECTIONTABLE_H_
#define NN_RO_RO_SECTIONTABLE_H_

#include <nn/types.h>
#include <nn/util/util_SizedEnum.h>
#include <nn/drivers/ro/ro_Types.h>
#include <nn/ro/ro_Types.h>

namespace nn { namespace ro { namespace detail {



    //--------------------------------------------------------------------------- 
    //
    //
    //--------------------------------------------------------------------------- 
    class SectionTable
    {
    private:
        const nn::drivers::ro::SectionInfo*  m_pSectionTable;
        s32                 m_NumSections;

    public:
        //--------------------------------------------------------------------------- 
        //
        //
        //
        //--------------------------------------------------------------------------- 
        SectionTable(const nn::drivers::ro::ObjectHeader* pModule)
            : m_pSectionTable(pModule->sectionInfo)
            , m_NumSections(pModule->numSections)
        {
        }
        
        //--------------------------------------------------------------------------- 
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //--------------------------------------------------------------------------- 
        const nn::drivers::ro::SectionInfo* GetSection(int index) const
        {
            if( (0 <= index) && (index < m_NumSections) )
            {
                return &m_pSectionTable[index];
            }
            else
            {
                return NULL;
            }
        }

        //--------------------------------------------------------------------------- 
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //--------------------------------------------------------------------------- 
        uptr GetAddress(int index, u32 offset) const
        {
            if( ! ((0 <= index) && (index < m_NumSections)) )
            {
                return NULL;
            }

            const nn::drivers::ro::SectionInfo& section = m_pSectionTable[index];

            if( ! (offset < section.size) )
            {
                return NULL;
            }

            return section.offset + offset;
        }

        //--------------------------------------------------------------------------- 
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //--------------------------------------------------------------------------- 
        uptr GetReferedAddress(int index, u32 offset) const
        {
            if( ! ((0 <= index) && (index < m_NumSections)) )
            {
                return NULL;
            }

            const nn::drivers::ro::SectionInfo& section = m_pSectionTable[index];

            if( ! (offset <= section.size) )
            {
                return NULL;
            }

            return section.offset + offset;
        }

        //--------------------------------------------------------------------------- 
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //--------------------------------------------------------------------------- 
        template<typename T>
        T GetPointer(int index, u32 offset) const
        {
            return reinterpret_cast<T>(GetAddress(index, offset));
        }

        uptr GetAddress(nn::drivers::ro::SectionAndOffset sao) const
        {
            return GetAddress(sao.GetFirst(), sao.GetSecond());
        }

        template<typename T>
        T GetPointer(nn::drivers::ro::SectionAndOffset sao) const
        {
            return reinterpret_cast<T>(GetAddress(sao));
        }
    };



}}}



#endif  // ifndef NN_RO_RO_SECTIONTABLE_H_
