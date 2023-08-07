#include <vector>
#include <set>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::set<int> checked;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto result = checked.insert(nums[i]);
            if (!result.second) { return true; }
        }
        return false;
    }
};