#include <iostream>
#include <string>

using namespace std;

void reverseStr(string &s) {
    string s_reversed;

    int n = s.length();
    int i = 0, j = n - 1;
    char temp;

    while(i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }

    /*
    for(int i = s.length() - 1; i >= 0; i--) {
        s_reversed += s[i];
    }

    return s_reversed;
    */
}

int main()
{
    string s = "Hello";

    cout << "Before: " << s << endl;
    //s = reverseStr(s);
    reverseStr(s);
    cout << "After: " << s << endl;

    return 0;
}


