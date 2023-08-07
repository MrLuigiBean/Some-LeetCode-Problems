#include <string>
#include <unordered_set>

class Solution {
public:
    bool isStringUnique(std::string const& s)
    {
        std::unordered_set<char> letters;
        for (char const& letter : s)
        {
            std::pair<std::unordered_set<char>::iterator, bool> result = letters.insert(letter);
            if (!result.second) { return false; } // return the moment the insertion failed
        }
        return true; // letters.size() == s.size();
    }
    
    int lengthOfLongestSubstring(std::string s) {
        std::string result{}, substring;        
        for (unsigned int i = 0; i < s.length(); ++i)
        {
            for (unsigned int j = i + 1; j <= s.length(); ++j)
            {
                substring = s.substr(i, j-i);

                // only when unique and new substring is longer
                if (!isStringUnique(substring)) { ++i; continue; }
                // without ++i, code took too long :( (Time Limit Exceeded)
                // ++i because if string isn't unique, every single other substring
                // beginning with i will be guaranteed to fail as well. thus, move on!
                if (substring.size() <= result.size()) { continue; }
                result = substring;
            }
        }
        return result.length();
    }
};
