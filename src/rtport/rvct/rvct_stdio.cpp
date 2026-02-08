/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     rvct_stdio.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 48158 $
 *---------------------------------------------------------------------------*/

#include <nn/types.h>
#include <nn/config.h>
#include <nn/assert.h>
#include <nn/os/CTR/os_ThreadLocalRegion.h>

#include <rt_sys.h>
#include <rt_misc.h>
#include <time.h>
#include <stdio.h>
#include <typeinfo>
#include <cstring>

#ifndef NN_DEBUGGER_ARM_REALVIEW

#pragma import(__use_no_semihosting_swi)
#pragma import(__use_c99_matherr)

extern "C"
{
    // rt_sys.h
    const char __stdin_name[]  = "";
    const char __stdout_name[] = "";
    const char __stderr_name[] = "";

    FILEHANDLE _sys_open(const char * name, int openmode) { NN_UNUSED_VAR(name); NN_UNUSED_VAR(openmode); return -1; }
    int     _sys_close(FILEHANDLE fh)           { NN_UNUSED_VAR(fh); return -1; }
    int     _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode) { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(buf); NN_UNUSED_VAR(len); NN_UNUSED_VAR(mode); return -1; }
    int     _sys_read(FILEHANDLE fh, unsigned char * buf, unsigned len, int mode) { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(buf); NN_UNUSED_VAR(len); NN_UNUSED_VAR(mode); return len; }
    void    _ttywrch(int ch)                    { NN_UNUSED_VAR(ch); }
    int     _sys_istty(FILEHANDLE fh)           { NN_UNUSED_VAR(fh); return -1; }
    int     _sys_seek(FILEHANDLE fh, long pos)  { NN_UNUSED_VAR(fh); NN_UNUSED_VAR(pos); return -1; }
    int     _sys_ensure(FILEHANDLE fh)          { NN_UNUSED_VAR(fh); return -1; }
    long    _sys_flen(FILEHANDLE fh)            { NN_UNUSED_VAR(fh); return -1; }
    int     _sys_tmpnam(char *name, int fileno, unsigned maxlength) { NN_UNUSED_VAR(name); NN_UNUSED_VAR(fileno); NN_UNUSED_VAR(maxlength); return -1; }
    void    _sys_exit(int return_code)          { NN_UNUSED_VAR(return_code); }
    char*   _sys_command_string (char* cmd, int len) { NN_UNUSED_VAR(cmd); NN_UNUSED_VAR(len); return NULL; }

    // rt_misc.h
//    void _getenv_init(void) {}
//    void _clock_init(void) {}
    int __raise(int signal, int type) { NN_UNUSED_VAR(signal); NN_UNUSED_VAR(type); return 0; }
    void __rt_raise(int sig, int type) { NN_UNUSED_VAR(sig); NN_UNUSED_VAR(type); }

    // Standard functions
    void abort()        { NN_PANIC("abort() called\n"); }
//    clock_t clock(void) { return 0; }
//    time_t time(time_t* timer){ NN_UNUSED_VAR(timer); return 0; }
//    char* getenv(const char* name) { NN_UNUSED_VAR(name); return NULL; }
//    int remove(const char* filename) { NN_UNUSED_VAR(filename); return -1; }
//    int rename(const char* old, const char* newname) { NN_UNUSED_VAR(old); NN_UNUSED_VAR(newname); return -1; }
//    int system(const char* string) { NN_UNUSED_VAR(string); return -1; }

    // Other
    void __aeabi_atexit()       {}
    void __cxa_finalize()       {}
    void __rt_SIGTMEM()         {}
    void __rt_SIGABRT()         {}
    void __rt_div0()            {}


    void** __rt_eh_globals_addr()
    {
        return &nn::os::CTR::GetThreadLocalRegion()->ehGlobalsAddr;
    }
}

namespace std
{
    bool type_info::operator==(const type_info& rhs) const
    {
        return std::strcmp(this->name(), rhs.name()) == 0;
    }
    bool type_info::operator!=(const type_info& rhs) const
    {
        return std::strcmp(this->name(), rhs.name()) != 0;
    }
    bool type_info::before(const type_info& rhs) const
    {
        return std::strcmp(this->name(), rhs.name()) < 0;
    }
}


#else

extern "C"
{
    void __aeabi_atexit()       {}
}

#endif
