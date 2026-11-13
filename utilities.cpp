#include "utilities.h"
#include <algorithm>
#include <utility>

bool parseLine(std::string &line, std::string &movieName, double &movieRating){
	if(!line.empty() && line.back() == '\r'){
		line.pop_back();
	}
	int commaIndex = (int)line.find_last_of(",");
	if(commaIndex < 0) return false;
	movieName = line.substr(0, commaIndex);
	movieRating = std::stod(line.substr(commaIndex + 1));

	if(!movieName.empty() && movieName.front() == '"'){
		movieName = movieName.substr(1, movieName.length() - 2);
	}
	return true;
}

std::pair<std::size_t, std::size_t>
prefixRange(const std::vector<Movie>& v, const std::string& prefix){
	auto lo = std::lower_bound(v.begin(), v.end(), prefix, [](const Movie& m, const std::string& p){ return m.name < p; });
	std::size_t start = (std::size_t)(lo - v.begin());

	std::size_t plen = prefix.size();
        std::size_t i = start;
	const std::size_t n = v.size();
	while(i < n){
		const std::string& nm = v[i].name;
		if(nm.size() < plen) break;
		bool match = true;
		for(std::size_t j = 0; j < plen; ++j){
			if(nm[j] != prefix[j]){
				match = false;
				break;
			}
		}
		if(!match) break;
		++i;
	}
	return {start, i};
}
