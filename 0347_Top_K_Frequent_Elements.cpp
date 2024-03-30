// Runtime: 11ms, Beats 69.53% of users with C++
// Memory:	17.03MB, Beats 78.59% of users with C++
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
	std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
		// Map of integers(keys) to their frequencies(value).
		std::unordered_map<int, int> map;

		for (int num : nums)
			++map[num];

		// Obtain the data from the map and sort it by descending frequency.
		std::vector<std::pair<int, int>> temp;
		temp.reserve(map.size());

		for (const auto& thing : map)
			temp.emplace_back(thing.first, thing.second);

		std::sort(temp.begin(), temp.end(), [](const auto& a, const auto& b)
			{
				return a.second > b.second;
			});

		// Fill result with the first k integers.
		// (which were already sorted by descending frequency)
		std::vector<int> result;
		result.reserve(k);
		for (int i = 0; i < k; ++i)
			result.emplace_back(temp[i].first);

		return result;
	}
};
