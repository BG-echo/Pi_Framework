#include <stdlib.h>
#include "Pi_Allocator.h"

#include "Pi_Defines.h"

//TODO : Create a new linked list named __pi_allocator__
//		Rewrite everything in the linked list way

PI_API void* pi_AllocateHeap(size_t size)
{
	void* __pi_allocator__ = malloc(size);
	PI_ALLOC_ASSERT(__pi_allocator__);
	return __pi_allocator__;
}

PI_API void* pi_ReallocateHeap(void* __pi_allocator__, size_t size)
{
	PI_NULLPTR_ASSERT(__pi_allocator__);
	void* __new_pi_allocator__ = realloc(__pi_allocator__, size);
	PI_ALLOC_ASSERT(__new_pi_allocator__);
	return __new_pi_allocator__;
}

PI_API void pi_FreeHeap(void* __pi_allocator__)
{
	free(__pi_allocator__);
	__pi_allocator__ = NULL;
}