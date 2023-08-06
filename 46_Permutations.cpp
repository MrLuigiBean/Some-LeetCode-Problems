#include <algorithm> // #include <vector> is already inside, nice!
#include <iostream> // #include <string> is already inside, nice!

/*
	Problem Constraints:

	~ All the integers of nums are unique.
	~ 1 <= nums.length <= 6
	~ -10 <= nums[i] <= 10
*/

class Solution
{
public:
	// for n elements, there are n! permutations
	constexpr int factorial(int const n)
	{
		return n > 1 ? n * factorial(n - 1) : 1;
	}

	std::string IntsToChars(std::vector<int> const &nums)
	{
		std::string result;

		// since -10 <= nums[i] <= 10...
		// +75 to each number so that they become (printable) characters for strings
		// `-10` becomes -10 + 75 = 65 = 'A'
		// `0` becomes 0 + 75 = 75 = 'K'
		// `10` becomes 10 + 75 = 85 = 'U'
		for (auto const &num : nums)
			result += num + 'K';

		return result;
	}

	std::vector<std::vector<int>> StringResultsToFinalResults(std::vector<std::string> const &strings)
	{
		std::vector<std::vector<int>> finalResults(strings.size(), std::vector<int>(strings.front().size()));

		for (int i = 0; i < strings.size(); ++i)
			for (int j = 0; j < strings.front().size(); ++j)
				finalResults[i][j] = strings[i][j] - 'K';

		return finalResults;
	}

	std::vector<std::string> PermuteSymbols(std::string symbols)
	{
		if (symbols.size() <= 2) // it should never be < 2, but i'm using <= just in case
		{
			// std::vector<std::string> temp(2);
			// temp[0] = symbols;
			// temp[1] = std::string({symbols.back(), symbols.front()});
			
			// the only permutations for [a, b]
			// is itself and itself, but reversed,
			// that being [a, b] and [b, a].
			// it's only two elements - might as well reverse it myself!
			return std::vector<std::string>({symbols, std::string({symbols.back(), symbols.front()})});
		}
		else
		{
			std::vector<std::string> stringResults = std::vector<std::string>(factorial(symbols.size()));
			unsigned index = 0;

			for (int i = 0; i < symbols.size(); ++i)
			{
				// for example:
				// i = 0: AKU (no rotation)
				// i = 1: KUA
				// i = 2: UAK
				std::string rotatedString = symbols.substr(i) + symbols.substr(0, i);

				// maybe try `for (std::string& str : PermuteSymbols(rotatedString.substr(1)))` // ???
				// POGGERS THAT WORKS HELL YEAH

				for (std::string& str : PermuteSymbols(rotatedString.substr(1)))
				{
					// for every string, prepend the letter that was removed initially
					stringResults[index++] = rotatedString.front() + str;
				}
			}
			return stringResults;
		}
	}

	std::vector<std::vector<int>> permute(std::vector<int> &nums)
	{
		// if there is only one number, the only permutation is itself
		if (nums.size() == 1)
			return std::vector<std::vector<int>>(1, nums);

		std::sort(nums.begin(), nums.end());

		// std::string theString = IntsToChars(nums);

		// auto stringResults = PermuteSymbols(theString);

		// return StringResultsToFinalResults(stringResults);

		// i want to do the follow so so badly XD :
		return StringResultsToFinalResults(PermuteSymbols(IntsToChars(nums)));
	}
};
