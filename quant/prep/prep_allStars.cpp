#include <iostream>
#include <unordered_map>
#include <random>
#include <algorithm>
#include <type_traits>

void* operator new(size_t s) {
    if (s == 0) s = 1;  // Fix zero-size
    std::cout << "Allocating " << s << " bytes\n";
    if (void* p = std::malloc(s))
        return p;
    throw std::bad_alloc{};
}

void* operator new[](size_t s) {  // Fixed syntax
    return operator new(s);
}

void operator delete(void* p) noexcept {
    std::free(p);
}

void operator delete[](void* p) noexcept {
    std::free(p);
}


template<typename T>
T execut(T a, T b){
    return a*b;
}

template<typename K>
class MyClass{
private:
    K data;
public:
    MyClass() = default;
    
    //copy
    MyClass(const MyClass& p) = delete;
    MyClass& operator=(MyClass& p) = delete;
    
    //move
    MyClass(const MyClass&& p) = delete;
    MyClass& operator=(MyClass&& p) = delete;
    
    ~MyClass()=default;
};


struct Point{
    int x;
    int y;
}

struct MyHash{
    size_t operator()(const Point& p)const{
        return std::hash<int>()(p.x)^std::hash<int>()(p.y);
    }
};

struct MyComparator{
    bool operator()(const Point& p1, const Point& p2) const{
        return p1.x==p2.x && p1.y==p2.y;
    }
    
};


int main(){
    
    std::unordered_map<Point, int, MyHash, MyComparator> mp;
    
    const char* h = "Hekki";
    std::string_view n(h);
    
    
    std::vector<int> vec = {1,2,6,8,32,4,7,2,4,89,24};
    std::random_device r;
    std::mt19937 gen(r());
    std::shuffle(vec.begin(), vec.end(),gen);
    
    for (auto k:vec)
        std::cout <<k <<"\n";
    
    return 0;
}
