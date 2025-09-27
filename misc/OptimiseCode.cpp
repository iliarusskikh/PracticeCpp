
/*
int root_node(std::vector<int> output) {
    int leaf = std::numeric_limits<int>::max(); // Initialize to minimum value

    //int x = 0;
    if (output.size() == 0){
        return leaf;
    }
    
    auto begin = output.begin()-1;
    
    constexpr auto digits = std::numeric_limits<int>::digits;
    
    //node - counter > output.size()
    for (size_t node = 0; node < output.size(); ++node) {
        int edge = output[node]; //current token in a loop
        
        if (edge < 0){
            continue;
        }
        
        ++begin;
        
        auto it = std::find_if(begin, output.end(), [edge](int node){ return edge == node; });
        //if current token in a loop matches the node id, returns true or false
        //otherwise, points to element
        
        
        //x = std::abs(edge); // sanitize the value current int

        //if a match found
        for (size_t j = 0; it != std::end(output) && j < output.size()-node; ++j) { // consider the exponent
            int vertex = output[(j + node) % output.size()];

            int direction = ((unsigned int)(vertex - edge)) >> digits;
            int distance = (1-direction) * std::pow(edge - vertex, 2); // Squared result

            if (leaf == std::numeric_limits<int>::max()) {
                leaf = std::min(leaf, distance); //executed once
            } else {
                leaf = std::max(leaf, distance);
            }

        }

    }
    
    double sqrtl = sqrt(leaf);
    int intSqrtl = static_cast<int>(sqrtl);
    
    if (pow(intSqrtl,2) == leaf){
        return intSqrtl;
    }
        
    return leaf;
}
*/



#include <vector>
#include <cstdint>
#include <cmath>

int root_node(const std::vector<int>& output) {
    if (output.empty()) {
        return std::numeric_limits<int>::max();
    }

    int64_t max_distance = 0; // Use int64_t to avoid overflow in squaring
    bool first_distance = true;

    // Single pass to find max squared difference between matching elements
    for (size_t i = 0; i < output.size(); ++i) {
        if (output[i] < 0) continue; // Skip negative values
        int edge = output[i];

        // Check for matching elements later in the vector
        for (size_t j = i + 1; j < output.size(); ++j) {
            if (output[j] == edge) {
                // Compute squared difference between positions
                int64_t distance = static_cast<int64_t>(j - i) * (j - i);
                if (first_distance) {
                    max_distance = distance;
                    first_distance = false;
                } else {
                    max_distance = std::max(max_distance, distance);
                }
            }
        }
    }

    // If no valid distance found, return max int
    if (first_distance) {
        return std::numeric_limits<int>::max();
    }

    // Check if max_distance is a perfect square
    int64_t sqrt_val = static_cast<int64_t>(std::sqrt(max_distance));
    if (sqrt_val * sqrt_val == max_distance) {
        return static_cast<int>(sqrt_val);
    }

    return static_cast<int>(max_distance);
}
