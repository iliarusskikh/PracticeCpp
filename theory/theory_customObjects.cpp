// C++ program to demonstrate the creation of descending
// order set container
//providing custom comparator and hash function
#include <iostream>
#include <set>
#include <unordered_set>

struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// In global namespace or in your own namespace — NOT inside std::
namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            // Better combining method (simple & reasonably good)
            size_t hx = hash<int>{}(p.x);
            size_t hy = hash<int>{}(p.y);

            // Option A – simple & popular
            return hx ^ (hy << 1);           // or hy + 0x9e3779b9 + (hx << 6) + (hx >> 2)

            // Option B – more avalanche (often better distribution)
            // return hx + 0x9e3779b9 + (hy << 6) + (hy >> 2);
        }
    };
}



struct Person{
    std::string name;
    int age;
    
    //sorting by default, alternatively user has to provide an overload comparator
    bool operator<(const Peron& other)const{ //operator<
        return age < other.age;
    }
};


struct PersonNameComp{
    //overloading comparator
    bool operator()(const Person& a, const Person& b)const{ //operator()
        return a.name>b.name;
    }
}





int main()
{
    std::set<Person> peopleByAge;
    
    
    //by default by age
    //using custom comparators and object
    //sort cutstom data types based on name
    std::set<Person, PersonNameComp> peopleByName;
    
    
    
    
    std::unordered_set<Point> setCustomHash;
    
    
    
    return EXIT_SUCCESS;
}



//creating a lambda comparator
//auto cmp = [](const Person& a, const Person& b){
//    return a.age > b.age;
//};
//using comparator within a priority queue
//std::priority_queue<Person, std::vector<Person>, decltype(cmp)> people(cmp);
