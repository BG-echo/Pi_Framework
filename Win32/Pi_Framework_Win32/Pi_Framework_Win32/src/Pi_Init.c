#include "Pi_Init.h"
#include "Pi_GLContext.h"
#include "Pi_Allocator.h"
#include "Pi_Window_.h"
#include "Pi_System.h"
#include "Pi_Defines.h"

static void __pi_DeleteContexts()
{
	for (int i = 0; i < __ref_piSysComp__->windowListCount; ++i)
	{
		pi_DeleteContext(__ref_piSysComp__->windowList[i]);
	}
}

static void __pi_DeleteWindows()
{
	for (int i = 0; i < __ref_piSysComp__->windowListCount; ++i)
	{
		pi_DeleteWindow(__ref_piSysComp__->windowList[i]);
	}
}

PI_API void pi_Initialize()
{
	static struct __pi__ __piSysComp__;
	__ref_piSysComp__ = &__piSysComp__;

	__piSysComp__.monitorCount = __pi_GetMonitorCount();
	__piSysComp__.hmMonitors = __pi_GetMonitors();
	__piSysComp__.windowList = (PI_Window**)pi_AllocateHeap(sizeof(PI_Window*) * 1);
	__piSysComp__.windowListCount = 0;
	__piSysComp__.lastWindowClose.m_window = NULL;

	__pi_RegisterWC(__pi_GetInstance());
}

PI_API void pi_Terminate()
{
	__pi_DeleteContexts();
	__pi_DeleteWindows();

	pi_FreeHeap(__ref_piSysComp__->windowList);

	exit(PI_EC_OK);
}
