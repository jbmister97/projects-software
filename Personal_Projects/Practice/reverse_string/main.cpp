#include <iostream>
#include "string.h";

using namespace std;
string reverseStr(string);

int main()
{
    string s = "Hello";

    cout << "Before: " << s << endl;
    s = reverseStr(s);
    cout << "After: " << s << endl;

    return 0;
}

string reverseStr(string s) {
    string s_reversed;

    for(int i = s.length() - 1; i >= 0; i--) {
        s_reversed += s[i];
    }

    return s_reversed;
}
