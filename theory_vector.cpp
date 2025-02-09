#include <iostream>
#include <vector>


using namespace std;

int main() {
    vector<char> v = {'a', 'c', 'f', 'd', 'z'};

    // Deleting last element 'z'
      v.pop_back();
      for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
  
      // Deleting element 'f'
    vector<char>::iterator it =find(v.begin(),v.end(),'w');
    cout << *it <<endl;
      v.erase(find(v.begin(), v.end(), 'f')); //needs an iterator pointer
    
      for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    
    return 0;
}

