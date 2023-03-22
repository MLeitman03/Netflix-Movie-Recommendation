#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_db = &user_database;
    m_movie_db = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<string> movies_names = m_user_db->get_user_from_email(user_email)->get_watch_history();
    unordered_map<string,int> hashmap;
    
    vector<string> watched_movies_ids;
    
    for (int i =0;  i < movies_names.size(); i++)
    {
        Movie* m = m_movie_db->get_movie_from_id(movies_names[i]);
        watched_movies_ids.push_back(m->get_id());
        
        vector<string> temp_dir = m->get_directors();
        for (int j = 0; j < temp_dir.size(); j++)
        {
            vector<Movie*> movies_with_dir = m_movie_db->get_movies_with_director(temp_dir[j]);
            
            for (int n = 0; n < movies_with_dir.size(); n++)
            {

                string id = movies_with_dir[n]->get_id();
                
                if (hashmap.find(id) == hashmap.end())
                    hashmap.insert(make_pair(movies_with_dir[n]->get_id(), 20));
                else
                    hashmap[id]+=20;
            }
        }
        
        vector<string> temp_act = m->get_actors();
        for (int j = 0; j < temp_act.size(); j++)
        {
            vector<Movie*> movies_with_act = m_movie_db->get_movies_with_actor(temp_act[j]);
            
            for (int n = 0; n < movies_with_act.size(); n++)
            {
                string id = movies_with_act[n]->get_id();
                
                if (hashmap.find(id) == hashmap.end())
                    hashmap.insert(make_pair(movies_with_act[n]->get_id(), 30));
                else
                    hashmap[id]+=30;
            }
        }
        
        vector<string> temp_gen = m->get_genres();
        for (int j = 0; j < temp_gen.size(); j++)
        {
            vector<Movie*> movies_with_gen = m_movie_db->get_movies_with_genre(temp_gen[j]);
            
            for (int n = 0; n < movies_with_gen.size(); n++)
            {
                string id = movies_with_gen[n]->get_id();
                
                if (hashmap.find(id) == hashmap.end())
                    hashmap.insert(make_pair(movies_with_gen[n]->get_id(), 1));
                else
                    hashmap[id]+=1;
            }
        }
    }
        vector<MovieAndRank> m_and_r;
    
        unordered_map<string, int>::iterator it;
        it = hashmap.begin();
        while (it != hashmap.end())
        {
            string movie_id = it->first;
            int compat_score = it->second;
    
            MovieAndRank m_r = MovieAndRank(movie_id, compat_score);
            m_and_r.push_back(m_r);
            it++;
        }
    
        sort(m_and_r.begin(), m_and_r.end(), [this](const MovieAndRank& lhs, const MovieAndRank& rhs)
        {
            if (lhs.compatibility_score > rhs.compatibility_score)
                return true;
            else if (lhs.compatibility_score < rhs.compatibility_score)
                return false;
            else
            {
                if (m_movie_db->get_movie_from_id(lhs.movie_id)->get_rating() > m_movie_db->get_movie_from_id(rhs.movie_id)->get_rating())
                    return true;
                else
                    return false;
            }
        });
    
        vector<MovieAndRank>::iterator it2;
    
        for (int i =0; i < watched_movies_ids.size(); i++)
        {
            it2 = m_and_r.begin();
            while (it2 !=  m_and_r.end())
            {
                if (watched_movies_ids[i] == (*it2).movie_id)
                    m_and_r.erase(it2);
                it2++;
            }
        }
    
        vector<MovieAndRank> recommended_movies_vector;
    
        for (int j = 0; j < movie_count; j++)
            recommended_movies_vector.push_back(m_and_r[j]);
    
    return recommended_movies_vector;
}


//loop over all user history, loop over actors, directors,  genres

//use a set, one set for actors, one for  directors and one for genres
//unqiue actors, directors, and genres associated with that user
//iterate over each set and find the mataching movies using the get movie from movie database
//store lsit of movies into a hashmap where we associate each movie ID with a score
//as you get movies from each set, create new entries in hashmap or update the compatability score


