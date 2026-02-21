#include <iostream>
#include <sstream>
#include <string>

std::string intToString(int num){
    std::ostringstream oss;
    oss << number;
    return oss.str();
}


int main()
{
    //stringstream, istringstream, ostringstream
    std::stringstream ss;
    
    ss << "Hello" << " " <<"World";
    std::string word1, word2;
    int number;
    
    ss >> word1 >> word2;
    
    ss.clear();
    
    
    std::string data ="Jojn,34,enfne";
    std::stringstream sss(data);
    std::string name, job;
    int age;
    std::getline(sss,name,',');
    sss>>age;
    sss.ignore(); //skip comma
    std::getline(sss,job);
    
    return EXIT_SUCCESS;
}
