#ifndef COLUMN
#define COLUMN


class Column {
public:
	uint32_t dataLen;
	bool dataExternal;
	uint8_t* data;
	Column* next;

	inline Column()
	{
		dataLen = 0;
		dataExternal = false;
		data = nullptr;
		next = nullptr;
	}
	inline Column(const Column& col)
	{
		dataLen = col.dataLen;
		if ((dataExternal = col.dataExternal))
			data = col.data;
		else {
			data = new uint8_t[dataLen];
			memcpy(data, col.data, dataLen);
		}
		next = nullptr;
	}
	inline ~Column()
	{
		if (!dataExternal)
			delete[] data;
	}
};


#endif /* COLUMN */
