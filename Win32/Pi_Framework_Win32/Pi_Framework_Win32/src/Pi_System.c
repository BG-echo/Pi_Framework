#include "Pi_System.h"
#include "Pi_Defines.h"

//TODO : You should initialize all system related stuff previously by a call to your own function

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, RECT lprcMonitor, LPARAM dwData) 
{
	static int i = 0;
	PI_Monitor* __pi_refMonitors__ = (PI_Monitor*)dwData;

	__pi_refMonitors__[i] = MonitorFromRect(&lprcMonitor, MONITOR_DEFAULTTONULL);
	
	++i;
	return TRUE;
}

int __pi_GetMonitorCount()
{
	return GetSystemMetrics(SM_CMONITORS);
}

PI_Monitor __pi_GetPrimaryMonitor()
{
	PI_Point originPoint =
	{
		.x = 0, .y = 0
	};
	return MonitorFromPoint(originPoint, MONITOR_DEFAULTTONULL);
}

PI_Monitor* __pi_GetMonitors()
{
	static PI_Monitor __pi_monitors__[MAX_MONITOR_COUNT];

	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, __pi_monitors__);

	return __pi_monitors__;
}

HWND __pi_GetLastWindowClose()
{
	return __ref_piSysComp__->lastWindowClose.m_window;
}
