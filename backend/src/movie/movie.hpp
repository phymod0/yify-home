#ifndef MOVIE
#define MOVIE


#include <stdio.h>
#include <stdint.h>

#include "../cpp/pair.hpp"


class Movie {
public:
	enum class Genre {
		Horror,
		Action,
		Mystery,
		Drama,
		SciFi,
		Thriller,
		Romance,
		Comedy,
		Adventure,
		Unregistered,
	};

	class GenreSet {
		uint32_t gBitfield;
		Genre gCode(const char* gStr);
	public:
		GenreSet();
		void include(Genre g);
		void include(const char* gStr);
		void remove(Genre g);
		void remove(const char* gStr);
		bool empty() const;
		bool matches(const Movie& m) const;
	};

	class Criteria {
		GenreSet genres, blacklist;
		float minRating, maxRating;
		int minReleaseYear, maxReleaseYear;
		int minUploadYear, maxUploadYear;
	public:
		Criteria();
		void allowGenre(Genre g);
		void blacklistGenre(Genre g);
		void setMinRating(float rating);
		void setMaxRating(float rating);
		void setMinReleaseYear(int year);
		void setMaxReleaseYear(int year);
		void setMinUploadYear(int year);
		void setMaxUploadYear(int year);
		bool contains(const Movie& m) const;
	};

	class Order {
	public:
		typedef enum {
			Rating,
			UploadYear,
			ReleaseYear,
		} Type;
		typedef enum {
			Ascending,
			Irrelevant,
			Descending,
		} Weight;
		typedef pair<Type,Weight> priority;
		Order();
		void prioritize(Type t, Weight w);
		void prioritize(const priority& p);
		int operator()(const Movie& m1, const Movie& m2);
		int compare(const Movie& m1, const Movie& m2);
	private:
		priority priorities[3];
	};

	Movie();
	Movie(const Movie& m);
	Movie& operator=(const Movie& m);
	~Movie();
	Movie(const char* jsonData, size_t len);
	const char* getTitle();
	int getYtsId();
	char* getJSONStr();

private:
	const char *imgLink, *title;
	int ytsId;
	GenreSet genres;
	float rating;
	int releaseYear, uploadYear;
};


#endif /* MOVIE */
