#include <string.h>

#include "../cpp_compat/alloc.hpp"
#include "../cpp_compat/string.hpp"
#include "../json/json.hpp"
#include "movie.hpp"


Movie::Movie()
{
	imgLink = string();
	title = string();
	ytsId = 0;
	rating = 0.0;
	releaseYear = 0;
	uploadYear = 0;
}


Movie::Movie(const char* jsonData, size_t len)
{
	JSONObject movie(jsonData, len);
	JSONObject movieGenres = movie["genres"];
	const size_t nGenres = movieGenres.arraySize();

	imgLink = movie["medium_cover_image"].toString();
	for (size_t i=0; i<nGenres; ++i)
		genres.include(movieGenres[i].toString());
	title = movie["title_long"].toString();
	ytsId = movie["id"].toInt();
	rating = (float)movie["rating"].toDouble();
	releaseYear = movie["year"].toInt();
	uploadYear = movie["date_uploaded_unix"].toInt();
}


string Movie::getTitle() const
{
	return title;
}


int Movie::getYtsId() const
{
	return ytsId;
}


string Movie::serialize() const
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
	return movieObj.serialize();
}


#if 0
int main()
{
	Movie m;
	string str = m.serialize();
	printf("%s\n", str.c_str());
}
#endif
