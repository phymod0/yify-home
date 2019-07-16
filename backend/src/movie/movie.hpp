#ifndef MOVIE
#define MOVIE


#include <stdio.h>
#include <stdint.h>

#include "../cpp_compat/pair.hpp"
#include "../cpp_compat/string.hpp"


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
		Genre gCode(const char* gStr) const;
		const char* gStr(Genre gCode) const;
	public:
		class iterator {
			friend class GenreSet;
			int currentBit;
			const GenreSet& gs;
		public:
			iterator(const GenreSet& gs);
			const char* operator*() const;
			iterator& operator++();
			bool operator!=(const iterator& it) const;
			bool operator==(const iterator& it) const;
		};
		GenreSet();
		void include(Genre g);
		void include(const char* gStr);
		void include(const string& gStr);
		void remove(Genre g);
		void remove(const char* gStr);
		void remove(const string& gStr);
		bool empty() const;
		bool matches(const Movie& m) const;
		iterator begin() const;
		iterator end() const;
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
		int operator()(const Movie& m1, const Movie& m2) const;
		int compare(const Movie& m1, const Movie& m2) const;
	private:
		priority priorities[3];
	};

	Movie();
	Movie(const char* jsonData, size_t len);
	string getTitle() const;
	int getYtsId() const;
	string serialize() const;

private:
	string imgLink, title;
	int ytsId;
	GenreSet genres;
	float rating;
	int releaseYear, uploadYear;
};


#endif /* MOVIE */
