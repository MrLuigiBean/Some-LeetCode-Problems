#include <vector>
#include <algorithm>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        /*const size_t oldSize{nums.size()};
        int newSize = oldSize;
        for (int i{0}; i < oldSize - 1; ++i)
        {
            if (nums[i] == nums[i + 1])
            {
                // do the shifting here
                for (int j{i}; j < oldSize - i; ++j)
                {
                    nums[j] = nums[j + 1];
                }
                --newSize;
                i += 1;
            }
            if (i == newSize +1)
            { break; }
        }
        return newSize;*/
        auto x = std::unique(nums.begin(), nums.end());
        auto y = x - nums.begin();
        return y;
        
    }
};
