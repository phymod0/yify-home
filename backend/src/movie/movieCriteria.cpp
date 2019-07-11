#include <float.h>
#include <limits.h>

#include "movie.hpp"


Movie::Criteria::Criteria()
{
	minRating = FLT_MIN;
	maxRating = FLT_MAX;
	minReleaseYear = INT_MIN;
	maxReleaseYear = INT_MAX;
	minUploadYear = INT_MIN;
	maxUploadYear = INT_MAX;
}


void Movie::Criteria::allowGenre(Movie::Genre g)
{
	genres.include(g);
	blacklist.remove(g);
}


void Movie::Criteria::blacklistGenre(Movie::Genre g)
{
	genres.remove(g);
	blacklist.include(g);
}


void Movie::Criteria::setMinRating(float rating)
{
	minRating = rating;
}


void Movie::Criteria::setMaxRating(float rating)
{
	maxRating = rating;
}


void Movie::Criteria::setMinReleaseYear(int year)
{
	minReleaseYear = year;
}


void Movie::Criteria::setMaxReleaseYear(int year)
{
	maxReleaseYear = year;
}


void Movie::Criteria::setMinUploadYear(int year)
{
	minUploadYear = year;
}


void Movie::Criteria::setMaxUploadYear(int year)
{
	maxUploadYear = year;
}


bool Movie::Criteria::contains(const Movie& m) const
{
	return (genres.empty() or genres.matches(m))
		and not blacklist.matches(m)
		and m.rating >= minRating
		and m.rating <= maxRating
		and m.releaseYear >= minReleaseYear
		and m.releaseYear <= maxReleaseYear
		and m.uploadYear >= minUploadYear
		and m.uploadYear <= maxUploadYear;
}
