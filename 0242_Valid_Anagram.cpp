// Runtime: 0ms, Beats 100% of users with C++ (!!!)
// Memory: 8.56MB, Beats 59.98% of users with C++
#include <string>

class Solution
{
public:
	bool isAnagram(std::string s, std::string t)
	{
		// An array containing the count/frequency of each English letter.
		int letterFrequency[26] = {0};

		// For every letter in `s`, increment the corresponding element.
		for (char ch : s)
			++letterFrequency[ch - 'a'];

		// For every letter in `t`, decrement the corresponding element.
		// If the frequenycy is negative after decrementing, return false.
		for (char ch : t)
			if (--letterFrequency[ch - 'a'] < 0)
				return false;

		// Ensure that all letters have been used up.
		for (int n : letterFrequency)
			if (n > 0)
				return false;

		return true;
	}
};
