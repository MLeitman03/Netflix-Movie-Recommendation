#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    m_name =  full_name;
    m_email = email;
    
    std::vector<string>::size_type size = watch_history.size();
    for (std::vector<string>::size_type i = 0; i < size; i++)
    {
        m_movies_watched.push_back(watch_history[i]);
    }
}

string User::get_full_name() const
{
    return m_name;
}

string User::get_email() const
{
    return m_email;
}

vector<string> User::get_watch_history() const
{
    return m_movies_watched;
}
