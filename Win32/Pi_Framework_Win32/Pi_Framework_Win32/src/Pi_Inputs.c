#include "Windows.h"
#include "Pi_Inputs.h"

PI_API void pi_GetMousePos(int* x, int* y)
{
	POINT defMousePoint;
	GetCursorPos(&defMousePoint);

	*x = defMousePoint.x;
	*y = defMousePoint.y;
}

PI_API bool pi_GetKeyState(enum PI_KEYS key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return PI_KEYDOWN;
	}

	return PI_KEYUP;
}

PI_API bool pi_IsKeyDown(enum PI_KEYS key)
{
	if (pi_GetKeyState(key))
	{
		return true;
	}

	return false;
}