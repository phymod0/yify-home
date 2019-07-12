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
	size_t arraySize();
	JSONObject operator[](int idx) const;
	JSONObject operator[](const char* key) const;
	bool toBool();
	int32_t toInt();
	int64_t toLongLongInt();
	double toDouble();
	const char* toString();
	void print();
};


#endif /* JSON_WRAPPER */
