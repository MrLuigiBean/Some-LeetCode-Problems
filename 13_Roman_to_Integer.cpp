#include <sstream>
#include <map>

class Solution {
public:
    
    // map of roman characters to integers
	std::map<char, int> data
    {
        {'I', 1}, {'V', 5 }, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500},
        {'M', 1000}
    };
    // that said, for smaller cases like this, 
    // just create a helper function to improve perfomance
    // like switch-case statements
    
    // using just the provided string
    int romanToInt(string s)
    {
        int total{0};
        for (int i{0}; i < s.length(); ++i)
        {
            // if the peeked character is bigger than the current...
            if (data[s[i + 1]] > data[s[i]]) // oops no out of bounds check lol
            {
                total += data[s[i + 1]] - data[s[i]];
                ++i; // skip peeked character
                continue;
            }
            total += data[s[i]];
        }
        return total;
    }
    
    // using stringstream
    int romanToInt0(string s)
    {
        std::stringstream is{s};
        int total{0};
        char ch;
        while (is >> ch)
        {
            // if the peeked character is bigger than the current...
            if (data[is.peek()] > data[ch])
            {
                total += data[is.peek()] - data[ch];
                is >> ch; // skip peeked character
                continue;
            }
            total += data[ch];
        }
        return total;
    }
};
