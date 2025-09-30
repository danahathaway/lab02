/*movie.cpp*/

/**
 * @brief Implementation of Movie class.
 *
 * Implementation of Movie member functions for class Movie, which
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
 
#include <iostream>
#include <string>
#include <vector>

#include "movie.h"
#include "sqlite_modern_cpp.h"

using namespace std;
using namespace sqlite;


/**
  * @brief constructor to initialize Movie object from database.
  *
  * @parame DB SQLite database object representing movie database.
  * @param Movie_ID ID (integer) of movie in database.
  * @return nothing.
  */
Movie::Movie(database& db, int movie_id)
  : Movie_ID(movie_id)
{
  //
  // First, let's retrieve the title and revenue from the database:
  //
  string sql = "SELECT Title, Revenue FROM Movies WHERE Movie_ID = ?;";

  auto results = db << sql << movie_id;

  for (auto row : results) {
    row >> this->Title >> this->Revenue;
    break; // there's only one row in the result:
  }

  //
  // Next, let's retreive any ratings for this movie and
  // store in the vector:
  //
  sql = "SELECT Rating FROM Ratings WHERE Movie_ID = ?;";

  auto results2 = db << sql << movie_id;

  for (auto row : results2) {

    int rating;

    row >> rating;

    this->Ratings.push_back(rating);
  }

  //
  // Finally, let's retrieve the genre(s) that this movie
  // falls into, and store in vector:
  //
  sql = R""""(
    SELECT Genre_Name
    FROM Genres
    JOIN Movie_Genres ON Genres.Genre_ID = Movie_Genres.Genre_ID
    WHERE Movie_ID = ?
    ORDER BY Genre_Name;
  )"""";

  auto results3 = db << sql << movie_id;

  for (auto row : results3) {

    string genre_name;

    row >> genre_name;

    this->Genres.push_back(genre_name);
  }

  return;
}


//
// getters:
//
int Movie::getMovieID()
{
  return (this->Movie_ID);
}
string Movie::getTitle()
{

  return (this->Title);

}
double Movie::getRevenue()
{

  return (this->Revenue);

}

//
// getNumRatings:
//
int Movie::getNumRatings()
{
  return (this->Ratings.size());
}


//
// getAverageRating:
//
double Movie::getAverageRating()
{
  //
  // TODO
  if (this->Ratings.size() == 0) {
    return 0.0;
  }

  double sum = 0.0;
  for (const auto& rating : this->Ratings) {
    sum += rating;
  }
  return sum / this->Ratings.size();
}


//
// print:
//
void Movie::print()
{
  cout << this->Movie_ID << ": " << "'" << this->Title << "'" << endl;
  cout << " Rating info: " << "# of ratings=" << this->getNumRatings()
       << ", avg rating=" << this->getAverageRating() << endl;

  cout << " Genres: ";

  //
  // TODO
  //
  // print out the genres vector with ", " between each genre.
  // Example: Genres: Action, Science Fiction, Thriller
  //

  for (size_t i = 0; i < this->Genres.size(); i++) {
    cout << this->Genres[i];
    if (i < this->Genres.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;

  // HINT: use an index-based for loop, not foreach, and use
  // index to decide if you should output ", " or not.
  //

  return;
}
