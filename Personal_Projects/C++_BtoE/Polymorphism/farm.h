#ifndef FARM_H_INCLUDED
#define FARM_H_INCLUDED

#include <iostream>

using namespace std;

class Animal
{
    protected:
        string voice;
    public:
        Animal();

        /* Virtual destructor is important for freeing up dynamically
        allocated memory in the event of mismatching inheritance
        (i.e. Animal *dog = new Dog; , after deleting this only the
        base-class destructor will be invoked and not the Dog sub-class destructor)*/
        virtual ~Animal();
        /* Virtual methods allow methods in derived classes to override it */
        //virtual string getVoice() {return voice;}

        /* Abstract value for default. Make this an abstract class */
        virtual string getVoice() = 0;

};

class Dog : public Animal
{
    private:
        string sign;
    public:
        Dog();
        ~Dog();
        string getVoice() {return voice + " " + sign;}
};

class Cat : public Animal
{
    private:
        string sign;
    public:
        Cat();
        ~Cat();
        string getVoice() {return voice + " " + sign;}
};

class Cow : public Animal
{
    private:
        string sign;
    public:
        Cow();
        ~Cow();
        string getVoice() {return voice + " " + sign;}
};

#endif // FARM_H_INCLUDED
