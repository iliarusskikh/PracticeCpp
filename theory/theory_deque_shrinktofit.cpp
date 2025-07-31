//releases unused memory, useful after elements release
#include <iostream>
#include <deque>


int main()
{
    std::deque<int> data (100,1);//100 elements in deq
    std::cout<<data.size() << std::endl;
    
    data.erase(data.begin(),data.begin()+90);
    std::cout<<data.size() << std::endl;

    data.shrink_to_fit();
    std::cout<<data.size() << std::endl;
    
    return 0;
}
