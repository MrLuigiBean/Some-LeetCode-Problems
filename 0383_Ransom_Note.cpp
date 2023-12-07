// Runtime: 50ms, Beats 5.05% of users with C++
// Memory: 9.10MB, Beats 85.17% of users with C++
#include <string>
#include <algorithm>

class Solution
{
public:
	bool canConstruct(std::string ransomNote, std::string magazine)
	{
		std::sort(ransomNote.begin(), ransomNote.end());
		std::sort(magazine.begin(), magazine.end());

		for (int i = 0; i < ransomNote.size(); ++i)
		{
			if (auto pos = magazine.find(ransomNote[i]); pos != std::string::npos)
				magazine.erase(pos, 1);
			else
				return false;
		}
		return true;
	}
};
