#include <string.h>

#include "movie.hpp"


Movie::Genre Movie::GenreSet::gCode(const char* gStr)
{
	if (strcmp(gStr, "Horror") == 0)
		return Genre::Horror;
	else if (strcmp(gStr, "Action") == 0)
		return Genre::Action;
	else if (strcmp(gStr, "Mystery") == 0)
		return Genre::Mystery;
	else if (strcmp(gStr, "Drama") == 0)
		return Genre::Drama;
	else if (strcmp(gStr, "Sci-Fi") == 0)
		return Genre::SciFi;
	else if (strcmp(gStr, "Thriller") == 0)
		return Genre::Thriller;
	else if (strcmp(gStr, "Romance") == 0)
		return Genre::Romance;
	else if (strcmp(gStr, "Comedy") == 0)
		return Genre::Comedy;
	else if (strcmp(gStr, "Adventure") == 0)
		return Genre::Adventure;
	else
		return Genre::Unregistered;
}


Movie::GenreSet::GenreSet() : gBitfield(0)
{ }


void Movie::GenreSet::include(Genre g)
{
	gBitfield |= (uint32_t)(1 << (int)g);
}


void Movie::GenreSet::include(const char* gStr)
{
	include(gCode(gStr));
}


void Movie::GenreSet::remove(Genre g)
{
	gBitfield &= ~(uint32_t)(1 << (int)g);
}


void Movie::GenreSet::remove(const char* gStr)
{
	remove(gCode(gStr));
}


bool Movie::GenreSet::empty() const
{
	return gBitfield == 0;
}


bool Movie::GenreSet::matches(const Movie& m) const
{
	return gBitfield & m.genres.gBitfield;
}
