#include <iostream>
#include <string>
#include <sstream>
int main()
{
    
    char s[] = "cStyleString"; //c-style string terminated by \0 character //char s[] = {'g', 'f', 'g', '\0'};
    std::cout << s << std::endl;
    
    std::string str("StringClass");
    std::cout << str;
    
    
    //getting input from user
    //cin, getline, stringstream s
    //std::string j;
    //std::cin >>j;
    //getline(std::cin,j);
    std::string str2 = "Hello World";
    std::string temp;
    std::stringstream obj(str2);
    while(obj >>temp) //tokenization
    {
        std::cout << temp <<"\n";
    }    
    std::string::iterator itr;
    itr = str2.begin();
    std::cout<<*itr<<"\n";
    std::cout << str2.length();
    str2.resize(5);//adjust number of elements
    
    //string
    //can be represented as strean of chars
    //in strings mem allocated dynamically
    //implementation is slower than char array
    
    //char array
    //array of chars can be terminated by \n
    //size allocated statically
    //array decay potentially
    
    str2.swap(str);
    
    swap(str,str2);
    std::string sub = "ld";
    std::cout << str2.find(sub); //returns position
    str2.push_back('s');//append char to the string
    str2.pop_back();//remove last char
    //.clear() removes all elements

    
    char kek1[] = "Hello2";
    char kek2[] = "Hello4";
    // comparing first 5 characters of each
    int value = std::strncmp(kek1, kek2, 5);
    strcat(kek1,kek2);//kek2 goes into kek1
    
    char ch[80];
    str2.copy(ch, 3, 0);//copying elements into char array
    
    return 0;
}
