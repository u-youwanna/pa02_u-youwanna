#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include "movies.h"

bool parseLine(std::string &line, std::string &movieName, double &movieRating);

std::pair<std::size_t, std::size_t>
prefixRange(const std::vector<Movie>& sortedByName, const std::string& prefix);

#endif
