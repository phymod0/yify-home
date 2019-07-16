#ifndef JSON_WRAPPER
#define JSON_WRAPPER


#include <stdio.h>
#include <json-c/json_tokener.h>


class JSONObject {
	bool root;
	json_object* obj;
public:
	JSONObject();
	JSONObject(const JSONObject& jobj);
	JSONObject& operator=(const JSONObject& jobj);
	~JSONObject();
	JSONObject(const char* JSONStr);
	JSONObject(const char* JSONStr, size_t len);
	size_t arraySize() const;
	JSONObject operator[](int idx) const;
	JSONObject operator[](const char* key) const;
	bool toBool() const;
	int32_t toInt() const;
	int64_t toLongLongInt() const;
	double toDouble() const;
	const char* toString() const;
	void set(const char* key, bool val);
	void set(const char* key, int32_t val);
	void set(const char* key, int64_t val);
	void set(const char* key, double val);
	void set(const char* key, const char* val);
	void arrayAppend(const JSONObject& obj);
	void print() const;
};


#endif /* JSON_WRAPPER */
