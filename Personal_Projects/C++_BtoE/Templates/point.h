#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>

 using namespace std;

template<typename T2>
class Point //base, parent, superclass
{
    /* Protected allows use in derived classes. Private will not */
    protected:
        T2 x;

    public:
        /* Adding a default value for constuctor will allow an instance to be made
        without having to pass an argument */
        Point(T2 = 0);
        virtual ~Point();
        T2 getX();
        void setX(T2);
};

template<typename T2>
Point<T2>::Point(T2 x)
{
    cout << "Constuctor for Point has been invoked" << endl;
    this->x = x;
}

template<typename T2>
Point<T2>::~Point()
{
    cout << "Deconstructor for Point has been invoked" << endl;
}

template<typename T2>
void Point<T2>::setX(T2 x)
{
    this->x = x;
}

template<typename T2>
T2 Point<T2>::getX()
{
    return this->x;
}

/* This kind of template will use this version of the getX() method when
a Point defined with <double> type uses getX() */
template<>
double Point<double>::getX()
{
    cout << "Point<double> was created so using different getX()" << endl;
    return this->x;
}

/* It is not possible to use pointers so this template is made to notify
the user */
template<typename K>
class Point<K*>
{
    public:
        Point(K a = 0) {cout << "Cannot use pointers here"}
}

template<typename T2>
class Point2D : public Point<T2> //derived, child. subclass
{
    // This class inherits the methods and variables from the parent(except the constructor and destructor) /
    T2 y;

    public:
        //Xcoordinate already defined in parent class so only need to work it Y coordinate /
        Point2D(T2 = 0, T2 = 0);
        virtual ~Point2D();
        T2 getY() {return y;}
        void setY(T2);
        void setXY(T2, T2);
        // Adding this operator will allow the addition of two instances of this class /
        Point2D operator+(Point2D);
};

template<typename T2>
Point2D<T2>::Point2D(T2 x, T2 y) : Point<T2>(x)
{
    cout << "Constuctor for Point2D has been invoked" << endl;
    // Only need to define y here. Send x to parent so it does not need to be
    //redefine in this constructor /
    this->y = y;
}

template<typename T2>
Point2D<T2>::~Point2D()
{
    cout << "Deconstructor for Point2D has been invoked" << endl;
}

template<typename T2>
void Point2D<T2>::setY(T2 y)
{
    this->y = y;
}
template<typename T2>
void Point2D<T2>::setXY(T2 x, T2 y)
{
    setX(x);
    setY(y);
}

template<typename T2>
Point2D<T2> Point2D<T2>::operator+(Point2D obj)
{
    Point2D tmp;

    tmp.setX(this->getX() + obj.getX());
    tmp.setY(this->getY() + obj.getY());

    return tmp;
}

/* Adding a template like this will override the Point class above if
a <char> type is specified */
template<>
class Point<char>
{
    public:
        Point(char a = 0) {cout << "Point<char> constructor was invoked" << endl;}
};

/*
class Point3D : public Point2D<T2>
{

};
*/

#endif // POINT_H_INCLUDED
