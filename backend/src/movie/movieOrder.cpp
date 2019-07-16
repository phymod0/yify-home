#include "movie.hpp"


Movie::Order::Order()
{
	priorities[0] = priority(ReleaseYear, Descending);
	priorities[1] = priority(UploadYear, Descending);
	priorities[2] = priority(Rating, Descending);
}


void Movie::Order::prioritize(Type t, Weight w)
{
	int idx = 0;
	while (priorities[idx].first != t)
		++idx;
	for (int i = idx; i > 0; ++i)
		priorities[i] = priorities[i - 1];
	priorities[0] = priority(t, w);
}


int Movie::Order::operator()(const Movie& m1, const Movie& m2) const
{
	auto cmp = [&](const priority& p) -> int {
		Type t = p.first;
		Weight w = p.second;
		int result;
		if (w == Irrelevant)
			return 0;
		switch (t) {
		case Rating:
			result = m1.rating < m2.rating ? -1 : 1;
			break;
		case UploadYear:
			result = m1.uploadYear < m2.uploadYear ? -1 : 1;
			break;
		case ReleaseYear:
			result = m1.releaseYear < m2.releaseYear ? -1 : 1;
			break;
		default:
			break;
		}
		return w == Ascending ? result : -result;
	};

	int result;
	for (const priority& p : priorities)
		if ((result = cmp(p)))
			return result;
	return 0;
}


int Movie::Order::compare(const Movie& m1, const Movie& m2) const
{
	return this->operator()(m1, m2);
}


#if 0
int main() {return 0;}
#endif
