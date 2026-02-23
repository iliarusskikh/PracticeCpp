
//Initializer List
//vs
//initializer_list

#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>


class IntBag {
private:
    std::vector<int> data;

public:
    // This is the key constructor
    IntBag(std::initializer_list<int> init)
        : data(init) {  // copies elements from the braced-init-list
        std::cout << "constructed from initializer_list, size = " << init.size() << "\n";
    }

    // Also useful: range-based for support
    auto begin() const { return data.begin(); }
    auto end()   const { return data.end();   }

    void print() const {
        for (int x : *this) std::cout << x << " ";
        std::cout << "\n";
    }

    int sum() const {
        return std::accumulate(begin(), end(), 0);
    }
};



void print(std::initializer_list<int> il) {
    std::cout << "size = " << il.size() << "   elements: ";
    for (int x : il) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}




struct Data {
    int x,y,z;
};


struct ILThing{
    ILThing(std::initalizer_list<int>);
    int x, y, z;
    
};


const std::initializer_list<int>& bad_func() {
    return {1, 2, 3, 4, 5};   // ← DANGER – dangling reference!
    // The braced-init-list is a temporary → destroyed at end of return statement
}


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
    
    print({});          // size = 0
    print({1});         // size = 1
    print({1,2,3});     // size = 3
    print({10,20,30,40,50}); // size = 5

    // also very common:
    std::vector<int> v = {1, 2, 3, 4, 5};   // implicit initializer_list
    print(v);           // works because vector has constructor from initializer_list
    
    
    
    
    auto& lst = bad_func();           // ← dangling!
    // lst is now invalid – undefined behavior if you use it

    for (int x : lst) {               // UB – may crash, print garbage, etc.
        std::cout << x << " ";
    }
    
    
    
    IntBag bag1 {};                     // empty
    IntBag bag2 {1, 3, 5, 7, 9};        // nicest syntax
    IntBag bag3 = {10, 20, 30};         // also very common
    IntBag bag4({-1, -2, -3, -4});      // explicit braced-init

    bag2.print();                       // 1 3 5 7 9
    std::cout << "sum = " << bag3.sum() << "\n";   // 60
    
    
    return d.y + d.x;
}


