// C++ program to show the different operator functions on std optional

#include <iostream>
#include <fstream>
#include <optional>


struct User{
    std::string name;
    int age;
};


std::optional<User> findUser(const std::string& id){
    //database lookup logic
    if(userExits(id)){
        return User{getName(id),getAge(id)};
    }
    
    
    return std::nullopt;
}



std::optional<std::string> ReadFileAsString(const std::string& filepath){
    std::ifstream stream(filepath);
    if(stream){
        std::string result;
        //read file
        stream.close();
        return result;
    }else{
        //return std::string();//or returning empty string
        return {};//return for std optional
    }
    //we need a better way to know if the file was read successfully
}


int main()
{
    //c++ 17
    std::optional<std::string> data = ReadFileAsString("data.txt");
    
    std::string value = data.value_or("Not present");//provides default values!
    
    if(data.has_value()){//or if (data)
        //true
        std::cout << "File read successfully " << "\n";

    }else
    {
        std::cout << "Failed " << "\n";

    }
    //std::string& string = *data; //accessing data
    std::cout << "Hello " << "\n";
    
    
    //.reset(), makes empty or destroying any contained value
    
    
    
    return 0;
}

