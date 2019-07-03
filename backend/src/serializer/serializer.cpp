#include <cstdlib>
#include <cstdint>

#include "exception.hpp"


#define VALLOC(x, n) (x = malloc((n) * sizeof *(x)))
#define ALLOC(x) VALLOC(x, 1)


struct StreamObject {
	size_t dataLen;
	void* data;
	StreamObject* next;
	StreamObject(void)
	{
		data = next = nullptr;
		dataLen = 0;
	}
};

class Stream {
private:
	StreamObject *head, *tail;
public:
	Stream(void);
	template<typename T>
	Stream(const T& obj);
	Stream(const uint8_t* buf, size_t n);
	Stream(const Stream& stream);
	~Stream(void);
	void operator+=(const Stream& stream);
	int write(uint8_t* buf, size_t n);
	int read(uint8_t* buf, size_t n);
};

Stream::Stream(void)
{
	head = tail = nullptr;
}

Stream::Stream(const Stream& stream)
{
	head = tail = nullptr;
	StreamObject* tmp = stream.head;

	if (!tmp)
		return;

	while (tmp) {
		if (!ALLOC())
		tmp = tmp->next;
	}

	return;
oom:
	// Free created
	throw oomException();
}

Stream::~Stream(void)
{
	while (head) {
		StreamObject* next = head->next;
		free(head->data);
		free(head);
		head = next;
	}
}

Stream::Stream(const uint8_t* buf, size_t n)
{


	return;
}

Stream::operator+=(const Stream& stream)
{
	stream

	return;
}


int main(void)
{
	Stream s;

	return 0;
}


#undef ALLOC
#undef VALLOC
