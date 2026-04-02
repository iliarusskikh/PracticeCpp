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
    while(getline(check1, intermediate, '1'))//while(check1 >> intermediate)
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






/*
int main2(){
    
    std::map<string,int> mp;
    std::string input = "joshfe  owkof w0 if0w 0i3f0 ofkew oo okfw 23f";
    
    std::stringstream ss(input);
    std::string token;
    while(getline(ss,token,' ')){
        mp[token]++;
        token = "";
    }
    
    auto it = *std::max_element(mp.begin(),mp.end(),[](const auto &i, const auto &j){return i.second < j.second;})
    std::cout << it.second <<"\n";
}
*/
