/*main.cpp*/

/**
 * @brief Program to lookup Movie information from a database.
 *
 * Program to read movies from a database, and then
 * allows the user to search for movies and output
 * related information.
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
#include <algorithm>
#include <cctype>


#include "movie.h"
#include "sqlite_modern_cpp.h"

using namespace std;
using namespace sqlite;


/**
  * @brief Reads movies from database into a vector.
  *
  * @param db_name File name of SQLite database file.
  * @return vector of Movie objects.
  */
vector<Movie> getMovies(string db_name)
{
  vector<Movie> movies;

  //
  // Open the MovieLens database and retrive the first 1000 movies:
  //
  database db(db_name);

  string sql = "SELECT Movie_ID FROM Movies ORDER BY Movie_ID LIMIT 1000;";

  //
  // Loop to execute the query step by step, getting each movie:
  //
  auto results = db << sql;

  int count = 0;

  //
  // for each movie id in the result set:
  //
  for (auto row : results) {
    int id;

    row >> id;

    // create movie and push into vector:
    Movie m(db, id);
    movies.push_back(m);

    // show some input progress:
    count++;
    if (count % 100 == 0) {
      cout << ".";
      cout.flush();
    }
  }

  cout << endl;
  cout << endl;

  return movies;
}


/**
  * @brief Searches for movies that contain given title, outputs movie data.
  *
  * @param movies Vector of Movie objects.
  * @param title Movie title (partial or complete) to search for
  * @return nothing.
  */
void findMovies(vector<Movie> movies, string title) {
    int truecount = 0;

    transform(title.begin(), title.end(), title.begin(), ::tolower);

    for (Movie m : movies) {
        string title2 = m.getTitle();
        transform(title2.begin(), title2.end(), title2.begin(), ::tolower);

        if (title2.find(title) != string::npos) {
            m.print();
            truecount++;
        }
    }

    if (truecount == 0) {
        cout << "no movies found..." << endl;
    }

    return;
}



/**
  * @brief required main program function.
  *
  * @return 0 (success).
  */
int main()
{
  vector<Movie> movies;

  cout << "** MovieLens **" << endl;
  cout << endl;

  cout << "Reading movies";
  cout.flush();

  movies = getMovies("movielens.db");
  cout << "# of movies: " << movies.size() << endl;

  //
  // let the user search for movies:
  //
  string title;

  cout << endl;
  cout << "Enter movie title (all or partial, or '#' to exit)>" << endl;

  getline(cin, title);  // use getline because input could be multiple words:

  //
  // Lookup movies for the user until they enter # to stop:
  //
  while (title != "#") {

    findMovies(movies, title);

    cout << endl;
    cout << "Enter movie title (all or partial, or '#' to exit)>" << endl;

    getline(cin, title);  // use getline because input could be multiple words:
  }

  //
  // done:
  //
  cout << endl;
  cout << "** done **" << endl;

  return 0;
}
