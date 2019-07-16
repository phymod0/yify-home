#ifndef STRING
#define STRING


class string {
	size_t len;
	char* str;
public:
	string();
	string(const string& s);
	string& operator=(const string& str);
	~string();
	string(const char* str);
	string& operator=(const char* str);
	char operator[](int idx) const;
	size_t length() const;
	const char* c_str() const;
};


#endif /* STRING */
