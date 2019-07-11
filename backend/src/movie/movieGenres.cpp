#include "movie.hpp"


Movie::GenreSet::GenreSet() : gBitfield(0)
{ }


void Movie::GenreSet::include(Genre g)
{
	gBitfield |= (uint32_t)(1 << (int)g);
}


void Movie::GenreSet::remove(Genre g)
{
	gBitfield &= ~(uint32_t)(1 << (int)g);
}


bool Movie::GenreSet::empty() const
{
	return gBitfield == 0;
}


bool Movie::GenreSet::matches(const Movie& m) const
{
	return gBitfield & m.genres.gBitfield;
}
