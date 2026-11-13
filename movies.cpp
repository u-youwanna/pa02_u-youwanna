#include "movies.h"

bool byName(const Movie& a, const Movie& b){
	return a.name < b.name;
}

bool byRatingDescNameAsc(const Movie& a, const Movie& b){
	if(a.rating != b.rating){
		return a.rating > b.rating;
	}
	return a.name < b.name;
}
