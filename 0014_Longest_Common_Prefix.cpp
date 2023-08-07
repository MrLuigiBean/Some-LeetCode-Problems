#include <vector>
#include <string>

class Solution {
public:
    bool wordsCheck(std::vector<std::string>& strings, std::string& prefix)
    {
        for (std::string& word : strings)
        {
            // if no match with prefix that starts from the beginning
            if (word.find(prefix) != 0) { return false; }
        }
        return true;
    }
    
    std::string longestCommonPrefix(std::vector<std::string>& strs)
    {
        // first character of first word
        std::string prevPrefix{}, prefix{strs[0].substr(0, 1)};

        // eliminate empty string situations
        for (std::string& word : strs)
        {
            if (word == "") { return ""; }
        }

        // skipping vectors with only one word
        if (strs.size() == 1) { return strs[0]; }
        else
        {
            while (wordsCheck(strs, prefix))
            {
                prevPrefix = prefix;
                // .substr() is safe, it doesn't allow taking in more characters
                // if a word only has so many. Using .substr() with a BIG BOI range
                // will just return the whole word with no funny business.
                prefix = strs[0].substr(0, prefix.size() + 1);
                // stop when previous prefix is the same as the current
                if (!prevPrefix.compare(prefix)) { return prefix; }
            }
            return prefix.substr(0, prefix.size() - 1);
        }
    }
};
