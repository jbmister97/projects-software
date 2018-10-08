 #include <iostream>
 #include "point.h"

 using namespace std;

Point::Point(int x)
{
    cout << "Constuctor for Point has been invoked" << endl;
    this->x = x;
}

Point::~Point()
{
    cout << "Deconstructor for Point has been invoked" << endl;
}

void Point::setX(int x)
{
    this->x = x;
}

Point2D::Point2D(int x, int y) : Point(x)
{
    cout << "Constuctor for Point2D has been invoked" << endl;
    /* Only need to define y here. Send x to parent so it does not need to be
    redefine in this constructor */
    this->y = y;
}

Point2D::~Point2D()
{
    cout << "Deconstructor for Point2D has been invoked" << endl;
}

void Point2D::setY(int y)
{
    this->y = y;
}
void Point2D::setXY(int x, int y)
{
    setX(x);
    setY(y);
}
