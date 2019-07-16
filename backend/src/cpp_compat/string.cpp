#include <string.h>

#include "alloc.hpp"
#include "string.hpp"


static char* _Strdup(const char* str)
{
	size_t len = strlen(str);
	char* result = new char[len + 1];
	memcpy(result, str, len + 1);
	return result;
}


string::string() : len(0), str(_Strdup(""))
{ }


string::string(const string& s) : len(s.len), str(_Strdup(s.str))
{ }


string& string::operator=(const string& s)
{
	delete[] str;
	len = s.len;
	str = _Strdup(s.str);
	return *this;
}


string::~string()
{
	delete[] str;
}


string::string(const char* cstr) : len(strlen(cstr)), str(_Strdup(cstr))
{ }


string& string::operator=(const char* cstr)
{
	delete[] str;
	len = strlen(cstr);
	str = _Strdup(cstr);
	return *this;
}


char string::operator[](int idx) const
{
	return str[idx];
}


size_t string::length() const
{
	return len;
}


const char* string::c_str() const
{
	return str;
}


#if 0
#include <stdio.h>
int main()
{
	string str = "abcdef";
	str = "Hello world!";
	str = string("Hello!");

	for (size_t i=0; i<str.length(); ++i)
		printf("%c", str[i]);
	printf("\n");

	return 0;
}
#endif
