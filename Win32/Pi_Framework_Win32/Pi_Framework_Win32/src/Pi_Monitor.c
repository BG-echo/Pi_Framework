#include "Pi_Monitor.h"

PI_API void pi_GetMonitorPos(PI_Monitor* monitor, int* x, int* y)
{
	PI_MonitorInfo monitor_info;
	monitor_info.cbSize = sizeof(PI_MonitorInfo);

	GetMonitorInfo(*monitor, &monitor_info);

	*x = monitor_info.rcMonitor.left;
	*y = monitor_info.rcMonitor.top;
}