#ifndef CPP_FUNCTIONAL_WRAPPER
#define CPP_FUNCTIONAL_WRAPPER


#include <functional>


namespace std {
	inline void __throw_bad_function_call() { while(1); }
}


#endif /* CPP_FUNCTIONAL_WRAPPER */
