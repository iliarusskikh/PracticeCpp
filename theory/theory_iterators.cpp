#include <iostream>
#include <vector>

#include <unordered_map>


int main() {
    std::vector<int> values = {1,2,4,6,87,2,5,7,33};
    
    /*
    for (int i=0; i< values.size(), i++){
        std::cout << values[i] <<"\n";
    }
    
    for (int value: values){
        std::cout << value << "\n";
    }*/
    
    for (std::vector<int>::iterator it =values.begin(); it!= values.end(); it++){
        std::cout << *it << "\n";//iterators useful when need to manupulate the collection of elements
        

    }
    
    std::unordered_map<std::string,int> map;
    map["lel"] = 5;
    map["kek"] = 2;
    
    
    using ScoreMap =  std::unordered_map<std::string,int>;
    for (ScoreMap::const_iterator it =  map.begin(). it!= map.end(); it++){
        auto& key = it->first;//& not copying the value
        auto& value = it->second;
    }

    for (auto kv:map){
        auto& key = kv.first;//& not copying the value
        auto& value = kv.second;
    }
    
    
    for (auto [key, value] :map){
        //auto& key = kv.first;//& not copying the value
        //auto& value = kv.second;
    }

    return EXIT_SUCCESS;
}
