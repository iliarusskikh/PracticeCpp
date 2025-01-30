#include <iostream>
#include <vector>

class Solution
{
public:
    bool canJump(std::vector<int>&nums)
    {
        int distance = 0;
        for(int i = 0; i<nums.size()-1; ++i)
        {
            distance = std::max(distance, i + nums[i]);
            if(distance == i) return false;
        }
        return true;
    };
}cl;

int main()
{
    std::vector<int>k ={3,2,1,0,8};
    std::cout<<cl.canJump(k)<<"\n";
    return 0;
}
