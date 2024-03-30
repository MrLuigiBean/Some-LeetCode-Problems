// Runtime: 20ms, Beats 29.36% of users with C++
// Memory:	38.15MB, Beats 5.05% of users with C++
#include <vector>

class Solution {
public:
	// thanks to https://www.youtube.com/watch?v=bNvIQI2wAjk !
	std::vector<int> productExceptSelf(std::vector<int>& nums) {
		std::vector<int> answer(nums.size(), 1);

		// prefix pass
		int prefix = 1;
		for (int i = 0; i < nums.size(); ++i)
		{
			// multiply elements BEFORE current element
			prefix *= (i == 0 ? 1 : nums[i - 1]);
			answer[i] = prefix;
		}

		// suffix pass
		int suffix = 1;
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			// multiply elements AFTER current element
			suffix *= (i == nums.size() - 1 ? 1 : nums[i + 1]);
			answer[i] *= suffix;
		}

		return answer;
	}
};
