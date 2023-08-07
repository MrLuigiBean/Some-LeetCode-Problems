class Solution {
public:
    vector<vector<int>> generate(int numRows)
    {
        // initialise result with having the correct number of rows
        vector<vector<int>> result(numRows);

        // make each row have the correct number of spaces
        for (int i = 0; i < result.size(); ++i)
                result[i].reserve(i+1);
        
        for (int i = 0; i < result.size(); ++i)
        {
            for (int j = 0; j < result[i].capacity(); ++j)
            {
                // using the subscript operator to insert doesn't work
                // because the size is still 0 dummy!!!

                int value;

                // the edges are always 1
                if (j == 0 || j == result[i].capacity() - 1)
                    value = 1;
                
                // the next closest to the edges are always the row number
                else if (j == 1 || j == result[i].capacity() - 2)
                    value = i;

                // take numbers from previous row
                else
                    value = result[i-1][j-1] + result[i-1][j];

                result[i].emplace_back(value);
            }
        }
        return result;
    }
};