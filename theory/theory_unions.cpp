#include <iostream>


struct Entity{
    union
    {
        float a;
        int b;
        
    };
};


struct Vector2
{
    float x,y;
    
}

struct Vector4
{
    union
    {
        struct
        {
            float x,y,z,w;
        };
        
        struct
        {
            Vector2 a,b; //occupying same memory
        }
    };
}



int main()
{
    Entity u;
    u.a = 2.0f;
    std::cout << u.a<< " " <<u.b << std::endl;
    //u.b is int representation of a
    
    
    return EXIT_SUCCESS;
}
