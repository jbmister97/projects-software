#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string file = "test.txt";
    fstream myFileHandler;

    /*
    myFileHandler.open(file);

    if(myFileHandler.is_open())
    {
        cout << "Opened " << file << " successfully" << endl;
        myFileHandler << "Sending this text to the text file!";

        myFileHandler.close();
    }
    */

    /* Different modes
        ios::in
        ios::out
        ios::trunc      Truncate (truncates the file by cutting everything inside)
        ios::ate        At The End (sets a pointer at the end of the file. Both the in and out flags must be set with this mode)
        ios::app        Append (the content is added at the end of the file and it is not possible to remove or add something anywhere else other than the end. In flag does not need to be set for this mode
        ios::binary     Opens the file as a binary file
    */

    /* Default Mode (Flags)
        fstream - ios::in | ios::out
        ifstream - ios::in
        ofstream - ios::out
    */

    /* In the open() function, the second parameter can dictate which mode to open the file in.
    specifying ios::out will only enable the output flag and if the file does not already exist then
    it will create it. By default both ios::in and ios::out flags are enabled and a new file cannot
    be created */
    myFileHandler.open(file, ios::in);

    if(myFileHandler.is_open())
    {
        cout << "Opened " << file << " successfully" << endl;

        /* Bad State */
        myFileHandler << "Sample text\n";
        myFileHandler << "Sample text\n";
        if(myFileHandler.bad())
        {
            cout << "There was an error while working with the file" << endl;
            myFileHandler.clear(); // Clears the bad bit or else nothing else can be done with the file

        }

        /* Fail State */
        int buf;
        myFileHandler >> buf;
        if(myFileHandler.fail())
        {
            cout << "Failed to get information from file due to wrong data types" << endl;
            myFileHandler.clear();
        }

        /* End of File */
        string buffer;
        do
        {
            myFileHandler >> buffer;

            cout << buffer << endl;
        }while(!myFileHandler.eof()); // Prints line-by-line until the End Of File is reached

        /* Read State */
        cout << (myFileHandler.rdstate() ^ ifstream::eofbit) << endl;
        if((myFileHandler.rdstate() ^ ifstream::eofbit) == 0)
            {
                cout << "File has been read successfully" << endl;
                myFileHandler.clear();
            }
        cout << "File state: " << myFileHandler.rdstate() << endl;

        /* Good State */
        cout << "Good state: " << myFileHandler.good() << endl;

        myFileHandler.close();
    }

    /* Opening same file again in separate if statement just for organization for the lessons*/
    myFileHandler.open(file, ios::in | ios::binary);

    /* Seekg and Tellg */

    /*Flags
        ios::beg    (default)
        ios::end
        ios::current
    */
    if(myFileHandler.is_open())
    {
        string buffer;

        myFileHandler.seekg(0, ios::end);

        streampos sizeOfFile = myFileHandler.tellg();
        cout << "The size of the file is " << sizeOfFile << " bytes" << endl;

        myFileHandler.seekg(0, ios::beg); // reset pointer to beginning of the file

        do
        {
            myFileHandler.clear();
            myFileHandler >> buffer;

            cout << buffer << endl;
        }while(!myFileHandler.eof());

        myFileHandler.close();
    }

    /* Seekp and Tellp */
    myFileHandler.open(file, ios::out | ios::binary);

    if(myFileHandler.is_open())
    {
        string tmp = "test text Justin!";
        myFileHandler << tmp;
        cout << myFileHandler.tellp() << endl;

        myFileHandler.seekp(0, ios::beg);
        myFileHandler << "T"; // Change first letter to capital T

        /* getline, get, ignore character extraction*/

        char buffer[50];

        myFileHandler.getline(buffer, 50 , '\n'); // stops at \n by default and do not need to include it but can change it to another delimiter


    }
    return 0;
}
