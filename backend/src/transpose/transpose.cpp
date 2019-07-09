#include <string.h>

#include "../cpp/alloc.hpp"
#include "transpose.hpp"


Transpose::Transpose()
{
	head = tail = nullptr;
}


Transpose::Transpose(const Transpose& T)
{
	head = tail = nullptr;
	Column* tmp = T.head;

	if (not tmp)
		return;

	head = tail = new Column(*tmp);
	while ((tmp = tmp->next))
		tail = tail->next = new Column(*tmp);
}


Transpose::~Transpose()
{
	while (head) {
		Column* next = head->next;
		delete head;
		head = next;
	}
}


bool Transpose::empty() const
{
	return not (head or tail);
}


void Transpose::operator+=(const Transpose& T)
{
	Column* tmp = T.head;

	if (not tmp)
		return;

	if (empty())
		head = tail = new Column(*tmp);
	else
		tail = tail->next = new Column(*tmp);
	while ((tmp = tmp->next))
		tail = tail->next = new Column(*tmp);
}


Transpose::Transpose(const uint8_t* buf, size_t n)
{
	head = tail = nullptr;
	auto decoder = Transpose::DecoderStream(*this);
	decoder.write(buf, n);
}


#include <stdio.h>


class Point {
	int x, y;
public:
	Point() : x(0), y(0) { }
	Point(int x, int y) : x(x), y(y) { }
	bool operator==(const Point& P)
	{
		return x == P.x and y == P.y;
	}
	void transpose(Transpose& T) const
	{
		T.load(x);
		T.load(y);
	}
	Point(Transpose& T)
	{
		T.unload(x);
		T.unload(y);
	}
};


class Square {
	Point topLeft, bottomRight;
public:
	Square() :
		topLeft(Point(0, 0)),
		bottomRight(Point(0, 0))
	{ }
	Square(int x1, int y1, int x2, int y2) :
		topLeft(Point(x1, y1)),
		bottomRight(Point(x2, y2))
	{ }
	bool operator==(const Square& S)
	{
		return topLeft == S.topLeft and bottomRight == S.bottomRight;
	}
	void transpose(Transpose& T) const
	{
		T.load(topLeft);
		T.load(bottomRight);
	}
	Square(Transpose& T)
	{
		T.unload(topLeft);
		T.unload(bottomRight);
	}
};


#if 0
int main(void)
{
	Square U(1, 2, 3, 4);

	Transpose T(U);
	// Transpose T; T += Transpose(U);
	// Transpose T; T.load(U);

	uint8_t buf[64];
	size_t n = Transpose::EncoderStream(T).read(buf, sizeof buf);

#if 1
	Transpose S(buf, n);
#else
	Transpose S;
	auto ds = Transpose::DecoderStream(S);
	ds.write(buf, n);
#endif

#if 1
	Square V(S);
#else
	Square V;
	S.unload(V);
#endif

	if (U == V) {
		printf("Correct!\n");
	} else {
		printf("Failed...\n");
	}

	return 0;
}
#endif
