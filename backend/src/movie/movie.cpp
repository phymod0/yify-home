#include <string.h>

#include "../cpp_compat/alloc.hpp"
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


const char* Movie::getTitle() const
{
	return title;
}


int Movie::getYtsId() const
{
	return ytsId;
}


char* Movie::getJSONStrCopy() const
{
	JSONObject movieObj("{}");
	JSONObject genreObj("[]");
	movieObj.assign("id", ytsId);
	movieObj.assign("title", title);
	movieObj.assign("title_long", title);
	movieObj.assign("year", releaseYear);
	movieObj.assign("rating", (double)rating);
	for (const char* genreName : genres)
		genreObj.arrayAppend(genreName);
	movieObj.assign("genres", genreObj);
	movieObj.assign("medium_cover_image", imgLink);
	movieObj.assign("date_uploaded_unix", (int64_t)uploadYear);
	return movieObj.strCopy();
}


#if 0
int main()
{
	Movie m;
	char* str = m.getJSONStrCopy();
	printf("%s\n", str);
	delete[] str;
}
#endif
