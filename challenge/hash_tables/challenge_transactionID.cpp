//This code detects "fraudulent" user IDs based on co-occurrence frequency in pairs.
//It assumes each string in the input vector represents a transaction that contains two user IDs (the first two tokens),
//and it counts how many times each user ID appears across all such pairs.
//If a user ID appears in ≥ threshold transactions, it is considered suspicious ("fraudulent").

#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

std::vector<std::string> get_fraud_id(const std::vector<std::string>& uid, int threshold) {
    
    std::unordered_map<std::string, int> count;
    std::vector<std::string> temp;

    for (const std::string& transaction : uid) { //using range
        stringstream ss(transaction); //single string appended into stream
        temp.clear(); //ensure temp vector is cleard

        std::string word;
        while (ss >> word) {
            temp.push_back(word);
        }

        // Safety: skip invalid lines (less than 2 IDs)
        if (temp.size() < 2) {
            continue;
        } // valid: 2 ids

        const std::string& id1 = temp[0];
        const std::string& id2 = temp[1];

        if (id1 != id2) {
            count[id1]++;
            count[id2]++;
        } else {
            count[id1]++; //same ID for both IDs
        }
    }

    std::vector<std::string> result; //detected IDs over threshold
    for (const auto& [id, freq] : count) { //new style
        if (freq >= threshold) { //if more than threshold transactions
            result.push_back(id);
        }
    }

    
    // Sort descending numerically (safest with stoull to avoid overflow)
    sort(result.begin(), result.end(),
         [](const std::string& a, const std::string& b) {
             return stoull(a) > stoull(b);
         });
    
    //OR rbegin()/rend() - reverse iterator
    //sort(result.rbegin(), result.rend()
    
    return result;
}



int main() {
    std::vector<std::string> id = {
        "345366 89921 45",
        "029323 38239 23",
        "38239 345366 15",
        "029323 38239 77",
        "345366 38239 23",
        "029323 345366 13",
        "38239 38239 23"
    };

    std::vector<std::string> res = get_fraud_id(id, 3);

    std::cout << "Fraudulent IDs (appearing >= 3 times): ";
    for (const std::string& s : res) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    return EXIT_SUCCESS;
}
