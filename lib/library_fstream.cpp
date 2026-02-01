// Q: write a single file handling program in c++ to reading
// and writing data on a file.

// Include necessary header files
#include <fstream>
#include <iostream>
#include <string>

// Use the standard namespace
using namespace std;

int main()
{
    // Create an output file stream object
    ofstream fout;
    // Open a file named "NewFile.txt" for writing
    fout.open("NewFile.txt");

    // Check if the file opened successfully
    if (!fout) {
        // Print an error message if the file couldn't be
        // opened
        cerr << "Error opening file!" << endl;
        // Return 1 to indicate failure
        return 1;
    }

    // Declare a string variable to hold each line of text
    string line;
    // Initialize a counter to limit input to 5 lines
    int i = 0;

    // Prompt the user to enter 5 lines of text
    cout << "Enter 5 lines of text:" << endl;
    // Loop to read 5 lines of input from the user
    while (i < 5) {
        // Read a line of text from standard input
        getline(cin, line);
        // Write the line of text to the file
        fout << line << endl;
        // Increment the counter
        i += 1;
    }

    // Close the file after writing
    fout.close();

    // Print a success message
    cout << "Text successfully written to NewFile.txt"
         << endl;

    
    
    
    
    
    
    std::fstream file; //read & Write
    std::ifstream inputFile; //read only
    std::ofstream outputFile; //write only
    
    
    //opening a file
    std::ifstream inFile("data.txt");
    //or
    std::fstream myFile; //read & Write
    myFile.open("data.txt",ios::in | ios::out);
    //ios::in open for reading
    //ios::out open for writing
    //ios::app append to end of file
    //ios::ate - go to end of file on opening
    //ios::trunc - delete content if file exists
    //ios::binary - open in binary mode
    
    
    //reading a file
    //get() - read a single character
    //getline() - read a line of text
    //read() - read binary data
    //>> operator - read formatted data
    //check for eof() (end of file)
    //close()
    ifstream inFile("data.txt");
    string line;
    //read line by line
    while(getline(inFile,line)){
        std::cout << line << std::endl;
    }
    
    //reading word by word
    string word;
    while(inFile >> word){
        //words
    }
    
    //reading character by character
    char ch;
    while(!inFile.eof()){
        
    }
    
    
    //writing to files
    ofstream outFile("output.txt");
    outFile <<"Hello"<<endl;
    //.put() - write a single char
    //.write() write binary data
    //<< operator - write formatted data
    //ios::out mode to create/overwrite
    //ios::app mode to append
    //flush() to ensure data is written
    
    //appending to files
    ofstream outFile("output.txt", ios::app);

    if(!outFile){
        //error opening a file)
        return 1
    }
    
    
    //.good() - no errors
    //.eof() end of file reached
    //.fail() logical error on I/O operation
    //.bad() read.write error
    //.is_open() check if file is open
    //.clear() clear error flags
    //exceptions()
    
    return EXIT_SUCCESS;
}

