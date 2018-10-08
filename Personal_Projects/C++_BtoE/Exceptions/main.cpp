#include <iostream>

/* Learning exception handling */
using namespace std;

class DivisionByZeroException
{
    public:
        void getErrorMessage() {cout << "Error: Do not divide by zero" << endl;}
};

/* Adding the throw in same line as function name and arguments is good practice so
another programmer can obviously see something can be thrown in this function */
double division(double a, double b) throw (DivisionByZeroException)
{
    if(b == 0)
        throw DivisionByZeroException();
    return a / b;
}

int main()
{
    double result;

    try
    {
        result = division(10, 0);

        cout << "The result is " << result << endl;
    }
    /* This catch will catch an integer that is thrown */

    catch(DivisionByZeroException e)
    {
        e.getErrorMessage();
    }
    /* This catch will catch everything and not just the specified type in the argument */
    catch(...)
    {
        cout << "Other catches were not invoked" << endl;
    }

    return 0;
}
