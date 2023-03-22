#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include "User.h"

//class User;

class UserDatabase //stores up to 100k user profiles and lets you search for a user based on email address
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
  private:
    std::vector<std::string> alreadyOpened;
    std::vector<User*> m_users;
    TreeMultimap<std::string, User*> m_tree;
};

#endif // USERDATABASE_INCLUDED
