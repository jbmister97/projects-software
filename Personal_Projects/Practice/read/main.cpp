#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1) {
        cout << "Error: No parameters given" << endl;
        return 1;
    }
    else if(argc > 3) {
        cout << "Error: Too many arguments" << endl;
        return 1;
    }

    string file = argv[1];
    string identifier;

    if(file == "-h") {
        cout << "Help Information" << endl;
        cout << "Format: ./read Arg1 Arg2" << endl;
        cout << "Arg1: Name of file to open" << endl;
        cout << "Arg2: Identifier used to print out lines that only have the identifier in it" << endl;

        return 1;
    }

    if(argc == 3) {
        identifier = argv[2];
    }

    ifstream inputFile;
    string output = "output.txt";
    ofstream outputFile(output);

    inputFile.open(file);

    if(inputFile.is_open()) {
        cout << "Successfully opened " << file << endl;
        string line;
        while(inputFile) {
            getline(inputFile, line);

            if(inputFile && argc == 3 && line.find(identifier) != string::npos) {
                outputFile << line << endl;
                cout << line << endl;
            }
            else if(inputFile && argc == 2) {
                cout << line << endl;
            }
        }
        inputFile.close();
    }
    else {
        cout << "Could not open " << file << endl;
    }


    return 0;
}
