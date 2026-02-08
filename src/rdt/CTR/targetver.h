#pragma once

// The following macro defines the minimum required platform. The minimum required platform is the oldest version of Windows or Internet Explorer, etc. that has the features required to run the application.
//
//These macros operate by enabling all features that can be used on the specified or earlier versions of the platform. 
// 

// If the target platform must be specified before the definitions specified below, then change the definitions below.
// Refer to MSDN for the most recent information regarding values corresponding to different platforms.
#ifndef _WIN32_WINNT            // Specifies that Windows Vista is the minimum required platform.
#define _WIN32_WINNT 0x0600     // Change this to a value appropriate for other Windows versions.
#endif

