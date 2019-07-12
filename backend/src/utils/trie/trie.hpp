#ifndef TRIE_CPP_WRAPPER
#define TRIE_CPP_WRAPPER


#include <stddef.h>

#include "../cpp/pair.hpp"
#include "trie_c/src/trie.h"


/*
 * REQUIREMENTS FOR T:
 *	- Default constructor [ T() ]
 *	- Copy constructor [ T(const T&) ]
 *	- Overloaded assignment [T& operator=(const T&)] for trie["str"] = val
 *	- Destructor [~T()]
 */


template<typename T>
class subtrie {
	Trie* t;
	const char* prefix;
	size_t maxKeylen;
public:
	class iterator {
		friend class subtrie;
		TrieIterator* iter;
	public:
		~iterator();
		iterator& operator++();
		pair<const char*, T&> operator*() const;
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;
	};
	subtrie(Trie*, const char*, size_t);
	~subtrie();
	iterator begin();
	iterator end();
};


template<typename T>
class trie {
	Trie* t;
public:
	class iterator {
		friend class trie;
		TrieIterator* iter;
	public:
		~iterator();
		iterator& operator++();
		pair<const char*, T&> operator*() const;
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;
	};
	trie();
	~trie();
	size_t maxKeylenAdded();
	void insert(const char* key, const T& value);
	void remove(const char* key);
	iterator find(const char* key);
	T& operator[](const char* key);
	iterator begin();
	iterator end();
	subtrie<T> getSubtrie(const char* prefix, size_t maxKeylen);
};


#endif /* TRIE_CPP_WRAPPER */
