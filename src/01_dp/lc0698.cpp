#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

/**
 * @file lc0698.cpp
 * @brief LeetCode 698. Partition to K Equal Sum Subsets
 *
 * Given an integer array nums and an integer k, return true if it is possible
 * to divide this array into k non-empty subsets whose sums are all equal.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [4,3,2,3,5,2,1]`, `k = 4`
 *   - Output: `true`
 *   - Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 * - **Example 2:**
 *   - Input: `nums = [1,2,3,4]`, `k = 3`
 *   - Output: `false`
 *
 * ### Constraints:
 * - $1 \le k \le \text{nums.length} \le 16$
 * - $1 \le \text{nums}[i] \le 10^4$
 * - The frequency of each element is in the range $[1, 4]$.
 */

class Solution {
public:
    /**
     * @brief Determines if the array can be partitioned into k subsets with equal sum.
     * 
     * @param nums Vector of integers representing the elements.
     * @param k Number of equal sum subsets to form.
     * @return true If valid partition exists, false otherwise.
     */
    bool canPartitionKSubsets(std::vector<int>& nums, int k) {
        int total_sum = std::accumulate(nums.begin(), nums.end(), 0);

        // Basic impossibility check
        if (total_sum % k != 0) {
            return false;
        }

        int target = total_sum / k;

        // Sort in descending order for greedy pruning
        std::sort(nums.rbegin(), nums.rend());

        // If the largest single element exceeds the target sum, partition is impossible
        if (nums[0] > target) {
            return false;
        }

        int n = static_cast<int>(nums.size());
        // memo[used_mask] stores whether the state (represented by bitmask) can lead to a valid partition.
        // -1: unvisited, 0: false, 1: true
        std::vector<int> memo(1 << n, -1);

        // Lambda helper for Backtracking with Bitmask DP State Memoization
        std::function<bool(int, int, int)> backtrack = [&](int mask, int current_sum, int k_remaining) -> bool {
            // Base case: All k subsets have been successfully constructed
            if (k_remaining == 0) {
                return true;
            }

            // Return memoized result if already calculated
            if (memo[mask] != -1) {
                return memo[mask] == 1;
            }

            // If current bucket is filled, move to the next subset starting sum from 0
            if (current_sum == target) {
                bool res = backtrack(mask, 0, k_remaining - 1);
                memo[mask] = res ? 1 : 0;
                return res;
            }

            // Try picking available elements
            for (int i = 0; i < n; ++i) {
                // If element i is already used, skip
                if ((mask & (1 << i)) != 0) {
                    continue;
                }

                // Pruning: if adding nums[i] exceeds target, skip
                if (current_sum + nums[i] > target) {
                    continue;
                }

                // Choose nums[i] and recurse
                if (backtrack(mask | (1 << i), current_sum + nums[i], k_remaining)) {
                    memo[mask] = 1;
                    return true;
                }
            }

            memo[mask] = 0;
            return false;
        };

        return backtrack(0, 0, k);
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> nums1 = {4, 3, 2, 3, 5, 2, 1};
    int k1 = 4;
    std::cout << "Example 1 Result: " << (solver.canPartitionKSubsets(nums1, k1) ? "true" : "false") << std::endl; // Expected: true

    // Test Example 2
    std::vector<int> nums2 = {1, 2, 3, 4};
    int k2 = 3;
    std::cout << "Example 2 Result: " << (solver.canPartitionKSubsets(nums2, k2) ? "true" : "false") << std::endl; // Expected: false

    return 0;
}