#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

class User
{
    private:
        int ID;             //ID # for each user
        static int counter; //Counter that increments for each new user

    public:
        User();             //Constructor
        ~User();            //Destructor
        int getID(){return ID;}

        /* Static method that is able to be used without referring to a specific instance */
        static int getCounter(){return counter;}
};


#endif // USER_H_INCLUDED
