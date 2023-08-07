class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // do nothing if nums2 is empty
        if (!n) { return; }
        // add nums2's elements to the back of nums1
        for (int i = 0; i < n; ++i) { nums1[m+i] = nums2[i]; }
        // sort modified nums1
        std::sort(nums1.begin(), nums1.end());
    }
};