#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "Windows.h"

#include "Pi_EC.h"

//Data types
typedef struct PI_Window
{
	HWND m_window;
	HDC m_device_context;
	HGLRC m_ogl_context;
}PI_Window;

struct __pi__
{
	int monitorCount;
	int windowListCount;
	PI_Monitor* hmMonitors;
	PI_Window** windowList;
	PI_Window lastWindowClose;
};


//The maximum number of monitors windows currently supports
#define MAX_MONITOR_COUNT 10

#define PI_ASSERT(_e, _ec, _c,...) if(!(_e)) { fprintf(stderr, __VA_ARGS__); _c; exit(_ec); }

#define PI_STRING(V)			#V
#define PI_EXPAND(V)			PI_STRING(V)

#define PI_NULLPTR_ASSERT(_e)	PI_ASSERT(_e, PI_EC_NULLPTR_EXCEPT, , "Error %s is NULL.\n", PI_STRING(_e))
//This should always be called after allocation of a variable
#define PI_ALLOC_ASSERT(_e)		PI_ASSERT(_e, PI_EC_ALLOC_FAIL, free(_e), "Failed to allocate %s.\n", PI_STRING(_e))