#include <iostream>
#include <vector>

/**
 * @file lc0416.cpp
 * @brief LeetCode 416. Partition Equal Subset Sum
 *
 * Given an integer array nums, return true if you can partition the array into two subsets
 * such that the sum of the elements in both subsets is equal or false otherwise.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [1,5,11,5]`
 *   - Output: `true`
 *   - Explanation: The array can be partitioned as [1, 5, 5] and [11].
 * - **Example 2:**
 *   - Input: `nums = [1,2,3,5]`
 *   - Output: `false`
 *   - Explanation: The array cannot be partitioned into equal sum subsets.
 *
 * ### Constraints:
 * - $1 \le \text{nums.length} \le 200$
 * - $1 \le \text{nums}[i] \le 100$
 */

class Solution {
public:
    /**
     * @brief Determine if the array can be partitioned into two subsets with equal sum
     *
     * @param nums Reference to a vector of integers
     * @return true If a partition exists, false otherwise
     */
    bool canPartition(std::vector<int>& nums) {
        int sum = 0;
        int max_num = 0;

        for (int num : nums) {
            sum += num;
            max_num = std::max(max_num, num);
        }

        // If total sum is odd, it cannot be partitioned into two equal integer subsets
        if (sum % 2 != 0) {
            return false;
        }

        int target = sum / 2;

        // If the largest single element exceeds the target sum, partition is impossible
        if (max_num > target) {
            return false;
        }

        // 0-1 Knapsack DP: dp[j] indicates whether a subset sum equal to j can be formed
        std::vector<bool> dp(static_cast<std::size_t>(target + 1), false);
        dp[0] = true;

        for (int num : nums) {
            // Iterate backwards to prevent using the same element multiple times
            for (int j = target; j >= num; --j) {
                dp[static_cast<std::size_t>(j)] = dp[static_cast<std::size_t>(j)] || dp[static_cast<std::size_t>(j - num)];
            }
        }

        return dp[static_cast<std::size_t>(target)];
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> nums1 = {1, 5, 11, 5};
    bool res1 = solver.canPartition(nums1);
    std::cout << "Example 1 Result: " << (res1 ? "true" : "false") << std::endl;

    // Test Example 2
    std::vector<int> nums2 = {1, 2, 3, 5};
    bool res2 = solver.canPartition(nums2);
    std::cout << "Example 2 Result: " << (res2 ? "true" : "false") << std::endl;

    return 0;
}