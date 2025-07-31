#include <iostream>

template<typename T, size_t S>
class Array
{
public:
    int Size() const {return S;}

private:
    T m_Data[S];
};


int main()
{
    int size = 5;
    Array<int,5> data;
    return 0;
}

