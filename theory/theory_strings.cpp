#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>


static uint32_t s_AllocCount=0;

void* operator new(size_t size){
    
    s_AllocCount++;
    std::cout << "Allocating "<<size<<" bytes";
    return malloc(size);
}

void PrintName(const std::string& name){
    std::cout << name << "\n";
}

void PrintNameStrView(std::string_view name){
    std::cout << name << "\n";
}



int main()
{
    
    char arrr[] = "hello";  // Array
    const char* ptr13 = "world";  // Pointer to literal (use const to prevent modification)
    // Or: char* s = new char[6]; strcpy(s, "hello");  // Dynamic allocation (heap).
    std::string dynStr = "world";  // Internally allocates on heap if needed
    
    std::cout << strlen(prt13) << std::endl;
    std::cout << sizeof(dynStr) << std::endl;
    
    
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
    //can be represented as stream of chars
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
    
    
    const char* name0 = u8"Hello";
    const wchar_t* name2 = L"Hello";
    const char16_t* name3 = u"Hello";
    const char32_t* name4 = U"Hello";
    
    
    
    
    
    //how to make strings performance faster
    //allocation on heap slows down the program
    std::string name = "Hehehe"; //heap allocation 1
    PrintName(name); //another allocation, when func param creates allocation
    
    std::string_view firstpart(name.c_str(),3);//3 chars
    PrintNameStrView(firstpart);//pointer to chars instead of creating a substring ; no mem allocations
    //
    
    // to get rid of all allocations, dont use function which has string as a param
    //also dont use strings - use const char* instead
    const char* naame = "No allocation";
    
    std::cout <<"Allocations: "<<s_AllocCount <<"\n";
    
    
    //sso small string optimisation
    //small strings not heap allocated.. up to certain length (16 chars)?
    
    std::string test = "MyTest";//allocated in stack in release mode .. for debug it would allocate on heap
    
    
    return 0;
}


/*
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    std::string str = "apple,banana,orange,grape";
    std::vector<std::string> tokens;
    std::string temp;
    std::stringstream obj(str);

    // Tokenize by comma
    while (std::getline(obj, temp, ',')) {
        std::cout << temp << "\n";
        tokens.push_back(temp);
    }

    // Print all tokens from the vector
    std::cout << "\nStored tokens:\n";
    for (const auto& token : tokens) {
        std::cout << token << "\n";
    }

    return 0;
}
*/
