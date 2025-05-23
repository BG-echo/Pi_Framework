#pragma once

#if defined(_WIN32)
    #define PI_PLATFORM_WINDOWS
#endif

#ifdef PI_PLATFORM_WINDOWS
    #ifdef PI_BUILD_DLL
        #define PI_API __declspec(dllexport)
        struct __pi__* __ref_piSysComp__;
    #else
        #ifdef __cplusplus
            #define PI_API "C" __declspec(dllimport)
        #else
            #define PI_API __declspec(dllimport)
        #endif
    #endif
#else
    #ifdef PI_BUILD_DLL
        #define PI_API __attribute__((visibility("default")))
        struct __pi__* __ref_piSysComp__;
    #else
        #define PI_API "C"
    #endif
#endif

#ifdef PI_PLATFORM_WINDOWS
    #include "Windows.h"
    typedef HMONITOR PI_Monitor;
    typedef MONITORINFO PI_MonitorInfo;
    typedef struct PI_Window PI_Window;
    typedef RECT PI_Rect;
    typedef POINT PI_Point;
#endif