class Solution {
public:
    // https://www.interviewbit.com/blog/maximum-subarray-sum/
    // https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
    int maxSubArray(vector<int>& nums) {
        // vectors with a single element
        if (nums.size() == 1) { return nums[0]; }
        
        int finals = INT_MIN, current = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            // add next number
            current += nums[i];
            // check if current maximum is greater
            if (current > finals) { finals = current; }
            // if the sum up until this point is negative, reset it
            if (current < 0) { current = 0; }
        }
        return finals;
    }
};