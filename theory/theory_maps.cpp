// C++ program to illustrate the begin and end iterator
#include <iostream>
#include <map> //self balancing binary search tree - elements end up sorted
#include <string>
#include <unordered_map>//hash table - may be faster than map
#include <sstream>
using namespace std;

struct CityRecord{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

//everytime your map needs a hash function for custom structure
namespace std{
    tempalte<>
    struct hash<CityRecord>
    {
        size_t operator()(const CityRecord& key){
            return hash<std::string>()(key.Name);
        }
        
    }
}


int main()
{
    unordered_map<CityRecord, string> mmap; //cannot hash custom data, alternatively use as a pointer CityRecord* or provide a hash implementation
    
     
    
    // Create a map of strings to integers
    map<string, int> mp;
    
    // Insert some values into the map
    mp["one"] = 1;
    mp["two"] = 2;
    mp["three"] = 3;

    // Get an iterator pointing to the first element in the
    // map
    map<string, int>::iterator it = mp.begin();

    // Iterate through the map and print the elements
    while (it != mp.end())
    {
        mp[it->first]++;
        cout << "Key: " << it->first
             << ", Value: " << it->second << endl;
        ++it;
    }
    
    cout << "Size of map: " << mp.size() << endl;

    
    // empty map container
    map<int, int> gquiz1;

    // insert elements in random order
    gquiz1.insert(pair<int, int>(1, 40));
    gquiz1.insert(pair<int, int>(2, 30));
    gquiz1.insert(pair<int, int>(3, 60));
    gquiz1.insert(pair<int, int>(4, 20));
    gquiz1.insert(pair<int, int>(5, 50));
    gquiz1.insert(pair<int, int>(6, 50));
    map<int, int> gquiz2(gquiz1.begin(), gquiz1.end());
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));

    if (mp.count("four") > 0)
    {
         cout << "Key 'four' is in the map" << endl;
    }
    
    for (auto a : mp)
    {
        mp[a.first]++;
    }
    
    
    multimap<int, int>::iterator it2; // empty multimap container

    multimap<int, int> mumap; // empty multimap container
    // insert elements in random order
    mumap.insert(pair<int, int>(1, 40));
    mumap.insert(pair<int, int>(2, 30));
    mumap.insert(pair<int, int>(3, 60));
    mumap.insert(pair<int, int>(6, 10));
    mumap.insert(pair<int, int>(6, 10));
    while (it2 != mumap.end())
    {
        //mumap[it2->second]++;
        cout << "Key: " << it2->first << ", Value: " << it2->second << endl;
        ++it2;
    }
    
    
    
    unordered_map<string, double> umap = {  //inserting element directly in map
     {"One", 1},
     {"Two", 2},
     {"Three", 3}
   };

     // inserting values by using [] operator
     umap["PI"] = 3.14;
     umap["root2"] = 1.414;
     umap["root3"] = 1.732;
     umap["log10"] = 2.302;
     umap["loge"] = 1.0;

     // inserting value by insert function
     umap.insert(make_pair("e", 2.718));

     string key = "PI";

     // If key not found in map iterator
     // to end is returned
     if (umap.find(key) == umap.end())
       cout << key << " not found\n\n";
    
    
    
    
    //print frequencies
    string str = "geeks for geeks geeks quiz "
                 "practice qa for";
    
    // each word is mapped to its frequency
    unordered_map<string, int> wordFreq;
    
    // breaking input into word using
    // string stream
    // Used for breaking words
    stringstream ss(str);
    
    // To store individual words
    string word;
    while (ss >> word)
      wordFreq[word]++;

    // now iterating over word, freq pair
    // and printing them in <, > format
    unordered_map<string, int>:: iterator p;
    for (p = wordFreq.begin();
         p != wordFreq.end(); p++)
      cout << "(" << p->first << ", " <<
                     p->second << ")\n";
    
    
    string nn;
    double gg;
    for (auto& [nn,gg] : umap){
        std::cout << nn << " " << gg << "\n";
    }
    
    
    /*-------------------------------------------------*/
    
    for (auto& kv : umap){
        std::string& namee = kv.first;
        double kkkk = kv.second;
    }

    //iterating through a vector is still faster than a map
    
    return 0;
}

//theory_maps.cpp
