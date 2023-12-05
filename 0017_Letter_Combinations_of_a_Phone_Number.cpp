// Runtime: 0ms, Beats 100% of users with C++ (!!!)
// Memory: 6.92MB, Beats 49.78% of users with C++
#include <vector>
#include <string>

class Solution
{
public:
	std::vector<std::string> letterCombinations(std::string digits)
	{
		if (digits.empty())
			return {};

		// The case where only 1 digit is entered.
		// Dynamic programming is not necessary to provide the right combinations.
		if (digits.size() == 1)
		{
			const char* chars = GetKeyChars(digits.front());
			unsigned numOfChars = strlen(chars);

			std::vector<std::string> result;
			result.reserve(numOfChars);

			// construct a string with only 1 character - that being chars[i]
			for (int i = 0; i < numOfChars; ++i)
				result.emplace_back(1, chars[i]);

			return result;
		}

		// In truth, the code above is a repetition of the code below.
		// The reason I decided to separate the cases where `digits.size()` is 0 or 1 is
		// because I did not want to incur unnecessary heap allocations for `history` container.

		// Used for Dynamic Programming (will store the results of each iteration).
		std::vector<std::vector<std::string>> history{ digits.size() + 1 };

		// The case when there are no digits being considered - no digits, no combinations!
		history[0] = std::vector<std::string>{ 1, "" };

		for (int i = 0; i < digits.length(); ++i)
		{
			const char* chars = GetKeyChars(digits[i]);
			unsigned numOfChars = strlen(chars);

			// obtain the previous combinations made with the keys prior
			const std::vector<std::string>& prev = history[i];

			// obtain the vector to store our current combinations made with the additional key being considered
			std::vector<std::string>& curr = history[i + 1];

			// Note that for every combination beforehand, there will be `numOfChars` times more that are made.
			// e.g. before: ["a","b","c"]
			// e.g. after: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
			// We went from 3 combinations to 3 * 3 = 9 combinations! Space must be reserved for this.
			curr.reserve(prev.size() * numOfChars);

			// append characters from the new key to the old combinations
			for (const std::string& combination : prev)
				for (unsigned j = 0; j < numOfChars; ++j)
					curr.emplace_back(combination + chars[j]);
		}

		return history[history.size() - 1];
	}

private:
	// look-up table(LUT) from Keys to the Characters they produce
	static constexpr char LUT[8][5]
	{
					"abc\0",	"def\0",
		"ghi\0",	"jkl\0",	"mno\0",
		"pqrs",		"tuv\0",	"wxyz"
	};

	// Obtain the characters mapped to a given digit/key
	inline const char* GetKeyChars(const unsigned key)
	{
		// as '2' is the first possible key, it should have index 0
		return LUT[key - '2'];
	}
};
