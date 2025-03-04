#include <iostream>
#include <memory>

class Example{
public:
    Example() {std::cout <<"Created"<<std::endl;
    }
    ~Example() {std::cout <<"Destroyed"<<std::endl;
    }
};

int main()
{
    //Example* ex = new Example(); //no no!!
    
    std::unique_ptr<Example> ex = std::make_unique<Example>();
    //automatically deletes at the end of scope
    
    return 0;
}
