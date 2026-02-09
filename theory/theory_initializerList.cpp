
//Initializer List
//vs
//initializer_list

#include <iostream>
#include <initializer_list>


struct Data {
    int x,y,z;
};


struct ILThing{
    ILThing(std::initalizer_list<int>);
    int x, y, z;
    
};


int main()
{
    //it's a braced list of things
    //this is being used for direct initialization of the members of Data
    Data d{1,2,3}; //Initializer List
    
    
    //std::initalizer_list
    //a type that can match from an Initalizer List
    //this is initializing the single parameter
    //for the user defined constructor
    ILThings ilt({3,4,5});
    
    
    return d.y + d.x;
}

