#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

MovieDatabase::MovieDatabase()
{
}

MovieDatabase::~MovieDatabase()
{
    if (m_movies.empty())
        return;
    
    for (int i =0; i < m_movies.size(); i++)
    {
        delete m_movies[i];
    }

}


bool MovieDatabase::load(const string& filename)
{
    fstream file;
    
    for (int i =0; i < alreadyOpened.size(); i++)
    {
        if (alreadyOpened[i] == filename)
            return false;
    }
    file.open(filename, ios::in);
    alreadyOpened.push_back(filename);
    
    int count = 0;
    string movie_id = "";
    string movie_name = "";
    string movie_year = "";
    std::vector<std::string> directors;
    std::vector<std::string> actors;
    std::vector<std::string> genres;
    int rating = 0;
    
    string director;
    string actor;
    string genre;
    
    string line;
    while(getline(file, line))
    {
        if (count == 0 && !line.empty())
        {
            movie_id = line;
            count++;
        }
        else if (count == 1)
        {
            movie_name = line;
            for (int i = 0; i < movie_name.size(); i++)
                movie_name[i] = tolower(movie_name[i]);
            count++;
        }
        else if (count == 2)
        {
            movie_year = line;
            count++;
        }
        else if (count == 3)
        {
            stringstream linestream(line);
            
            while (getline(linestream,  director, ','))
            {
                for (int i = 0; i < director.size(); i++)
                    director[i] = tolower(director[i]);
                directors.push_back(director);
            }
            count++;
        }
        else if (count == 4)
        {
            stringstream linestream(line);
            
            while (getline(linestream, actor, ','))
            {
                for (int i = 0; i < actor.size(); i++)
                    actor[i] = tolower(actor[i]);
                actors.push_back(actor);
            }
            count++;
        }
        else if (count == 5)
        {
            stringstream linestream(line);
            
            while (getline(linestream, genre, ','))
            {
                for (int i = 0; i < genre.size(); i++)
                    genre[i] = tolower(genre[i]);
                genres.push_back(genre);
            }
            count++;
        }
        else if (count == 6)
        {
            rating = stof(line);
            count++;
            
            Movie* m = new Movie(movie_id, movie_name, movie_year, directors, actors, genres, rating);
            m_movies.push_back(m);
            m_tree_id.insert(movie_id, m);
            
            count = 0;
            movie_id = "";
            movie_name = "";
            movie_year = "";
            directors.clear();
            actors.clear();
            genres.clear();
            rating = 0;
        }
        else
            continue;
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    if (m_tree_id.find(id).is_valid())
        return m_tree_id.find(id).get_value();
    else
        return nullptr; //is  this right
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    std::vector<Movie*> vector_to_return;
    
    for (int i = 0; i < m_movies.size(); i++)
    {
        std::vector<std::string> temp = m_movies[i]->get_directors();
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == director)
                vector_to_return.push_back(m_movies[i]);
        }
    }
    return vector_to_return;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    std::vector<Movie*> vector_to_return;
    
    for (int i = 0; i < m_movies.size(); i++)
    {
        std::vector<std::string> temp = m_movies[i]->get_actors();
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == actor)
                vector_to_return.push_back(m_movies[i]);
        }
    }
    return vector_to_return;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    std::vector<Movie*> vector_to_return;
    
    for (int i = 0; i < m_movies.size(); i++)
    {
        std::vector<std::string> temp = m_movies[i]->get_genres();
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == genre) {
                vector_to_return.push_back(m_movies[i]);
            }
        }
    }
    return vector_to_return;
}
