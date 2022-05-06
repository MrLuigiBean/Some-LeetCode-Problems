class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
        { return false; }
        std:string text{std::to_string(x)};
        size_t length = text.length();
        if (length % 2) // odd length
        {
            for (int i{0}; i < length / 2; ++i)
            {
                if (text[i] != text[length -1 - i])
                {return false;}
            }
        }
        else // even length
        {
            for (int i{0}; i < length / 2; ++i)
            {
                if (text[i] != text[length - 1 - i])
                {return false;}
            }
        }
        return true;
    }
};
