#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push , 1) //Pushes a directive onto the stack that will remove the padding added to the struct below

struct Person {
    char name[50]; //Do not use strings in a structure that will be written to a file. It will only write the pointer and not the string
    int age;
    double height;
};

#pragma pack(pop) //Add padding back

int main()
{
    /* Writing to text file */
    ofstream outFile;
    string file = "test.txt";

    outFile.open(file);

    if(outFile.is_open()) {
        cout << "Successfully opened " << file << endl;
        outFile << "Hello!" << endl;
        outFile << "I am a test file!" << endl;
        outFile << 123 << endl;
        outFile.close();
    }
    else {
        cout << "Could not open " << file << endl;
    }

    /* Reading from text file */
    ifstream inFile;

    inFile.open(file);

    if(inFile.is_open()) {
        cout << "Successfully opened " << file << endl;
        string line;

        //while(!inFile.eof()) {
        while(inFile) { //ifsteam has an overloaded operator where the file will return a false when reaching the end of the file
            getline(inFile, line);
            cout << line << endl;
        }

        inFile.close();
    }
    else {
        cout << "Could not open " << file << endl;
    }

    /* Parsing text from a file */
    ifstream input;
    string parse_file = "parse.txt";

    input.open(parse_file);

    if(!input.is_open()) {
        cout << "Could not open " << parse_file << endl;
        return 1;
    }

    cout << "Successfully opened " << parse_file << endl;

    while(input) {
        string line;

        getline(input, line, ':'); //getline allows a delimiter and will retrieved everything up until the colon
        int population;
        input >> population;

        //input.get(); //Discards the new line character at the end of each line
        input >> ws; //Only C++11

        if(!input) {
            break;
        }
        cout << line << " - " << population << endl;
    }

    /* Using fstream instead of ifstream or ofstream */
    fstream generalFile;
    string file2 = "test2.txt";

    generalFile.open(file2, ios::out);

    if(generalFile) {
        cout << "Successfully opened " << file2 << endl << endl;
        generalFile.close();
    }
    else {
        cout << "Could not open " << file2 << endl << endl;
    }

    /* Writing binary files */
    cout << sizeof(Person) << endl;
    Person someone = {"Justin", 54, 5.4};

    file = "binary.bin";
    ofstream binaryFile;

    binaryFile.open(file, ios::binary);

    if(binaryFile.is_open()) {
        cout << "Successfully opened " << file << endl;
        cout << "Writing to " << file << "..." << endl;
        binaryFile.write(reinterpret_cast<char *>(&someone), sizeof(Person));
        cout << "Finished" << endl << endl;
        binaryFile.close();
    }
    else {
        cout << "Could not open " << file << endl << endl;
    }

    /* Reading binary files */
    ifstream inputFile;
    Person newPerson = {};

    inputFile.open(file, ios::binary);

    if(inputFile.is_open()) {
        cout << "Succesffully opened " << file << endl;
        cout << "Reading from " << file << "..." << endl;
        inputFile.read(reinterpret_cast<char *>(&newPerson), sizeof(Person));

        cout << "Name: " << newPerson.name << endl;
        cout << "Age: " << newPerson.age << endl;
        cout << "Height: " << newPerson.height << endl;
        cout << "Finished" << endl;
        inputFile.close();
    }
    else {
        cout << "Could not open " << file << endl;
    }

    return 0;
}
