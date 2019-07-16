#ifndef JSON_WRAPPER
#define JSON_WRAPPER


#include <json-c/json_tokener.h>

#include "../cpp_compat/string.hpp"


class JSONObject {
	bool root;
	json_object* obj;
public:
	JSONObject();
	JSONObject(const JSONObject& jobj);
	JSONObject& operator=(const JSONObject& jobj);
	~JSONObject();
	JSONObject(const char* JSONStr);
	JSONObject(const string& JSONStr);
	JSONObject(const char* JSONStr, size_t len);
	size_t arraySize() const;
	JSONObject operator[](int idx) const;
	JSONObject operator[](const char* key) const;
	bool toBool() const;
	int32_t toInt() const;
	int64_t toLongLongInt() const;
	double toDouble() const;
	string toString() const;
	void assign(const char* key, bool val);
	void assign(const char* key, int32_t val);
	void assign(const char* key, int64_t val);
	void assign(const char* key, double val);
	void assign(const char* key, const char* val);
	void assign(const char* key, const JSONObject& newObj);
	void arrayAppend(bool val);
	void arrayAppend(int32_t val);
	void arrayAppend(int64_t val);
	void arrayAppend(double val);
	void arrayAppend(const char* val);
	void arrayAppend(const JSONObject& obj);
	string serialize() const;
	void print() const;
};


#endif /* JSON_WRAPPER */
