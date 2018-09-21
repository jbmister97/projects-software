#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point //base, parent, superclass
{
    /* Protected allows use in derived classes. Private will not */
    protected:
        int x;

    public:
        /* Adding a default value for constuctor will allow an instance to be made
        without having to pass an argument */
        Point(int = 0);
        ~Point();
        int getX() {return x;};
        void setX(int);
};

class Point2D : public Point //derived, child. subclass
{
    /* This class inherits the methods and variables from the parent(except the constructor and destructor) */
    int y;

    public:
        /* X coordinate already defined in parent class so only need to work it Y coordinate */
        Point2D(int = 0, int = 0);
        ~Point2D();
        int getY() {return y;}
        void setY(int);
        void setXY(int, int);

};

class Point3D : public Point2D
{

};

#endif // POINT_H_INCLUDED
