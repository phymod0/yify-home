#include <stdlib.h>
#include <stdio.h>


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

void operator delete[](void* ptr)
{
	if (ptr)
		free(ptr);
}

void operator delete(void* ptr, size_t sz)
{
	if (ptr)
		free(ptr);
}


class A {
private:
	int* a;
public:
	A()
	{
		printf("Called constructor...\n");
		a = new int[5];
	}
	void setInt(int n, int idx)
	{
		a[idx] = n;
	}
	~A()
	{
		delete[] a;
		printf("Called destructor...\n");
	}
};


int main()
{
	A* a = new A();
	delete a;

	return 0;
}
