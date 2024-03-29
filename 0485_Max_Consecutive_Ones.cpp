// Runtime: 21ms, Beats 83.94% of users with C++
// Memory: 41.73MB, Beats 5.38% of users with C++
#include <vector>

class Solution
{
public:
	// I have no clue which is faster so here's both.
	int findMaxConsecutiveOnes(std::vector<int> &nums)
	{
#if 0
		std::vector<int> zeroIndices;

		// No clue how many zeros there could be -
		// better reserve some space just in case!
		zeroIndices.reserve(nums.size() / 2);

		// This value marks the beginning of the array.
		// Zero is not used since that's a possible index.
		zeroIndices.push_back(-1);

		// Obtain all the indices where a zero is present.
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] == 0)
				zeroIndices.push_back(i);

		// If there were no zeros added from nums itself,
		// all digits must have been `1`'s.
		if (zeroIndices.size() == 1)
			return nums.size();

		// If zeroIndices is as large as nums (plus one because of
		// the starting `-1` value), then there must be no zeros at all.
		if (zeroIndices.size() == nums.size() + 1)
			return 0;

		// This value marks the end of the array
		zeroIndices.push_back(nums.size());

		// For every pair of indices that had a zero,
		// find how many elements were in-between.
		int maxConsecutiveOnes = 0;
		for (int i = 0; i < zeroIndices.size() - 1; ++i)
		{
			int consecutiveOnes = zeroIndices[i + 1] - zeroIndices[i] - 1;

			// ignoring ternary operator for legibility's sake:
			maxConsecutiveOnes = std::max(maxConsecutiveOnes, consecutiveOnes);
		}

		return maxConsecutiveOnes;
#else
		// Prepends and appends one zero to the nums std::vector to denote the start and end.
		std::vector<int> newNums = std::vector<int>(1);
		newNums.insert(newNums.end(), nums.begin(), nums.end());
		newNums.push_back(0);

		int maxConsecutiveOnes = 0;
		int beginningZero = 0;
		for (int counter = 0; counter < newNums.size(); ++counter)
		{
			// If a zero is found, find how many elements were in-between.
			if (newNums[counter] == 0)
			{
				int consecutiveOnes = counter - beginningZero - 1;
				maxConsecutiveOnes = std::max(maxConsecutiveOnes, consecutiveOnes);
				beginningZero = counter; // jump ahead to the current zero
			}
		}

		return maxConsecutiveOnes;
#endif
	}
};
