#include <bitset>
#include <iostream>

using namespace std;

int main()
{
    int a1 = 5; //00000101 00000000 00000000 00000000 4 bytes
    int a = 0b101;
    int b = 0b10110;
    b <<=4;
    int c = a|b;
    cout<< std::bitset<9>(c)<<"\n";
    
    

    bitset<4> bitset1("1001"), bitset2("1010");

    cout << "Unsigned Long value: " << allSet.to_ulong();
    
    
    return 0;
}

