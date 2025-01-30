#include <iostream>
#include <vector>
static int s_CopyCount = 0;
static int s_AllocationCount = 0;

void* operator new(size_t size)
{
    std::cout<<"Allocated "<< size<<" bytes\n";
    s_AllocationCount++;
    return malloc(size);//override new to count dynamic allocations
}


struct Data
{
    int Value = 0;
    
    Data() = default;
    Data(int value): Value(value){}
    Data(const Data& other): Value(other.Value)
    {
        s_CopyCount++;
        std::cout <<"Copied Data \n"; //copy constructor
    }
    
public:
    void printData(const Data& data) { // Pass by reference

        std::cout << "Name: " << data.Value << "\n";

    }
};


int main()
{
    std::vector<Data> vector;
    vector.reserve(5);
    
    for (int i=0; i<5; ++i)
        vector.emplace_back(Data(i));//to avoid copying, use emplace_back instead of push_back. (i)

    for(auto x:vector)
        x.printData(x);
    
    std::cout<<s_AllocationCount<<"\n";
    std::cout<<s_CopyCount<<"\n";
    
    return 0;
}
