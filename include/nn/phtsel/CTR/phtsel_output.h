/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     phtsel_output.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev:$
 *---------------------------------------------------------------------------*/

#ifndef NN_PHTSEL_CTR_PHTSEL_OUTPUT_H_
#define NN_PHTSEL_CTR_PHTSEL_OUTPUT_H_

/* Please see man pages for details 
  
  
*/

#include <nn/types.h>
#include <nn/config.h>


#ifdef  __cplusplus

namespace nn {
namespace phtsel {
namespace CTR {

/* Please see man pages for details 
    

            
*/
enum ReturnCode
{
    //
    RETURN_CODE_UNKNOWN                         = -1,

    //
    RETURN_CODE_INVALID_CONFIG                  = -2,

    //
    RETURN_CODE_OUT_OF_MEMORY                   = -3,

    //
    RETURN_CODE_FILENAME_OVERFLOW               = -4,

    //
    RETURN_CODE_SUCCESS                         = 0,

    //
    RETURN_CODE_HOME_BUTTON                     = 1,

    //
    RETURN_CODE_SOFTWARE_RESET                  = 2,

    //
    RETURN_CODE_CANCEL                          = 3,

    //
    RETURN_CODE_POWER_BUTTON                    = 4,

    //
    RETURN_CODE_MAX_BIT = static_cast<s32>(1u << 31)
};


/*
    

    
 */
struct PhtselOutput
{
public:
    //----------------------------------------
    //

    /* Please see man pages for details 
        
    */
    static const size_t FILE_PATH_VALUE_MAX_NUM   = 512;

    /* Please see man pages for details 
        
        
        
    */
    static const size_t OUTPUT_RESERVED_SIZE      = 200;

protected:

    /* Please see man pages for details 
        
        
        
    */
    wchar_t m_nValue[FILE_PATH_VALUE_MAX_NUM];

    /* Please see man pages for details 
        

        
    */
    u16     m_nValueLen;

    NN_PADDING2;

    /* Please see man pages for details 
        

        

                
                
    */
    ReturnCode m_returnCode;

    /* Please see man pages for details 
        
        
        
    */
    u8                  m_reserved[OUTPUT_RESERVED_SIZE];

public:

    //----------------------------------------
    //

    /* Please see man pages for details 
        

        

        
    */
    void InitAll();


    /* Please see man pages for details 
        

        

        
    */
    void InitValue();

    //----------------------------------------
    //

    /* Please see man pages for details 
        

        
        

        
    */
    void SetReturnCode(ReturnCode returnCode);

    /* Please see man pages for details 
        


        
        

        
    */
    void SetValue(const wchar_t* value);

    //----------------------------------------
    //

    /* Please see man pages for details 

        
        
    */
    ReturnCode GetReturnCode() const;

    /* Please see man pages for details 
        
        
    */
    const wchar_t* GetValue() const;

    /* Please see man pages for details 
        
        
    */
    u16 GetValueLen() const;
};

} // end of namespace CTR
} // end of namespace phtsel
} // end of namespace nn

#endif /*__cplusplus*/

#endif /* NN_PHTSEL_CTR_PHTSEL_OUTPUT_H_ */
