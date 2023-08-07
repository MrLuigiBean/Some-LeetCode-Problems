#include <vector>
#include <set>

class Solution {
public:

    const int BOX_WIDTH = 3;
    const int BOARD_WIDTH = 9;
    const char EMPTY_CHAR = '.';

    struct CustomException
    {
        enum TYPE {ROW, COL, BOX};
        TYPE error_type;
        CustomException(TYPE type) : error_type{type}{}
    };

    bool ValidateRow(std::vector<std::vector<char>> const& board, int row)
    {
        std::set<char> rowDigits;

        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            char value = board[row][i];

            if (value == EMPTY_CHAR)
                continue;

            auto result = rowDigits.insert(value);

            // sets will fail to insert duplicate elements
            if (!result.second)
                throw CustomException(CustomException::ROW);
        }
        return true;
    }

    bool ValidateCol(std::vector<std::vector<char>> const& board, int col)
    {
        std::set<char> colDigits;

        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            char value = board[i][col];

            if (value == EMPTY_CHAR)
                continue;

            auto result = colDigits.insert(value);

            // sets will fail to insert duplicate elements
            if (!result.second)
                throw CustomException(CustomException::COL);
        }
        return true;
    }
    
    bool ValidateBox(std::vector<std::vector<char>> const& board, int box)
    {
        std::set<char> boxDigits;
        
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            int row = (box / 3) * BOX_WIDTH + i / 3;
            int col = (box % 3) * BOX_WIDTH + i % 3;
            char value = board[row][col];

            if (value == EMPTY_CHAR)
                continue;

            auto result = boxDigits.insert(value);

            // sets will fail to insert duplicate elements
            if (!result.second)
                throw CustomException(CustomException::BOX);
        }
        return true;
    }

    bool isValidSudoku(std::vector<std::vector<char>>& board)
    {
        try
        {
            // check all rows
            for (int i = 0; i < BOARD_WIDTH; ++i)
                ValidateRow(board, i);
            
            // check all columns
            for (int i = 0; i < BOARD_WIDTH; ++i)
                ValidateCol(board, i);
            
            // check all boxes
            for (int i = 0; i < BOARD_WIDTH; ++i)
                ValidateBox(board, i);
        }
        catch(CustomException const&)
        {
            return false;
        }
        return true;
    }
};