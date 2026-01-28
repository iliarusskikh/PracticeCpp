#include <iostream>
#include <memory>

struct Orange{
    operator float() {return 5.5f;}
    
};


tempalte<typename T>
class ScopedPtr{
public:
    ScopedPtr() = default;
    ScopedPtr(T* ptr) : m_Ptr(ptr){}
    ~ScopedPtr() {delete m_Ptr;}
    
    T* Get(){return m_Ptr;}
    const T* Get() const {return m_Ptr;}
    
    operator bool() const {return IsValid();} //need this bool conversion operator
    
    
private:
    T* m_Ptr = nullptr;
};

struct Entity{
    float X = 0.0f, Y=0.0f;
};

void ProcessEntity(const ScopedPtr<Entity>&e){
    if (e){
        //..
    }
}



int main()
{
    ScopedPtr<Entity> e = new Entity();
    Entity * entity = new Entity();
    
    if(entity != nullptr){
        //..
    }
    
    
    
    Orange orange;
    float f = orange; //overlooading
    
    std::cout << f << "\n";//5.5
    std::cout << float(orange) << "\n";//5.5

    
    
    return EXIT_SUCCESS;
}

