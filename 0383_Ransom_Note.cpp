// Runtime: 13ms, Beats 74.65% of users with C++
// Memory: 9.00MB, Beats 85.17% of users with C++
#include <string>

class Solution
{
public:
	bool canConstruct(std::string ransomNote, std::string magazine)
	{
		// If `magazine` has fewer letters than `ransomNote`,
		// it's not possible for `ransomNote` to be constructed.
		if (ransomNote.size() > magazine.length())
			return false;

		// Since `ransomNote` and `magazine` consist of only lowercase English letters,
		// we can use an array of 26 to allow each alphabet to have its own frequency!
		int arr[26] = { 0 };

		// 'a' takes the first element in the array
		for (int i = 0; i < magazine.length(); ++i)
			++arr[magazine[i] - 'a'];

		// Subtract the frequency of the current `ransomNote` letter.
		// If the frequency becomes negative after subtraction, there
		// isn't enough letters to make `ransomNote` from `magazine`.
		for (int i = 0; i < ransomNote.size(); ++i)
			if (--arr[ransomNote[i] - 'a'] < 0)
				return false;

		return true;
	}
};
