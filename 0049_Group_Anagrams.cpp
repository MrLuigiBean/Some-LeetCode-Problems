// Runtime: 58ms, Beats 7.15% of users with C++
// Memory:	27.90MB, Beats 18.62% of users with C++
#include <vector>
#include <string>
#include <unordered_map>

class Solution
{
public:
#if 1
	// Thanks to https://www.youtube.com/watch?v=vzdNOK2oB2E !
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
	{
		// No groups to make if there are no std::strings to examine!
		if (strs.empty())
			return {};

		// If there's only one element, that is the only anagram present.
		if (strs.size() == 1)
			return std::vector<std::vector<std::string>>(1, std::vector<std::string>(1, strs.front()));

		// The frequencies of letters in the word.
		// e.g. eat ->1a0b0c0d1e0f0g...0s1t0u0v0w0x0y0z
		// e.g. tea -> <identical to above>
		// e.g. tan ->1a0b0c...0m1n0p...0s1t0u0v0w0x0y0z
		using key_type = std::string;

		// The strings that are anagrams of the letters in the key
		using value_type = std::vector<std::string>;

		std::unordered_map<key_type, value_type> map;

		for (const std::string& str : strs)
		{
			// An array containing the count/frequency of each English letter.
			constexpr int lettersSize = 26;
			int letterFrequency[lettersSize] = { 0 };

			// For every letter in the std::string, increment the corresponding element.
			for (char ch : str)
				++letterFrequency[ch - 'a'];

			key_type key;
			for (int i = 0; i < lettersSize; ++i)
				key += std::to_string(letterFrequency[i]) + static_cast<char>('a' + i);

			map[key].emplace_back(str);
		}

		// Gotta move everything from the map to the container to return
		std::vector<std::vector<std::string>> result;
		result.reserve(map.size());
		for (const auto& entry : map)
			result.emplace_back(entry.second);

		return result;
	}
#else // Time Limit Exceeded :(
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
	{
		// No groups to make if there are no std::strings to examine!
		if (strs.empty())
			return {};

		// If there's only one element, that is the only anagram present.
		if (strs.size() == 1)
			return std::vector<std::vector<std::string>>(1, std::vector<std::string>(1, strs.front()));

		// Construct as if the first element was already considered. (see above)
		std::vector<std::vector<std::string>> groupedAnagrams = std::vector<std::vector<std::string>>(1, std::vector<std::string>(1, strs.front()));

		// Skip first std::string since `groupedAnagrams` has it already.
		for (int i = 1; i < strs.size(); ++i)
		{
			const std::string& str = strs[i];
			bool successfullyGrouped = false;

			for (int j = 0; j < groupedAnagrams.size(); ++j)
			{
				// Use a REFERENCE to the current anagram group being considered.
			std:
				std::vector<std::string>& anagramGroup = groupedAnagrams[j];

				// is anagram with front element <-> is anagram with any element
				if (isAnagram(str, anagramGroup.front()))
				{
					anagramGroup.emplace_back(str);
					successfullyGrouped = true;
					break;
				}
			}

			// Create new group if there were no previous anagrams.
			if (!successfullyGrouped)
				groupedAnagrams.emplace_back(1, str);
		}

		return groupedAnagrams;
	}

	// From 0242: Valid Anagram
	bool isAnagram(std::string s, std::string t)
	{
		// An array containing the count/frequency of each English letter.
		int letterFrequency[26] = { 0 };

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
#endif
};