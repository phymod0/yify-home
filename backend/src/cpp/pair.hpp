#ifndef PAIR
#define PAIR


template<typename S, typename T>
struct pair {
	S first;
	T second;
	pair(S s, T t) : first(s), second(t) { }
};


#endif /* PAIR */
