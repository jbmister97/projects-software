#include <iostream>
#include "user.h"

using namespace std;

int main()
{
    User a;
    User b;

    cout << "User A: " << a.getID() << endl;
    cout << "User B: " << b.getID() << endl;
    cout << "Counter value: " << User::getCounter() << endl;


    return 0;
}
