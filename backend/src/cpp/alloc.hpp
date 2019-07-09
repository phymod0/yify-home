#ifndef CPP_LIB
#define CPP_LIB


void* operator new(size_t sz);
void* operator new[](size_t sz);
void operator delete(void* ptr);
void operator delete(void* ptr, size_t sz);
void operator delete[](void* ptr);
void operator delete[](void* ptr, size_t sz);


#endif
