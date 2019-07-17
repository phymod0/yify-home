#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "edb.hpp"
#include "../cpp_compat/alloc.hpp"
#include "../cpp_compat/string.hpp"


static uint32_t u32_read(FILE* fd)
{
	uint32_t N = 0;
	N = (N << 8) | (uint32_t)fgetc(fd);
	N = (N << 8) | (uint32_t)fgetc(fd);
	N = (N << 8) | (uint32_t)fgetc(fd);
	N = (N << 8) | (uint32_t)fgetc(fd);
	return N;
}


static void u32_write(FILE* fd, uint32_t N)
{
	fputc((N >> 24) & 0xFF, fd);
	fputc((N >> 16) & 0xFF, fd);
	fputc((N >>  8) & 0xFF, fd);
	fputc((N >>  0) & 0xFF, fd);
}


EDB::EDB(const char* dbPath) : dbPath(dbPath)
{ }


EDB::EDB(const string& dbPath) : dbPath(dbPath)
{ }


/* TODO: Remove scope resolution from arguments if possible */
void EDB::forEach(ReaderFn fn) const
{
	FILE* fd = fopen(dbPath.c_str(), "r");
	if (not fd)
		return;

	uint32_t nEntries = u32_read(fd);

	long pos = 4;
	uint32_t maxLen = 0;
	char* buf = new char[0];
	for (uint32_t i=0; i<nEntries; ++i) {
		uint32_t len = u32_read(fd);
		if (len > maxLen) {
			maxLen = len;
			delete[] buf;
			buf = new char[len];
		}
		fread(buf, 1, len, fd);
		fn(buf, len, pos);
		pos += 4 + len;
	}
	delete[] buf;

	fclose(fd);
}


void EDB::forEach(ContextFreeReaderFn fn) const
{
	FILE* fd = fopen(dbPath.c_str(), "r");
	if (not fd)
		return;

	uint32_t nEntries = u32_read(fd);

	uint32_t maxLen = 0;
	char* buf = new char[0];
	for (uint32_t i=0; i<nEntries; ++i) {
		uint32_t len = u32_read(fd);
		if (len > maxLen) {
			maxLen = len;
			delete[] buf;
			buf = new char[len];
		}
		fread(buf, 1, len, fd);
		fn(buf, len);
	}
	delete[] buf;

	fclose(fd);
}


long EDB::addEntry(const char* buf, uint32_t len) const
{
	auto incrementEntryCount = [&]()
	{
		FILE* fd = fopen(dbPath.c_str(), "r+");
		uint32_t nEntries = u32_read(fd);
		fseek(fd, 0, SEEK_SET);
		u32_write(fd, nEntries + 1);
		fclose(fd);
	};

	FILE* fd = fopen(dbPath.c_str(), "a");

	long pos = ftell(fd);
	if (pos == 0) {
		/* Newly created file, write the initial 0 */
		u32_write(fd, 0);
		pos = 4;
	}
	u32_write(fd, len);
	fwrite(buf, 1, len, fd);

	fclose(fd);
	incrementEntryCount();
	return pos;
}


void EDB::forEntryAt(long entryPos, ContextFreeReaderFn fn) const
{
	FILE* fd = fopen(dbPath.c_str(), "r");
	if (not fd)
		return;

	fseek(fd, entryPos, SEEK_SET);
	uint32_t len = u32_read(fd);
	char* buf = new char[len];
	fread(buf, 1, len, fd);
	fn(buf, len);
	delete[] buf;

	fclose(fd);
}


#if 0
int main()
{
	EDB edb(string("words.db"));
	edb.forEach([](const char* buf, uint32_t len, long pos) {
		printf("Got entry: ");
		for (uint32_t i=0; i<len; ++i)
			printf("%c", buf[i]);
		printf(" at position %ld\n", pos);
	});
	edb.forEntryAt(42, [&](const char* buf, uint32_t len){
		printf("Entry at 42: ");
		for (uint32_t i=0; i<len; ++i)
			printf("%c", buf[i]);
		printf("\n");
	});

	return 0;
}
#endif
