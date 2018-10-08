#ifndef CLASSES_INCLUDED
#define CLASSES_INCLUDED

#include <iostream>

using namespace std;

class personalData
{
    private:
        string name;
        short age;
        int *p;

    public:
        personalData();
        personalData(short);
        ~personalData();
        void setAge(int);
        short getAge(void){return age;}

};


#endif // CLASSES_INCLUDED
