# Intuition
<!-- Describe your first thoughts on how to solve this problem. -->
At first glance, it can be observed that the combinations of a certain sequence of digits share a pattern with the combinations of that same sequence of digits, but with the last digit chopped off. We can use this observation to build our solution by iterating through each digit of the given sequence.

![0017_Letter_Combinations_of_a_Phone_Number_Diagram](https://assets.leetcode.com/users/images/2c17fb85-e487-42da-819f-84b99bcec896_1701783305.485144.png)

# Approach
<!-- Describe your approach to solving the problem. -->
Since we observed that the solution of our problem builds upon the solution of a subproblem, a dynamic programming approach is suitable. This means that we iterate through the digits one by one, building the solutions for the subproblems along the way! Specifically, for each combination we encounter, we just make more combinations that have an additional character from our current digit appended to it. If the current digit is `3`, we just take each combination from the previous subproblem, and add `d`, `e` and `f` to each one!

# Complexity
If my complexities seem incorrect, please let me know. Thank you!

Let $$n$$ be the number of digits.
<!-- Add your time complexity here, e.g. $$O(n)$$ -->
- Time complexity: $$O(4^n)$$

<!-- Add your space complexity here, e.g. $$O(n)$$ -->
- Space complexity: $$O(4^n)$$

This is because 4 is the largest number of letters any single digit can have.

# Code
```
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

```