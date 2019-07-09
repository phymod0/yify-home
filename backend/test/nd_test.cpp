#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <vector>


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


class Group {
private:
	int len;
	int* a;
public:
	Group()
	{
		printf("Called constructor...\n");
		a = new int[len = 5];
	}
	void setInt(int n, int idx)
	{
		std::function<void(int)> set = [&](int i) {
			a[i] = n;
		};
		set(idx);
	}
	~Group()
	{
		delete[] a;
		printf("Called destructor...\n");
	}
};


void std::__throw_bad_function_call()
{
	printf("Hi fags...\n");
	while (1);
}


int main()
{
	int i = 5;
	std::function<void(void)> print_i = [&]() {
		printf("%d\n", i);
	};

	print_i();

	return 0;
}
