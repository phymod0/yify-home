#ifndef PAIR
#define PAIR


template<typename S, typename T>
struct pair {
	S first;
	T second;
	inline pair() { }
	inline pair(S s, T t) : first(s), second(t) { }
};


#endif /* PAIR */
