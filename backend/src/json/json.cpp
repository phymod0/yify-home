#include <stdio.h>
#include <json-c/json_tokener.h>

#include "json.hpp"


JSONObject::JSONObject()
{
	root = true;
	obj = nullptr;
}


JSONObject::JSONObject(const JSONObject& jobj)
{
	obj = nullptr;
	root = true;
	json_object_deep_copy(jobj.obj, &obj, nullptr);
}


JSONObject& JSONObject::operator=(const JSONObject& jobj)
{
	if (root) {
		json_object_put(obj);
		obj = nullptr;
	}
	if ((root = jobj.root))
		json_object_deep_copy(jobj.obj, &obj, nullptr);
	else
		obj = jobj.obj;
	return *this;
}


JSONObject::~JSONObject()
{
	if (root)
		json_object_put(obj);
}


JSONObject::JSONObject(const char* JSONStr)
{
	root = true;
	obj = json_tokener_parse(JSONStr);
}


JSONObject::JSONObject(const char* JSONStr, size_t len)
{
	root = true;
	json_tokener* tok = json_tokener_new();
	obj = json_tokener_parse_ex(tok, JSONStr, len);
	json_tokener_free(tok);
}


size_t JSONObject::arraySize() const
{
	return obj ? json_object_array_length(obj) : 0;
}


JSONObject JSONObject::operator[](int idx) const
{
	JSONObject newObj;
	newObj.root = false;
	newObj.obj = json_object_array_get_idx(obj, idx);
	return newObj;
}


JSONObject JSONObject::operator[](const char* key) const
{
	JSONObject newObj;
	newObj.root = false;
	json_object_object_get_ex(obj, key, &newObj.obj);
	return newObj;
}


bool JSONObject::toBool() const
{
	return json_object_get_boolean(obj);
}


int32_t JSONObject::toInt() const
{
	return json_object_get_int(obj);
}


int64_t JSONObject::toLongLongInt() const
{
	return json_object_get_int64(obj);
}


double JSONObject::toDouble() const
{
	return json_object_get_double(obj);
}


const char* JSONObject::toString() const
{
	return json_object_get_string(obj);
}


void JSONObject::set(const char* key, bool val)
{
	json_object_object_add(obj, key, json_object_new_boolean(val));
}


void JSONObject::set(const char* key, int32_t val)
{
	json_object_object_add(obj, key, json_object_new_int(val));
}


void JSONObject::set(const char* key, int64_t val)
{
	json_object_object_add(obj, key, json_object_new_int64(val));
}


void JSONObject::set(const char* key, double val)
{
	json_object_object_add(obj, key, json_object_new_double(val));
}


void JSONObject::set(const char* key, const char* val)
{
	json_object_object_add(obj, key, json_object_new_string(val));
}


void JSONObject::arrayAppend(const JSONObject& newObj)
{
	json_object_array_add(obj, json_object_get(newObj.obj));
}


void JSONObject::print() const
{
	printf("%s\n", json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY));
}


#if 0
int main()
{
	char* str = new char[65536];
	FILE* fd = fopen("list_movies.json", "r");
	if (not fd) {
		printf("Failed to open file\n");
		return -1;
	}
	int nRead = fread(str, 1, 65536, fd);
	// printf("%s\n", str);
	if (feof(fd))
		printf("Reached EOF\n");
	fclose(fd);

	printf("\n");
	JSONObject J(str);
	JSONObject movieList = J["movies"];
	JSONObject newMovie("{}");
	newMovie.set("title", "Hello world!");
	newMovie.set("summary", "Random HelloWood garbage");
	movieList.arrayAppend(newMovie);
	JSONObject secondMovie = movieList[1];
	const char* title = secondMovie["title"].toString();
	const char* summary = secondMovie["summary"].toString();
	printf("%s:\n\n\t%s\n\n", title, summary);
	J.print();

	delete[] str;
	return 0;
}
#endif
