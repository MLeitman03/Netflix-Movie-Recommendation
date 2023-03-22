#include "UserDatabase.h"
//#include "User.h"
#include "treemm.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{

}

UserDatabase::~UserDatabase()
{
    while (!m_users.empty())
    {
        delete m_users.back();
        m_users.pop_back();
    }
}

bool UserDatabase::load(const string& filename)
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
    string name = "";
    string email = "";
    int size = -99;
    std::vector<std::string> movie_history;
    
    string line;
    while(getline(file, line))
    {
        if (line.empty())
            continue;
        if (count == 0)
        {
            name = line;
            count++;
        }
        else if (count == 1)
        {
            email = line;
            count++;
        }
        else if (count == 2)
        {
            size = stoi(line);
            count++;
        }
        else if (!line.empty())
        {
            movie_history.push_back(line);
            count++;
        }
        if (count == 3+size)
        {
            User* n = new User(name, email, movie_history);
            m_users.push_back(n);
            m_tree.insert(email, n);
            count = 0;
            name = "";
            email = "";
            size = -99;
            movie_history.clear();
        }
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (m_tree.find(email).is_valid())
        return m_tree.find(email).get_value();
    else
        return nullptr;
}

