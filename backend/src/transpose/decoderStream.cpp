#include <string.h>


#include "../cpp/alloc.hpp"
#include "transpose.hpp"


template<typename T>
static T min(const T& a, const T& b)
{
	return a < b ? a : b;
}


Transpose::DecoderStream::DecoderStream(Transpose& T) :
	T(T),
	nLenWritten(0),
	nDataWritten(0),
	partialDataLen(0),
	partialData(nullptr)
{ }


Transpose::DecoderStream::~DecoderStream()
{
	delete[] partialData;
}


void Transpose::DecoderStream::write(const uint8_t* buf, size_t n)
{
	constexpr size_t lenSz = sizeof partialDataLen;

	auto writeDataLen = [&]()
	{
		for (; n > 0 and nLenWritten < lenSz; --n, ++nLenWritten)
			partialDataLen = (partialDataLen << 8) | (uint32_t)*buf++;
		if (nLenWritten == lenSz and not partialData)
			partialData = new uint8_t[partialDataLen];
	};

	auto writeData = [&]()
	{
		if (not partialData)
			return;
		const uint32_t nDataRemaining = min(n, (size_t)partialDataLen - nDataWritten);
		memcpy(&partialData[nDataWritten], buf, nDataRemaining);
		n -= nDataRemaining;
		buf += nDataRemaining;
		nDataWritten += nDataRemaining;
	};

	auto appendColumn = [&]()
	{
		if (nLenWritten < lenSz or nDataWritten < partialDataLen)
			return;
		Column* col = new Column();
		col->dataLen = partialDataLen;
		col->data = partialData;
		nLenWritten = nDataWritten = 0;
		partialDataLen = 0;
		partialData = nullptr;
		if (T.head or T.tail)
			T.tail = T.tail->next = col;
		else
			T.head = T.tail = col;
	};

	while (n) {
		writeDataLen();
		writeData();
		appendColumn();
	}
}
