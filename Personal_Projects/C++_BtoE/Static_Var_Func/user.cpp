#include "user.h"

int User::counter = 0; // Initialize counter

User::User()
{
    counter++; // Increment counter for each new user
    ID = counter; // ID # is set so it is different from other users
}

User::~User()
{

}
