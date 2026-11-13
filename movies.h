#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
#include <cstddef>

struct Movie{
	std::string name;
	double rating;
};

bool byName(const Movie& a, const Movie& b);

bool byRatingDescNameAsc(const Movie& a, const Movie& b);

#endif

