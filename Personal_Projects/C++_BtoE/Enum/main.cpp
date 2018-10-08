#include <iostream>

using namespace std;

enum dayOfWeek
{
    Monday;
    Tuesday;
    Wednesday;
    Thursday;
    Friday;
    Saturday;
    Sunday;
}

string getDay(dayOfWeek);

int main()
{


    return 0;
}

string getDay(dayOfWeek day)
{
    switch(day)
    {
        case Monday:
            return "Monday";

        case Tuesday:
            return "Tueday";

        case Wednesday:
            return "Wednesday";

        case Thursday:
            return "Thursday";

        case Friday:
            return "Friday";

        case Saturday:
            return "Saturday";

        case Sunday:
            return "Sunday";

        default:
            return "Incorrect input";
    }
}
