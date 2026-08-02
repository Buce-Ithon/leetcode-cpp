#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @file lc0740.cpp
 * @brief LeetCode 740. Delete and Earn
 *
 * You are given an integer array nums. You want to maximize the number of points
 * you get by performing the following operation any number of times:
 *
 * - Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete
 *   every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
 *
 * Return the maximum number of points you can earn by applying the above operation
 * some number of times.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [3,4,2]`
 *   - Output: `6`
 *   - Explanation: You can perform the following operations:
 *     - Delete 4 to earn 4 points. nums = [3,4,2] -> [2] (3 is also deleted).
 *     - Delete 2 to earn 2 points. nums = [] (1 and 3 deleted).
 *     - You earn a total of 6 points.
 * - **Example 2:**
 *   - Input: `nums = [2,2,3,3,3,4]`
 *   - Output: `9`
 *   - Explanation: You can perform the following operations:
 *     - Delete a 3 to earn 3 points. All 2's and 4's are deleted. nums = [3,3].
 *     - Delete a 3 again to earn 3 points. nums = [3].
 *     - Delete a 3 once more to earn 3 points. nums = [].
 *     - You earn a total of 9 points.
 *
 * ### Constraints:
 * - $1 \le \text{nums.length} \le 2 \times 10^4$
 * - $1 \le \text{nums}[i] \le 10^4$
 */

class Solution {
public:
    /**
     * @brief Find the maximum number of points that can be earned
     *
     * @param nums Reference to a vector of integers
     * @return int Maximum total points
     */
    int deleteAndEarn(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // 1. Find the maximum element to bound the range of values
        int max_val = 0;
        for (int num : nums) {
            max_val = std::max(max_val, num);
        }

        // 2. Aggregate the total points earned by picking each value
        std::vector<int> sum(max_val + 1, 0);
        for (int num : nums) {
            sum[num] += num;
        }

        // 3. Dynamic Programming (equivalent to House Robber problem)
        //    dp[i][0]: Max points from values up to i without picking i
        //    dp[i][1]: Max points from values up to i while picking i
        int first = sum[0];
        int second = std::max(sum[0], sum[1]);

        for (int i = 2; i <= max_val; ++i) {
            int current = std::max(second, first + sum[i]);
            first = second;
            second = current;
        }

        return second;
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> nums1 = {3, 4, 2};
    int res1 = solver.deleteAndEarn(nums1);
    std::cout << "Example 1 Result: " << res1 << std::endl;

    // Test Example 2
    std::vector<int> nums2 = {2, 2, 3, 3, 3, 4};
    int res2 = solver.deleteAndEarn(nums2);
    std::cout << "Example 2 Result: " << res2 << std::endl;

    return 0;
}