/* Learning Classes */
#include <iostream>
#include "people.h"

using namespace std;

void test()
{
    personalData person[5];
}

void test2()
{
    /* dynamically allocating memory for a class like this only
    invokes the constructor and NOT the destructor */
    personalData *pointer = new personalData[5];

    /* Freeing the memory also invokes the destructor */
    delete [] pointer;
}

int main()
{

    personalData person;

    /* Passing an argument will override the constructor method */
    personalData person2(20);

    person.setAge(-25);
    short age = person.getAge();

    cout << "Age is: " << age << endl;


    //test();
    //test2();

    return 0;
}
