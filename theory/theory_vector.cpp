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
    
    
    // Vector resized to 7 and added
    // elements initialized to 9
    v.resize(7, 9);

    for (auto i : v)
        cout << i << " ";
    
    return 0;
}




// Function to merge two sorted vectors
std::vector<int> merge_sorted(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    std::vector<int> result;
    result.reserve(vec1.size() + vec2.size()); // Avoid reallocations

    size_t i = 0, j = 0;
    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] <= vec2[j]) {
            result.push_back(vec1[i]);
            ++i;
        } else {
            result.push_back(vec2[j]);
            ++j;
        }
    }

    // Append remaining elements from vec1
    while (i < vec1.size()) {
        result.push_back(vec1[i]);
        ++i;
    }

    // Append remaining elements from vec2
    while (j < vec2.size()) {
        result.push_back(vec2[j]);
        ++j;
    }

    return result;
}

/*
std::vector<int> vec = {1, 3, 5, 7, 3, 9};
int target = 3;

std::cout << "Vector: ";
print_vector(vec);
std::cout << "Searching for: " << target << "\n\n";

// 1. Using std::find
auto it = std::find(vec.begin(), vec.end(), target);
if (it != vec.end()) {
    std::cout << "std::find: Found " << target << " at index "
              << (it - vec.begin()) << "\n";
} else {
    std::cout << "std::find: " << target << " not found\n";
}

// 2. Using std::find_if (example: find first element > target)
auto it_if = std::find_if(vec.begin(), vec.end(),
                          [target](int x) { return x > target; });
*/



//// Max element in vector
//cout << *max_element(v.begin(), v.end()) << endl;
//
//// Max element in array
//cout << *max_element(arr, arr + n);




//// Find the maximum element in the vector of structure
//// based on the sno field
//St max = *max_element(v.begin(), v.end(),
//                [](const St &i, const St &j) {
//                    return i.sno < j.sno;
//                });


/*
 int main() {
     vector<int> v1 = {1, 5, 6, 8};
     vector<int> v2(v1.size());

     // Incrementing all elements of vector by 1
     transform(v1.begin(), v1.end(), v2.begin(),
               [](int a) {
                 return a + 1;
               });

     for (auto i : v2)
         cout << i << " ";
     return 0;
 }
 */
