#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

//struct is a user-defined data type
typedef struct GFG {
    int G1;
    char G2;
    float G3;
}Kek;

struct node {
    int data1;
    char data2;
    struct node* link;
};

int main()
{
    Kek hello;

    hello.G1 = 88;
    std::cout <<hello.G1 <<"\n";

    //struct pointer
    Kek* ptrStr = &hello;
    std::cout<<ptrStr->G1<<"\n'";
    
    
    //nodes
    struct node Node1;
    Node1.link = NULL;
    Node1.data1 = 1;
    Node1.data2 = 2;
    
    struct node Node2;
    Node2.link = NULL;
    Node2.data1 = 5;
    Node2.data2 = 6;
    
    Node1.link = &Node2;
    std::cout<< Node1.link->data1 << "\n";//accessing data from Node2
    
    
    return 0;
}

