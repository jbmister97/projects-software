#include "people.h"

void personalData::setAge(int age)
{
    if(age < 0)
    {
        cout << "Age cannot be negative" << endl;
        this->age = 0;
        return;
    }
    this->age = age;
}

personalData::personalData()
{
    static int i = 0;
    cout << "This constuctor has been invoked " << ++i << " times" << endl;
    age = 10;

    p = new int[5]; // dynamically allocate memory (Remember to free it!)
}

personalData::personalData(short age)
{
    this->age = age;
    cout << "New age is: "<< this->age << endl;
}

personalData::~personalData()
{
    static int i = 0;
    cout << "This destructor has been invoked " << ++i << " times" << endl;

    delete [] p; // free dynamically allocated memory
}
