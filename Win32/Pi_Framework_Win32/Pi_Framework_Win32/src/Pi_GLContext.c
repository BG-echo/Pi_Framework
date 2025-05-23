#pragma once

#include "Pi_GLContext.h"
#include "Pi_Defines.h"

static void __pi_CreateContext(PI_Window* window)
{
	PI_NULLPTR_ASSERT(window);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	window->m_device_context = GetDC(window->m_window);
	int iPixelFormat;

	iPixelFormat = ChoosePixelFormat(window->m_device_context, &pfd);
	PI_ASSERT(iPixelFormat, PI_EC_OPENGL_PIXELFORMAT, , "The pfd was not filled out correctly.\n");

	SetPixelFormat(window->m_device_context, iPixelFormat, &pfd);

	window->m_ogl_context = wglCreateContext(window->m_device_context);
}

PI_API void pi_MakeContextCurrent(PI_Window* window)
{
	__pi_CreateContext(window);

	if (wglMakeCurrent(window->m_device_context, window->m_ogl_context) == FALSE)
	{
		perror("Couldn't make the context current.\n");
		exit(PI_EC_OPENGL_CONTEXT_CREATION);
	}
}

PI_API void pi_DeleteContext(PI_Window* window)
{
	PI_NULLPTR_ASSERT(window);
	
	if (window->m_ogl_context == NULL)
	{
		return;
	}

	if (window->m_device_context)
	{
		ReleaseDC(window->m_window, window->m_device_context);
	}

	wglMakeCurrent(NULL, NULL);
	if (!wglDeleteContext(window->m_ogl_context))
	{
		perror("Couldn't delete the context.\n");
		exit(PI_EC_OPENGL_CONTEXT_DELETION);
	}
}

PI_API void pi_SwapBuffers(PI_Window* window)
{
	PI_NULLPTR_ASSERT(window);
	PI_NULLPTR_ASSERT(window->m_device_context);

	if (wglSwapLayerBuffers(window->m_device_context, WGL_SWAP_MAIN_PLANE) == FALSE)
	{
		return;
	}
}