/*movie.h*/

/**
 * @brief Declaration of Movie class.
 *
 * Declaration of Movie members for class Movie, which
 * models one Movie object.
 *
 * Initial template:
 *   Prof. Hummel
 *   Northwestern University
 *
 * @note Modified by ...
 * @note Northwestern University
 * @note Database access using "SqliteModernCPP": https://github.com/SqliteModernCpp/sqlite_modern_cpp
 */
 
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "sqlite_modern_cpp.h"

using namespace std;
using namespace sqlite;

class Movie
{
private:
  int Movie_ID;
  string Title;
  double Revenue;
  vector<int> Ratings;
  vector<string> Genres;

public:
  // constructor
  Movie(database& db, int movie_id);

  // methods:
  int    getMovieID();
  string getTitle();
  double getRevenue();

  int    getNumRatings();
  double getAverageRating();
  void   print();
};
