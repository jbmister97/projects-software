#include <iostream>
#include "point.h"

/* Learning function and class templates */

using namespace std;

void operationOnPoints();

/* A template like this will allow functions to like "add" to have
two different types like a double and integer without having to make
multiple functions for each combination of the two types */
template<typename T, typename T2>
T add(T var1, T2 var2)
{
    return var1 + var2;
}

/* This tempalte method can be used in the event that a function does not
accept classes and there is no access to the header files to change the class.
In this case the add template above does not accept classes by default */
/*
template<>
Point2D add(Point2D var1, Point2D var2)
{
    Point2D tmp;

    tmp.setX(var1.getX() + var2.getX());
    tmp.setY(var1.getY() + var2.getY());

    cout << tmp.getX() << endl;
    cout << tmp.getY() << endl;
}
*/
typedef Point<int> PointInt;

int main()
{
    operationOnPoints();
    //cout << add<double, double>(4, 5.6) << endl;
    return 0;
}

void operationOnPoints()
{
    /*
    Point2D p1(10, 67);
    Point2D p2(50, 3);

    Point2D p3 = add(p1,p2);

    cout << p3.getX() << endl;
    cout << p3.getY() << endl;
    */

    PointInt a(5);
    Point<double> b(5.7);

    Point2D<int> c(7, 6);
    Point2D<double> d(6.9, 5.5);

    cout << a.getX() << endl;
    cout << b.getX() << endl;

    cout << c.getX() << endl;
    cout << c.getY() << endl;
    cout << d.getX() << endl;
    cout << d.getY() << endl;

    Point<char> e(6);
}
