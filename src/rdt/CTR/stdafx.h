// stdafx.h: Specifies include files for standard system include files. Also specifies project-specific include files that are referenced often and do not change often. 
// 
// 
//
#ifdef _WIN32

#pragma once

//#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <cstring>
#include "types.h"
#include <nn/Result.h>

#else

#include <nn.h>
#include <nn/types.h>
#include <nn/Result.h>
#include <nn/uds.h>

#endif

// TODO: Reference additional headers required by the program here.
