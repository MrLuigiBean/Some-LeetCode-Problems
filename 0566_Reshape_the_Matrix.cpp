class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        // return original matrix if dimensions are identical
        if (r == mat.size() && c == mat[0].size()) { return mat; }

        // return original matrix if the reshaped dimensions will omit data
        // or leave extra space
        if (r * c != mat.size() * mat[0].size()) { return mat; }

        // initialise result to the correct dimensions
        vector<vector<int>> result(r, vector<int>(c));

        const u_int total_elements = r * c;
        const u_int old_cols = mat[0].size();

        for (int i = 0; i < total_elements; ++i)
        {
            u_int row = i / c;
            u_int col = i % c;
            u_int old_row = i / old_cols;
            u_int old_col = i % old_cols;

            // obtain underlying data to use pointer arithmetic
            *(result[row].data()+col) = *(mat[old_row].data()+old_col);
        }
        return result;
    }
};