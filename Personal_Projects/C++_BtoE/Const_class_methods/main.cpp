#include <iostream>
#include "position.h"

using namespace std;

int main()
{
    Position dog(10, 50);

    dog.getPosition();
    dog.setPosition(40,60);
    cout << endl;
    dog.getPosition();
    cout << endl;

    /* House must be constant since it cannot move */
    const Position house (200,300);

    /* Only the getPosition function has been made so it can be used when
    the object is defined as a constant */
    house.getPosition();
    //house.setPosition(40,60);
    //house.getPosition();

    return 0;
}
