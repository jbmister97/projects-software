#include <iostream>
#include "point.h"

/* Learning inheritance between classes */

using namespace std;

void operationOnPoints();

int main()
{
    operationOnPoints();
    cout << "Hello world!" << endl;
    return 0;
}

void operationOnPoints()
{
    Point2D p1;

    p1.setX(10);
    p1.setY(20);

    cout << "X: " << p1.getX() << endl;
    cout << "Y: " << p1.getY() << endl;

    p1.setXY(30,40);

    cout << "X: " << p1.getX() << endl;
    cout << "Y: " << p1.getY() << endl;
}
