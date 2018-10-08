#include <iostream>
#include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
    //cout << "Hello world!" << endl;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Looks like you could use some help!" << endl;
        }
    }


    uint8_t x = 5;
    // Add the + in front of variable with primitive data types to print
    // or it will print as the ASCII value.
    cout << +x << endl;

    return 0;
}
