class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> checked;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto result = checked.insert(nums[i]);
            if (!result.second) { return true; }
        }
        return false;
    }
};