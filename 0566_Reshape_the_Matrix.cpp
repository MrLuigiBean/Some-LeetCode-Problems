#include <vector>
#include <cstdint>

class Solution {
public:
    std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& mat, int r, int c) {
        // return original matrix if dimensions are identical
        if (r == mat.size() && c == mat[0].size()) { return mat; }

        // return original matrix if the reshaped dimensions will omit data
        // or leave extra space
        if (r * c != mat.size() * mat[0].size()) { return mat; }

        // initialise result to the correct dimensions
        std::vector<std::vector<int>> result(r, std::vector<int>(c));

        const unsigned total_elements = r * c;
        const unsigned old_cols = mat[0].size();

        for (int i = 0; i < total_elements; ++i)
        {
            unsigned row = i / c;
            unsigned col = i % c;
            unsigned old_row = i / old_cols;
            unsigned old_col = i % old_cols;

            // obtain underlying data to use pointer arithmetic
            *(result[row].data()+col) = *(mat[old_row].data()+old_col);
        }
        return result;
    }
};