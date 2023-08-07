#include <vector>

class Solution {
public:
    int GetElement(std::vector<std::vector<int>> &matrix, int index)
	{
		int result = 0;
		if (matrix.size() == 1) // case for row vectors
		{
			result = matrix[0][index];
		}
		else if (matrix[0].size() == 1) // case for column vectors
		{
			result = matrix[index][0];
		}
		else
		{
			// cases for general matrices
			int row = index / matrix[0].size();
			int col = index % matrix[0].size();
			result = matrix[row][col];
		}
		return result;
	}
    
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        // because the matrix is sorted in ascending order, 
        // binary seach can be used.

        int left = 0, right = matrix.size() * matrix[0].size() - 1;
        
        // case for 1x1 matrix
        if (right <= 0)
            return matrix[0][0] == target;

        while (left <= right)
        {
            int middle = (left + right) / 2;
            int middleElement = GetElement(matrix, middle);
            
            if (target == middleElement)
                return true;
            
            // if element not found, decrease the
            // left or right bounds accordingly
            if (target < middleElement)
                right = middle - 1;
            else
                left = middle + 1;
        }
        return false;
    }
};