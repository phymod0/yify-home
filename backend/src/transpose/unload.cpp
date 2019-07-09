#include <string.h>

#include "../cpp/alloc.hpp"
#include "../cpp/typeTraits.hpp"
#include "transpose.hpp"


template<typename T>
static inline void unloadPrimitive(Column*& head, Column*& tail, T& obj)
{
	if (not head)
		return;
	const size_t len = (size_t)head->dataLen;
	const uint8_t* data = head->data;

	auto uObj = TypeTraits::toUnsigned((T)0);
	uObj = data[0];
	for (size_t i=1; i<len; ++i)
		uObj = (uObj << 8) | data[i];
	obj = TypeTraits::toSigned(uObj);

	Column* oldHead = head;
	if (not (head = head->next))
		tail = nullptr;
	delete oldHead;
}


template<>
void Transpose::unload<bool>(bool& obj)
{
	unloadPrimitive<bool>(head, tail, obj);
}


template<>
void Transpose::unload<char>(char& obj)
{
	unloadPrimitive<char>(head, tail, obj);
}


template<>
void Transpose::unload<unsigned char>(unsigned char& obj)
{
	unloadPrimitive<unsigned char>(head, tail, obj);
}


template<>
void Transpose::unload<unsigned short>(unsigned short& obj)
{
	unloadPrimitive<unsigned short>(head, tail, obj);
}


template<>
void Transpose::unload<unsigned int>(unsigned int& obj)
{
	unloadPrimitive<unsigned int>(head, tail, obj);
}


template<>
void Transpose::unload<unsigned long>(unsigned long& obj)
{
	unloadPrimitive<unsigned long>(head, tail, obj);
}


template<>
void Transpose::unload<unsigned long long>(unsigned long long& obj)
{
	unloadPrimitive<unsigned long long>(head, tail, obj);
}


template<>
void Transpose::unload<signed char>(signed char& obj)
{
	unloadPrimitive<signed char>(head, tail, obj);
}


template<>
void Transpose::unload<signed short>(signed short& obj)
{
	unloadPrimitive<signed short>(head, tail, obj);
}

template<>
void Transpose::unload<signed int>(signed int& obj)
{
	unloadPrimitive<signed int>(head, tail, obj);
}


template<>
void Transpose::unload<signed long>(signed long& obj)
{
	unloadPrimitive<signed long>(head, tail, obj);
}


template<>
void Transpose::unload<signed long long>(signed long long& obj)
{
	unloadPrimitive<signed long long>(head, tail, obj);
}


void Transpose::unloadCString(char*& str)
{
	if (not head)
		return;

	if (head->dataExternal) {
		str = reinterpret_cast<char*>(new uint8_t[head->dataLen]);
		memcpy(str, head->data, head->dataLen);
	} else {
		str = reinterpret_cast<char*>(head->data);
		/* XXX: To not internally free the data */
		head->dataExternal = true;
	}

	Column* oldHead = head;
	if (not (head = head->next))
		tail = nullptr;
	delete oldHead;
}
