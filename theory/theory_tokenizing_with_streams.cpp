//tokenizing with streams
#include <sstream>
#include <iostream>

int main()
{
    //string line = "GeeksForGeeks is a must try";
    std::string line = "13GeeksForGeeks13is13a13must13try";

    // Vector of string to save tokens
    std::vector <std::string> tokens;
     
    // stringstream class check1
    std::stringstream check1(line);
     
    std::string intermediate;
     
    // Tokenizing w.r.t. space ' '
    //    while(getline(check1, intermediate, ' '))
    while(getline(check1, intermediate, '1'))
    //while(check1 >> intermediate)
    {
        if(intermediate[0] == '3')
        {
            intermediate.erase(0,1);
            tokens.push_back(intermediate);
        }
        intermediate = "";
    }
     
    // Printing the token vector
    for(int i = 0; i < tokens.size(); ++i)
    {
        std::cout << tokens[i] << '\n';
    }
}
