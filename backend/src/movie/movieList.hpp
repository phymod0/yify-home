#ifndef MOVIELIST
#define MOVIELIST


class MovieList {
	struct MovieListItem {
		Movie m;
		MovieListItem* next;
		MovieListItem(const Movie& m);
	};
	MovieListItem* head;
	size_t nItems;
public:
	MovieList();
	MovieList(const MovieList& list);
	MovieList& operator=(const MovieList& list);
	MovieList(const char* jsonFilePath);
	~MovieList();
	MovieList& operator+=(const Movie& m);
	MovieList& operator+=(const MovieList& list);
	void addMovie(const Movie& m);
	void sort(const Movie::Order& order);
	size_t size();
};


#endif /* MOVIELIST */
