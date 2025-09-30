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
void findMovies(vector<Movie> movies, string title)
{    
  for (Movie m : movies) {
    //
    // TODO
    // 
    // Right now we only show the movie if the title is
    // an exact match. We want to do a substring search,
    // i.e. output the movie if the given title appears
    // anywhere in m.getTitle(). We also want to perform
    // a case-insensitive search. Finally, if no movies
    // are found, output "no movies found...".
    // 
    // HINT: strings have a find() method that searches
    // for a substring. If found, returns the index in
    // the string array where the substring starts. If
    // not found, returns string::npos, which means "no
    // position found".
    // 

    
    
    if (m.getTitle() == title) {
      m.print();
      return;
    }

    size_t pos = m.getTitle().find(title);

    if (pos != string::npos){
      m.print();
      return;
    }

    string title2 = m.getTitle(); // make a modifiable copy
    transform(title2.begin(), title2.end(), title2.begin(), ::tolower);

   size_t pos2 = title2.find(title);
    if (pos2 != string::npos){
        m.print();
        return;
    }


  }
  
  cout << "no movies found..." << endl;
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
