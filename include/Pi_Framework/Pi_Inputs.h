#pragma once

#include <stdbool.h>
#include "Pi_Core.h"

#ifdef PI_PLATFORM_WINDOWS
    #define PI_SPACE    VK_SPACE
    #define PI_CAPITAL  VK_CAPITAL
    #define PI_LSHIFT   VK_LSHIFT
    #define PI_RSHIFT   VK_RSHIFT
    #define PI_LCONTROL VK_LCONTROL
    #define PI_RCONTROL VK_RCONTROL
    #define PI_LMENU    VK_LMENU
    #define PI_RMENU    VK_RMENU
#endif

enum PI_KEYS {
    A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

enum PI_KEYSTATE {
    PI_KEYUP = 0, 
    PI_KEYDOWN 
};
//Mouse Inputs
extern PI_API void pi_GetMousePos(int* x, int* y);

//Keyborad Inputs
extern PI_API bool pi_GetKeyState(enum PI_KEYS key);
extern PI_API bool pi_IsKeyDown(enum PI_KEYS key);