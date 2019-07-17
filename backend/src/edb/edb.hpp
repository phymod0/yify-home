#ifndef ENTRYDB
#define ENTRYDB


#include "../cpp_compat/string.hpp"
#include "../cpp_compat/functional.hpp"


class EDB {
	string dbPath;
public:
	typedef std::function<void(const char*, uint32_t)> ContextFreeReaderFn;
	typedef std::function<void(const char*, uint32_t, long)> ReaderFn;
	EDB(const char* dbPath);
	EDB(const string& dbPath);
	void forEach(ReaderFn fn) const;
	void forEach(ContextFreeReaderFn fn) const;
	long addEntry(const char* buf, uint32_t len) const;
	void forEntryAt(long entryPos, ContextFreeReaderFn fn) const;
};


#endif /* ENTRYDB */
