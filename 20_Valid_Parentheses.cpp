class Solution {
public:
    bool validate(std::string &string, size_t &round, size_t &square, size_t &curly)
    {
        round = string.find("()");
        square = string.find("[]");
        curly = string.find("{}");
        
        return round != std::string::npos ||
               square != std::string::npos ||
               curly != std::string::npos;
    }
    
    bool isValid(string s)
    {
        size_t round, square, curly;

        while (validate(s, round, square, curly))
        {
            // erase matches, if any
            if (round != std::string::npos)
            {
                s.erase(round, 2);
                continue;
            }
            if (square != std::string::npos)
            {
                s.erase(square, 2);
                continue;
            }
            if (curly != std::string::npos)
            {
                s.erase(curly, 2);
                continue;
            }
        }
        return !s.size();
    }
};
