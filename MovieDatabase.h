#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase //stores up to 20k movies and lets user search for a movie based on movie's ID, director of the movie, an actor in the movie, or the genre
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    //MovieDatabase(const MovieDatabase &src);
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
  private:
    std::vector<std::string> alreadyOpened;
    std::vector<Movie*> m_movies;
    TreeMultimap<std::string, Movie*> m_tree_id;
};

#endif // MOVIEDATABASE_INCLUDED
