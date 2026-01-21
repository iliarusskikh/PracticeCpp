#include <type_traits>


template<auto value>
void do_things(){
    static_assert(value > 5);
}


int main()
{

//    static_assert(false); //this would fail the compiler
    //static_assert(std::is_pointer_v<char>);
    static_assert(value > 5, std::format("Expected 5, got {}",value));
    
    
    return EXIT_SUCCESS;
}
