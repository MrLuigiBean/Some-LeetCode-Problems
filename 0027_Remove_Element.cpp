#include <vector>
#include <algorithm>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        auto x = std::remove(nums.begin(), nums.end(), val);
        auto y = x - nums.begin();
        return y;
    }
};
