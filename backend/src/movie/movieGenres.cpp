#include <string.h>

#include "movie.hpp"


Movie::Genre Movie::GenreSet::gCode(const char* gStr) const
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


const char* Movie::GenreSet::gStr(Genre gCode) const
{
	switch (gCode) {
	case Genre::Horror:
		return "Horror";
	case Genre::Action:
		return "Action";
	case Genre::Mystery:
		return "Mystery";
	case Genre::Drama:
		return "Drama";
	case Genre::SciFi:
		return "Sci-Fi";
	case Genre::Thriller:
		return "Thriller";
	case Genre::Romance:
		return "Romance";
	case Genre::Comedy:
		return "Comedy";
	case Genre::Adventure:
		return "Adventure";
	default:
		return "(Unregistered)";
	}
}


Movie::GenreSet::iterator::iterator(const GenreSet& gs) : gs(gs)
{ }


const char* Movie::GenreSet::iterator::operator*() const
{
	return gs.gStr(static_cast<Genre>(currentBit));
}


Movie::GenreSet::iterator& Movie::GenreSet::iterator::operator++()
{
	if (currentBit < 0)
		return *this;
	while (--currentBit >= 0 and not (gs.gBitfield & (1 << currentBit)));
	return *this;
}


bool Movie::GenreSet::iterator::operator!=(const iterator& it) const
{
	return currentBit != it.currentBit;
}


bool Movie::GenreSet::iterator::operator==(const iterator& it) const
{
	return currentBit == it.currentBit;
}


Movie::GenreSet::GenreSet() : gBitfield(0)
{ }


void Movie::GenreSet::include(Genre g)
{
	gBitfield |= (uint32_t)(1 << static_cast<int>(g));
}


void Movie::GenreSet::include(const char* gStr)
{
	include(gCode(gStr));
}


void Movie::GenreSet::remove(Genre g)
{
	gBitfield &= ~(uint32_t)(1 << static_cast<int>(g));
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


Movie::GenreSet::iterator Movie::GenreSet::begin() const
{
	iterator it(*this);
	it.currentBit = -1;
	for (int currentBit=31; currentBit>=0; --currentBit) {
		if (gBitfield & (1 << currentBit)) {
			it.currentBit = currentBit;
			break;
		}
	}
	return it;
}


Movie::GenreSet::iterator Movie::GenreSet::end() const
{
	iterator it(*this);
	it.currentBit = -1;
	return it;
}


#if 0
int main() {
	Movie::GenreSet gs;
	gs.include(Movie::Genre::Horror);
	gs.include(Movie::Genre::Mystery);
	gs.include(Movie::Genre::Thriller);
	printf("Added genres:");
	for (const char* gStr : gs)
		printf(" %s", gStr);
	printf("\n");
	return 0;
}
#endif
