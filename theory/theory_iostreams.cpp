#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>


std::ostream& currency(std::ostream& os){
    os <<"$"<<std::fixed <<std::setprecision(2);
    return os;
}

void pricessFile(const std::string& filename){
    std::ifstream file(filename);
    
    if(!file.is_open()){
        throw std::runtime_error("Failed to open a file");
    }
    //process the file
    file.close();
}

int main() {
    std::cout << "Output to console"<<std::endl;
    int value;
    std::cin >> value;
    
    //ios_base : base calss with formatting flags
    //ios : adds stream state functionality
    //istream : input operations
    //ostream: output operations (cout)
    //iostream both input and output
    double pi = 3.14159345245452l;
    std::cout << std::fixed << std::setprecision(4);
    int x = 255;
    std::cout <<"Decimal:" <<  x <<std::endl; <<"Hex" <<std::hex <<x <<std::endl;
    
    double price = 42.5;
    std::cout << currency <<price << std::endl;
    
    
    return EXIT_SUCCESS;
}
