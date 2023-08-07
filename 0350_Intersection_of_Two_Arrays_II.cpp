#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
        // number, frequency
        std::map<int, int> hashmap;
        // or maybe a static array of size 1000 would work too lmao
        // since the question assures that the numbers are [0, 1000]

        std::vector<int> result;
        
        // add numbers and respective frequencies to hashmap
        for (int i  = 0; i < nums1.size(); ++i) { ++hashmap[nums1[i]]; }

        for (int i = 0; i < nums2.size(); ++i)
        {
            // match found!
            if (hashmap[nums2[i]] > 0)
            {
                // decrement frequency
                --hashmap[nums2[i]];
                // add to result
                result.emplace_back(nums2[i]);
            }
        }
        return result;
    }
};