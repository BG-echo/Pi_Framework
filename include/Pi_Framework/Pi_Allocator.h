#pragma once

#include "Pi_Core.h"

extern PI_API void* pi_AllocateHeap(size_t size);
extern PI_API void* pi_ReallocateHeap(void* __pi_allocator__, size_t size);
extern PI_API void pi_FreeHeap(void* __pi_allocator__);