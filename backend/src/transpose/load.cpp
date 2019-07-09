#include <string.h>

#include "../cpp/alloc.hpp"
#include "transpose.hpp"


template<typename T>
static void loadPrimitive(Column*& head, Column*& tail, T obj)
{
	constexpr size_t sz = sizeof(T);
	uint8_t* data = new uint8_t[sz];

	switch (sz) {
	case 8: data[7] = (uint8_t)(obj & 0xFF), obj >>= 8;
		data[6] = (uint8_t)(obj & 0xFF), obj >>= 8;
		data[5] = (uint8_t)(obj & 0xFF), obj >>= 8;
		data[4] = (uint8_t)(obj & 0xFF), obj >>= 8;
		/* fallthrough */
	case 4: data[3] = (uint8_t)(obj & 0xFF), obj >>= 8;
		data[2] = (uint8_t)(obj & 0xFF), obj >>= 8;
		/* fallthrough */
	case 2: data[1] = (uint8_t)(obj & 0xFF), obj >>= 8;
		/* fallthrough */
	case 1: data[0] = (uint8_t)(obj & 0xFF);
		/* fallthrough */
	default: /* FIXME: Case not handled */
		break;
	}

	Column* col = new Column();
	col->dataLen = sz;
	col->data = data;
	if (not (head or tail))
		head = tail = col;
	else
		tail = tail->next = col;
}


template<>
void Transpose::load<bool>(const bool& obj)
{
	loadPrimitive<bool>(head, tail, obj);
}


template<>
void Transpose::load<char>(const char& obj)
{
	loadPrimitive<char>(head, tail, obj);
}


template<>
void Transpose::load<unsigned char>(const unsigned char& obj)
{
	loadPrimitive<unsigned char>(head, tail, obj);
}


template<>
void Transpose::load<unsigned short>(const unsigned short& obj)
{
	loadPrimitive<unsigned short>(head, tail, obj);
}


template<>
void Transpose::load<unsigned int>(const unsigned int& obj)
{
	loadPrimitive<unsigned int>(head, tail, obj);
}


template<>
void Transpose::load<unsigned long>(const unsigned long& obj)
{
	loadPrimitive<unsigned long>(head, tail, obj);
}


template<>
void Transpose::load<unsigned long long>(const unsigned long long& obj)
{
	loadPrimitive<unsigned long long>(head, tail, obj);
}


template<>
void Transpose::load<signed char>(const signed char& obj)
{
	loadPrimitive<signed char>(head, tail, obj);
}


template<>
void Transpose::load<signed short>(const signed short& obj)
{
	loadPrimitive<signed short>(head, tail, obj);
}


template<>
void Transpose::load<signed int>(const signed int& obj)
{
	loadPrimitive<signed int>(head, tail, obj);
}


template<>
void Transpose::load<signed long>(const signed long& obj)
{
	loadPrimitive<signed long>(head, tail, obj);
}


template<>
void Transpose::load<signed long long>(const signed long long& obj)
{
	loadPrimitive<signed long long>(head, tail, obj);
}


void Transpose::loadCString(const char* str)
{
	Column* col = new Column();
	col->dataLen = strlen(str) + 1;
	col->dataExternal = true;
	col->data = (uint8_t*)str;

	if (empty())
		head = tail = col;
	else
		tail = tail->next = col;
}


void Transpose::loadCStringCopy(const char* str)
{
	uint32_t len = (uint32_t)strlen(str) + 1;
	uint8_t* data = new uint8_t[len];
	memcpy(data, str, len);

	Column* col = new Column();
	col->dataLen = len;
	col->data = data;

	if (empty())
		head = tail = col;
	else
		tail = tail->next = col;
}
