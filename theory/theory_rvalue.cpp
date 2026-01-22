//rvalue -> does not have persistent mem location, does not have mem location
//lvalue -> persistent memory location, can get an address of it
//int x = 10; //x is lvalue, 10 is rvalue

//rvalue reference binds to rvalue || int&& rr = 5;
//lvalue ref binds to lvalue || int& k = x;


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <cstring>


int& GetValue(){//now this is rvalue
    static int value = 30;
    return value;
}

void PrintName(const std::string& name){
    std::cout<<"lvalue "<<name<<"\n";
}

void PrintName(std::string&& name){//overload function
    std::cout<<"rvalue "<<name<<"\n";
}

int main() {

    int i = 10;//ivalue left side, rvalue on right side - i something that has location
    //or function that returns int
    int k = GetValue();
    GetValue() = 50;
    
    //exception
    const int& a = 30;
    
    //rvalue reference &&
    std::string firstname="hehehe";
    std::string secondname="hehww";
    std::string fullname = firstname+secondname;//rvalue on the right
    PrintName(fullname); //takes lvalue as argument
    PrintName(firstname + secondname);//rvalue
    

    //rvalue can help us detecting temporary objects
    
    return EXIT_SUCCESS;
}
