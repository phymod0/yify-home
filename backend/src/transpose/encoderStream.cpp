#include <string.h>

#include "transpose.hpp"


template<typename T>
static T min(const T& a, const T& b)
{
	return a < b ? a : b;
}


Transpose::EncoderStream::EncoderStream(const Transpose& T) :
	nLenRead(0),
	nDataRead(0),
	partiallyEncoded(T.head)
{ }


Transpose::EncoderStream::~EncoderStream()
{ }


size_t Transpose::EncoderStream::read(uint8_t* buf, size_t sz)
{
	constexpr size_t lenSz = sizeof partiallyEncoded->dataLen;

	auto readComplete = [&]() -> bool
	{
		bool encodingComplete =
			not partiallyEncoded->next and nLenRead == lenSz
			and nDataRead == (size_t)partiallyEncoded->dataLen;
		return sz == 0 or encodingComplete;
	};

	auto readDataLen = [&]()
	{
		auto getByte = [](uint32_t n, int i) -> uint8_t
		{
			return (n >> (8*i)) & 0xFF;
		};
		const uint32_t len = partiallyEncoded->dataLen;
		for (; sz > 0 and nLenRead < lenSz; --sz, ++nLenRead)
			*buf++ = getByte(len, lenSz - nLenRead - 1);
	};

	auto readData = [&]()
	{
		const size_t len = (size_t)partiallyEncoded->dataLen;
		const uint32_t nDataRemaining = min(sz, len - nDataRead);
		memcpy(buf, &partiallyEncoded->data[nDataRead], nDataRemaining);
		sz -= nDataRemaining;
		buf += nDataRemaining;
		nDataRead += nDataRemaining;
	};

	auto nextColumn = [&]()
	{
		if (sz == 0 or not partiallyEncoded->next)
			return;
		nLenRead = nDataRead = 0;
		partiallyEncoded = partiallyEncoded->next;
	};

	const size_t oldSz = sz;
	while (not readComplete()) {
		readDataLen();
		readData();
		nextColumn();
	}
	return oldSz - sz;
}
