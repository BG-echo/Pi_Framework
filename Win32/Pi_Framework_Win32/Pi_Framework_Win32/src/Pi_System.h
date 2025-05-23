#pragma once

#include "Pi_Core.h"

//Monitor
extern int __pi_GetMonitorCount();
extern PI_Monitor __pi_GetPrimaryMonitor();
extern PI_Monitor* __pi_GetMonitors();

//Window
extern HWND __pi_GetLastWindowClose();