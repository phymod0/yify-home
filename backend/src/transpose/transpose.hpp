#ifndef TRANSPOSE
#define TRANSPOSE

#include <stdint.h>

#include "column.hpp"


class Transpose {
	Column *head, *tail;

public:
	Transpose();
	Transpose(const Transpose& T);
	~Transpose();

	bool empty() const;
	void operator+=(const Transpose& T);

	class EncoderStream {
		size_t nLenRead, nDataRead;
		Column *partiallyEncoded;
	public:
		EncoderStream(const Transpose& T);
		~EncoderStream();
		size_t read(uint8_t* buf, size_t sz);
	};

	class DecoderStream {
		Transpose& T;
		size_t nLenWritten, nDataWritten;
		uint32_t partialDataLen;
		uint8_t* partialData;
	public:
		DecoderStream(Transpose& T);
		~DecoderStream();
		void write(const uint8_t* buf, size_t n);
	};

	template<typename T>
	void load(const T& obj)
	{
		obj.transpose(*this);
	}
	void loadCString(const char* str);
	void loadCStringCopy(const char* str);
#if 0
	template<typename T>
	void loadArray(T* array, size_t n);
	template<typename T>
	void loadOnDemand(T* obj);
	template<typename T>
	void loadOnDemand(T* array, size_t n);
#endif

	template<typename T>
	void unload(T& obj)
	{
		obj = T(*this);
	}
	void unloadCString(char*& str);

	template<typename T>
	Transpose(const T& obj)
	{
		head = tail = nullptr;
		this->load(obj);
	}
	Transpose(const uint8_t* buf, size_t n);
};


template<>
void Transpose::load<bool>(const bool&);
template<>
void Transpose::load<char>(const char&);
template<>
void Transpose::load<unsigned char>(const unsigned char&);
template<>
void Transpose::load<unsigned short>(const unsigned short&);
template<>
void Transpose::load<unsigned int>(const unsigned int&);
template<>
void Transpose::load<unsigned long>(const unsigned long&);
template<>
void Transpose::load<unsigned long long>(const unsigned long long&);
template<>
void Transpose::load<signed char>(const signed char&);
template<>
void Transpose::load<signed short>(const signed short&);
template<>
void Transpose::load<signed int>(const signed int&);
template<>
void Transpose::load<signed long>(const signed long&);
template<>
void Transpose::load<signed long long>(const signed long long&);


template<>
void Transpose::unload<bool>(bool&);
template<>
void Transpose::unload<char>(char&);
template<>
void Transpose::unload<unsigned char>(unsigned char&);
template<>
void Transpose::unload<unsigned short>(unsigned short&);
template<>
void Transpose::unload<unsigned int>(unsigned int&);
template<>
void Transpose::unload<unsigned long>(unsigned long&);
template<>
void Transpose::unload<unsigned long long>(unsigned long long&);
template<>
void Transpose::unload<signed char>(signed char&);
template<>
void Transpose::unload<signed short>(signed short&);
template<>
void Transpose::unload<signed int>(signed int&);
template<>
void Transpose::unload<signed long>(signed long&);
template<>
void Transpose::unload<signed long long>(signed long long&);


#endif /* TRANSPOSE */
