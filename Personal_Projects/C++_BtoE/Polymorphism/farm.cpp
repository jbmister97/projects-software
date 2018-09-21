#include <iostream>
#include "farm.h"

using namespace std;

Animal::Animal()
{
    //voice = "Default value"; // Not needed if abstact value is used
}

Animal::~Animal()
{
    cout << "From the Animal base class" << endl;
}

Dog::Dog()
{
    sign = "D";
    voice = "Woof!";
}

Dog::~Dog()
{
    cout << "From the Dog sub-class" << endl;
}

Cat::Cat()
{
    sign = "C";
    voice = "Meow!";
}

Cat::~Cat()
{
    cout << "From the Cat sub-class" << endl;
}

Cow::Cow()
{
    sign = "CW";
    voice = "Moo!";
}

Cow::~Cow()
{
    cout << "From the Cow sub-class" << endl;
}
