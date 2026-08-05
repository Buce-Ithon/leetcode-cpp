#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @file lc0368.cpp
 * @brief LeetCode 368. Largest Divisible Subset
 *
 * Given a set of distince positive integers nums, return the largest subset answer s.t.
 * every pair (answer[i], answer[j]) of elements in this subset satisfies:
 * - answer[i] % answer[j] == 0, or
 * - answer[j] % answer[i] == 0
 *
 * If there are multiple solution, return any of them.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [1,2,3]`
 *   - Output: `[1,2]`
 *   - Explanation: `[1,3]` is also accepted.
 * - **Example 2:**
 *   - Input: `nums = [1,2,4,8]`
 *   - Output: `[1,2,4,8]`
 *
 * ### Constraints:
 * - $1 \le \text{nums.length} \le 1000$
 * - $1 \le \text{nums}[i] \le 2 \times 10^9$
 * - All the integers in `nums` are unique.
 */

class Solution {
public:
    /**
     * @brief Find the largest subset of numbers where every pair is divisible
     *
     * @param nums Reference to a vector of distinct positive integers
     * @return std::vector<int> The largest divisible subset
     */
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        // 1. Sort the input array for convenience of comparison and calculating
        std::sort(nums.begin(), nums.end());
        std::size_t n = nums.size();
        // 2. Create dp[n]: used to record the LDS of the current index in every traverse state
        std::vector<int> dp(static_cast<std::size_t>(n),1);
        // 3. Create prev[n]: used to record the index sequence of the LDS of the current index in every traverse state
        std::vector<int> prev(static_cast<std::size_t>(n),-1);
        // 4. Recording the final LDS of whole indexs
        std::size_t maxi = 0;
        // 5. The process of DP
        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && dp[i] <= dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    prev[i] = static_cast<int>(j);
                }
            }
            if (dp[i] > dp[maxi]) maxi = i;
        }
        // 6. Push back elements into the and according to the index recorded by prev[n]
        std::vector<int> ans;
        for (std::size_t i = maxi; i != static_cast<std::size_t>(-1); i = static_cast<std::size_t>(prev[i])) {
            ans.push_back(nums[i]);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> nums1 = {1, 2, 3};
    std::vector<int> res1 = solver.largestDivisibleSubset(nums1);
    std::cout << "Example 1 Result: ";
    for (int x : res1)
        std::cout << x << " ";
    std::cout << std::endl;

    // Test Example 2
    std::vector<int> nums2 = {1, 2, 4, 8};
    std::vector<int> res2 = solver.largestDivisibleSubset(nums2);
    std::cout << "Example 2 Result: ";
    for (int x : res2)
        std::cout << x << " ";
    std::cout << std::endl;
    
    // Test Example 3
    std::vector<int> nums3 = {4, 8, 10, 240};
    std::vector<int> res3 = solver.largestDivisibleSubset(nums3);
    std::cout << "Example 3 Result: ";
    for (int x : res3)
        std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}