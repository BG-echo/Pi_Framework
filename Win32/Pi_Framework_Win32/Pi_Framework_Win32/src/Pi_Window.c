#include "Pi_Window_.h"
#include "Pi_Allocator.h"
#include "Pi_Defines.h"
#include "Pi_GLContext.h"

#define PI_DEFAULT_WINDOW_CLASS_NAME L"PI_DEFAULT_WINDOW_CLASS"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_QUIT: 
		PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
	{
		__ref_piSysComp__->lastWindowClose.m_window = hWnd;
		DestroyWindow(hWnd);
		hWnd = NULL;
		return 0;
	}

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HINSTANCE __pi_GetInstance()
{
	return GetModuleHandle(NULL);
}

int __pi_RegisterWC(HINSTANCE hInstance)
{
	WNDCLASS defWindowClass = {
		.lpszClassName = PI_DEFAULT_WINDOW_CLASS_NAME,
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.hIcon = LoadIcon(NULL, IDI_WINLOGO),
		.hInstance = hInstance,
		.lpfnWndProc = WndProc,
		.style = CS_OWNDC
	};

	if (!RegisterClass(&defWindowClass))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_CLASS_ALREADY_EXISTS)
			return HRESULT_FROM_WIN32(dwError);
	}

	return 0;
}

PI_API PI_Window* pi_CreateWindow(int x, int y, int w, int h, LPCWSTR title, PI_Window* parentWindow)
{
	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME | WS_SIZEBOX | WS_MAXIMIZEBOX;
	
	__ref_piSysComp__->windowListCount++;
	__ref_piSysComp__->windowList = (PI_Window**)pi_ReallocateHeap(__ref_piSysComp__->windowList, __ref_piSysComp__->windowListCount * sizeof(PI_Window*));


	PI_Window* _window = (PI_Window*)pi_AllocateHeap(sizeof(PI_Window) * 1);
	__ref_piSysComp__->windowList[__ref_piSysComp__->windowListCount - 1] = _window;

	_window->m_window = CreateWindowEx(
		0,
		PI_DEFAULT_WINDOW_CLASS_NAME,
		title,
		style,
		x,
		y,
		w,
		h,
		parentWindow == NULL ? NULL : parentWindow->m_window,
		NULL,
		__pi_GetInstance(),
		NULL);
	
	_window->m_device_context = NULL;
	_window->m_ogl_context = NULL;

	PI_NULLPTR_ASSERT(_window->m_window);

	EnableWindow(_window->m_window, TRUE);
	ShowWindow(_window->m_window, SW_SHOW);

	return _window;
}

PI_API void pi_DeleteWindow(PI_Window* window)
{
	PI_NULLPTR_ASSERT(window);

	window->m_window = NULL;
	window->m_device_context = NULL;
	window->m_ogl_context = NULL;

	pi_FreeHeap(window);
}

PI_API void pi_GetWindowPos(PI_Window* window, int* x, int* y)
{
	PI_NULLPTR_ASSERT(window);
	PI_NULLPTR_ASSERT(window->m_window);

	RECT defWindowRect;
	GetWindowRect(window->m_window, &defWindowRect);

	*x = defWindowRect.left;
	*y = defWindowRect.top;
}

PI_API void pi_GetWindowSize(PI_Window* window, int* w, int* h)
{
	PI_NULLPTR_ASSERT(window);
	PI_NULLPTR_ASSERT(window->m_window);

	RECT defWindowRect;
	GetWindowRect(window->m_window, &defWindowRect);

	*w = defWindowRect.right - defWindowRect.left;
	*h = defWindowRect.bottom - defWindowRect.top;
}

PI_API int pi_ProcessWindowShouldClose(PI_Window* window)
{
	PI_NULLPTR_ASSERT(window);
	static MSG uMsg;

	PeekMessage(&uMsg, NULL, 0u, 0u, PM_REMOVE);

	if (__ref_piSysComp__->lastWindowClose.m_window == window->m_window)
	{
		PostQuitMessage(0);
		return FALSE;
	}

	TranslateMessage(&uMsg);
	DispatchMessage(&uMsg);

	Sleep(20);

	return TRUE;
}


PI_API int pi_ProcessMessages()
{
	static MSG uMsg;

	GetMessage(&uMsg, NULL, 0u, 0u);

	if (uMsg.message == WM_QUIT)
		return FALSE;

	TranslateMessage(&uMsg);
	DispatchMessage(&uMsg);

	return TRUE;
}