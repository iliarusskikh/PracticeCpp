//rvalue -> does not have persistent mem location, does not have mem location
//lvalue -> persistent memory location, can get an address of it
//int x = 10; //x is lvalue, 10 is rvalue

//rvalue reference binds to rvalue || int&& rr = 5;
//lvalue ref binds to lvalue || int& k = x;

//we need rvalue reference for move constructor

#include <iostream>
#include <cstring>

class MyString{
    char* data;

public:
    MyString(const char* s){
        data = new char[strlen(s) + 1];//null character
        strcpy(data,s);
        std::cout << "Constructed!"<<std::endl;
    }
    
    //deep copy
    MyString(const MyString& other){//lvalue reference is defined!
        data = new char[strlen(other.data) + 1];//null character
        strcpy(data,other.data);
        std::cout << "Copied!\n";

    }
    
    MyString(MyString&& other){//when move constructor is triggered, we need R-value reference, with && in place; also const key word removed
        data = other.data
        other.data = nullptr;
        std::cout << "Moved!\n";

    }
    
    ~MyString(){
        delete[] data;
        std::cout << "Destroyed!\n";
    }
    
    void print(){
        if(data){//if data is nullptr
            std::cout <<data<<"\n";
        } else{
            std::cout <<"Empty\n";
        }
    }
};


int main(){
    MyString s1("Hello");
    MyString s2 = s1; //copy object of s1, s1 is lvalue
    s1.print();
    s2.print();
    
    //now we want to transfer the ownership of s1 into s2
    //hence, move constructor
    //we need to tell the compilor to read s1 as a temporary object or rvalue.
    
    MyString s3 = std::move(s1); //now
    
    return EXIT_SUCCESS;
}
