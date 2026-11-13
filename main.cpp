// Winter'24
// Instructor: Diba Mirza
// Student name: Yuanna Wu
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

//bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> movies;
    movies.reserve(80000);
 
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    	    if(line.empty()) continue;
            if(parseLine(line, movieName, movieRating)){
            	movies.push_back(Movie{movieName, movieRating});
            }
    }

    movieFile.close();

    sort(movies.begin(), movies.end(), byName);

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            for(const Movie& m : movies){
	    	//cout << m.name << ", " << m.rating <<"\n";
	        cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
	    }
	    return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if(!line.empty() && line.back() == '\r'){
	    line.pop_back();
	}
	if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    //cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    //cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

    //return 0;
    struct BestHit{
	    string name;
	    double rating;
	    bool found;
    };
    vector<BestHit> best(prefixes.size(), BestHit{"", 0.0, false});

    vector<Movie> scratch;
    for(size_t p = 0; p <prefixes.size(); ++p){
    	const string& pref = prefixes[p];
	auto range = prefixRange(movies, pref);
	size_t lo = range.first, hi = range.second;

	if(lo == hi){
		cout << "No movies found with prefix " << pref << "\n";
		continue;
	}

	scratch.clear();
	scratch.assign(movies.begin() + lo, movies.begin() + hi);
	sort(scratch.begin(), scratch.end(), byRatingDescNameAsc);

	for(const Movie& m : scratch){
		cout << m.name << ", " << fixed << setprecision(1) << m.rating << "\n";
	}
	cout << "\n";
	best[p] = BestHit{scratch[0].name, scratch[0].rating, true};
    }

    for(size_t p = 0; p < prefixes.size(); ++p){
    	if(!best[p].found) continue;
	cout << "Best movie with prefix " << prefixes[p] << " is: " << best[p].name << " with rating " << fixed << setprecision(1) << best[p].rating << "\n";
    }
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/*bool parseLine(string &line, string &movieName, double &movieRating) {
    if(!line.empty() && line.back() == '\r') line.pop_back();
	
    int commaIndex = line.find_last_of(",");
    if(commaIndex < 0) return false;

    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (!movieName.empty() && movieName.front() == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}*/
