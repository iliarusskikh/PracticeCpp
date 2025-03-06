//allows picking a random element from the contrainer without mixing it
// std::sample ensures randomness without replacement.
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    std::vector<int> data{1,2,3,4,5,6,7,8};
    std::vector<int> sample_result(3);
    std::random_device rd;
    std::mt19937 gen(rd()); //random num geneerator
    
    std::sample(data.begin(),data.end(), sample_result.begin(), sample_result.size(), gen);
    
    for (int n:sample_result)
        std::cout << n << std::endl;
    
    return 0;
}
