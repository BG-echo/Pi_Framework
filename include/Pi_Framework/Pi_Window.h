#pragma once

#include "Pi_Core.h"

//Window functions
extern PI_API PI_Window* pi_CreateWindow(int x, int y, int w, int h, LPCWSTR title, PI_Window* parentWindow);
extern PI_API void pi_DeleteWindow(PI_Window* window);
extern PI_API void pi_GetWindowPos(PI_Window* window, int* x, int* y);
extern PI_API void pi_GetWindowSize(PI_Window* window, int* w, int* h);

//Handle the Events
extern PI_API int pi_ProcessWindowShouldClose(PI_Window* window);
extern PI_API int pi_ProcessMessages();