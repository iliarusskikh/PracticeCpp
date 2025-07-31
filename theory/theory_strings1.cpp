#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

int main()
{
    
    char s[] = "cStyleString"; //c-style string terminated by \0 character //char s[] = {'g', 'f', 'g', '\0'};
    std::cout << s << std::endl;
    
    std::string str("StringClass");
    std::cout << str;
    std::vector <std::string> tokens;

    
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
        tokens.push_back(temp);

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
    
    
    //ways to create an array of strings
    
    //array of strings using pointers, each pointer points to a particular string
    const char* colour[4] = { "Blue", "Red", "Orange", "Yellow" };
    
    //create array of strings using a 2D array
    char colour2[4][10] = { "Blue", "Red", "Orange", "Yellow" }; //storing chars
    
    //create array of strings using string class
    std::string colour3[4] = { "Blue", "Red", "Orange", "Yellow" };
    
    //using vector class
    std::vector<std::string> colour4 { "Blue", "Red", "Orange", "Yellow" };
    
    //using array class
    std::array<std::string,4>colour5 { "Blue", "Red", "Orange", "Yellow" };
    
    
    //string functions
    std::string num1 = "Get this prep";
    std::cout<< num1.at(3);//char at index
    
    std::string kk = num1 + str2;
    kk.append(num1);//adds up
    
    num1.compare(kk);//returns 0 if equals
    //str1.compare(position,length,str2);
    //.find() can be either char or string
    
    //std::string kkkk = str1.substr(start,num of chars);
    num1.insert(4,"hello"); //insert at specific location
    num1.replace(2,4,"cats");//replaces from index 2 , 4 characters , with cats
    
    std::string str5 = "jduhis:jdiie";
    unsigned int pos = str5.find(":");
    // or str5.substr(0,pos);
    std::string subs = str5.substr(pos + 1);//from position

    
    //printing all substrings
    for (int i = 0; i < 7; i++)
        for (int len = 1; len <= 7 - i; len++)
            std::cout << str5.substr(i, len) << std::endl;
    //int x = stoi(sub);  srtring to integer if string is integer
    return 0;
}
