//netowring ts namespace
#include <iostream>
#include <fstream>

int main() {
    std::ifstream inFile;
    inFile.open("data.txt",std::ios::binary);
    
    std::ofstream outFile;
    outFile.open("output.bin", std::ios::binary | std::ios::out);
    
    //combined read and write access
    std::fstream combFile("data.bin", std::ios::binary | std::ios::in | std::ios::out);
    
    //writing data to binary files
    std::ofstream outFile("data.bin", std::ios::binary);
    
    if(outFile.is_open()){
        int num = 45;
        double pi = 3.14159;
        
        //write int (4 bytes)
        outFile.write(reinterpret_cast<char*>(&num),sizeof(num));
        outFile.write(reinterpret_cast<char*>(&pi),sizeof(pi));
        outFile.close();
    }
    
    //read data from binary file
    std::ifstream inFile("data.bin",std::ios::binary);
    if(inFile.is_open()){
        int num;
        double pi;
        //read int 4 bytes
        inFile.read(reinterpret_cast<char*>(&num),sizeof(num));
        
        //check if read was successfull
        if(inFile.gcount() == sizeof(num)){//returns number of bytes read
            //use the data..
        }
        inFile.close();
    }
    
    
    
    

    return EXIT_SUCCESS;
}

