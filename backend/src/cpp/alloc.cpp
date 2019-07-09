#include <stdlib.h>


void* operator new(size_t sz)
{
	return malloc(sz);
}

void* operator new[](size_t sz)
{
	return malloc(sz);
}

void operator delete(void* ptr)
{
	if (ptr)
		free(ptr);
}

void operator delete(void* ptr, size_t sz __attribute__((__unused__)))
{
	if (ptr)
		free(ptr);
}

void operator delete[](void* ptr)
{
	if (ptr)
		free(ptr);
}

void operator delete[](void* ptr, size_t sz __attribute__((__unused__)))
{
	if (ptr)
		free(ptr);
}
