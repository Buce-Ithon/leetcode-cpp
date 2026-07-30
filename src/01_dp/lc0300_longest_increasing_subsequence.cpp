#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @file lc0300_longest_increasing_subsequence.cpp
 * @brief LeetCode 300. Longest Increasing Subsequence
 * 
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * 
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [10,9,2,5,3,7,101,18]`
 *   - Output: `4`
 *   - Explanation: The longest increasing subsequence is `[2,3,7,101]`, therefore the length is 4.
 * - **Example 2:**
 *   - Input: `nums = [0,1,0,3,2,3]`
 *   - Output: `4`
 * - **Example 3:**
 *   - Input: `nums = [7,7,7,7,7,7,7]`
 *   - Output: `1`
 * 
 * ### Constraints:
 * - $1 \le \text{nums.length} \le 2500$
 * - $-10^4 \le \text{nums}[i] \le 10^4$
 */

class Solution {
public:
    /**
     * @brief Calculates the length of the longest strictly increasing subsequence using Dynamic Programming.
     * 
     * @param nums Reference to an integer array.
     * @return int The length of the longest strictly increasing subsequence.
     * 
     * @note Time Complexity: O(n^2), Space Complexity: O(n)
     */
    int lengthOfLIS(std::vector<int> &nums) {
        int n = static_cast<int>(nums.size());

        std::vector<int> LIS(n, 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    LIS[i] = std::max(1 + LIS[j], LIS[i]);
                }
            }
        }
        int sol = 0;
        for (int k = 0; k < n; k++) {
            sol = std::max(sol, LIS[k]);
        }
        return sol;
    }
};

int main() {
    Solution solver;

    // Test example 1
    std::vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    int res1 = solver.lengthOfLIS(nums1);
    std::cout << "Example 1 Result: " << res1 << " (Expected: 4)" << std::endl;
    assert(res1 == 4);

    // Test 2: nums = [0,1,0,3,2,3], Output: 4
    std::vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    int res2 = solver.lengthOfLIS(nums2);
    std::cout << "Example 2 Result: " << res2 << " (Expected: 4)" << std::endl;
    assert(res2 == 4);

    std::cout << "\nAll test cases passed!" << std::endl;
    return 0;
}
