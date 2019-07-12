#include <string.h>

#include "../cpp/alloc.hpp"
#include "../json/json.hpp"
#include "movie.hpp"


static char* _Strdup(const char* str)
{
	size_t len = strlen(str);
	char* result = new char[len + 1];
	memcpy(result, str, len + 1);
	return result;
}


Movie::Movie()
{
	imgLink = _Strdup("");
	title = _Strdup("");
	ytsId = 0;
	rating = 0.0;
	releaseYear = 0;
	uploadYear = 0;
}


Movie::Movie(const Movie& m)
{
	imgLink = _Strdup(m.imgLink);
	title = _Strdup(m.title);
	ytsId = m.ytsId;
	rating = m.rating;
	releaseYear = m.releaseYear;
	uploadYear = m.uploadYear;
}


Movie& Movie::operator=(const Movie& m)
{
	delete[] imgLink;
	delete[] title;
	imgLink = _Strdup(m.imgLink);
	title = _Strdup(m.title);
	ytsId = m.ytsId;
	rating = m.rating;
	releaseYear = m.releaseYear;
	uploadYear = m.uploadYear;
	return *this;
}


Movie::~Movie()
{
	delete[] imgLink;
	delete[] title;
}


Movie::Movie(const char* jsonData, size_t len)
{
	JSONObject movie(jsonData, len);
	JSONObject movieGenres = movie["genres"];
	const size_t nGenres = movieGenres.arraySize();

	imgLink = _Strdup(movie["medium_cover_image"].toString());
	for (size_t i=0; i<nGenres; ++i)
		genres.include(movieGenres[i].toString());
	title = _Strdup(movie["title_long"].toString());
	ytsId = movie["id"].toInt();
	rating = (float)movie["rating"].toDouble();
	releaseYear = movie["year"].toInt();
	uploadYear = movie["date_uploaded_unix"].toInt();
}


const char* Movie::getTitle()
{
	return title;
}


int Movie::getYtsId()
{
	return ytsId;
}


char* Movie::getJSONStr()
{
	/* TODO: Complete function */
	return nullptr;
}


int main()
{
	return 0;
}
