#include <iostream>
#include <array>
//on stack

template<typename T, size_t S>
class Array{
public:
    //Array(int size){
        //m_Data = (int*)alloca(size * sizeof(int));//alloca take size in bytes
   // }
    constexpr int Size() const{return S;}
    T& operator[](int index){return m_Data[index];}//need reference to be able to write into this memory like a[4] = 3;
    const T& operator[](int index)const {return m_Data[index];}//if array is const then this version will be used dye to second const provided
    
    T* Data() {return m_Data;}//returning data for example memset(data,Data(),0,data,Size()*sizeof(int));
    
private:
    T m_Data[S];
};


int main(){

    Array<int, 19> data;
    //std::array<int,10> collection;
    //int array[5];
    
    static_assert(data.Size() < 10, "Size is too large");
    data.Size();
    
    return EXIT_SUCCESS;
}
