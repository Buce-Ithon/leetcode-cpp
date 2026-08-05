#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

/**
 * @file lc1049.cpp
 * @brief LeetCode 1049. Last Stone Weight II
 *
 * You are given an array of integers stones where stones[i] is the weight of the i-th stone.
 * We are playing a game with the stones. On each turn, we choose any two stones and smash
 * them together. Suppose the stones have weights x and y with x <= y. The result is:
 * - If x == y, both stones are destroyed.
 * - If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
 * 
 * Return the smallest possible weight of the left stone. If there are no stones left, return 0.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `stones = [2,7,4,1,8,1]`
 *   - Output: `1`
 * - **Example 2:**
 *   - Input: `stones = [31,26,33,21,40]`
 *   - Output: `5`
 *
 * ### Constraints:
 * - $1 \le \text{stones.length} \le 30$
 * - $1 \le \text{stones}[i] \le 100$
 */

class Solution {
public:
    /**
     * @brief Calculate the smallest possible weight of the remaining stone using 0-1 Knapsack DP.
     * 
     * @param stones Reference to a vector of stone weights
     * @return int The minimal remaining stone weight
     */
    int lastStoneWeightII(std::vector<int>& stones) {
        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;

        // dp[j] represents the maximum weight capacity we can pack into a knapsack of target 'j'
        std::vector<int> dp(static_cast<std::size_t>(target + 1), 0);

        for (int stone : stones) {
            // Reverse iteration to avoid reusing the same stone multiple times
            for (int j = target; j >= stone; --j) {
                dp[static_cast<std::size_t>(j)] = std::max(dp[static_cast<std::size_t>(j)], dp[static_cast<std::size_t>(j - stone)] + stone);
            }
        }

        // Total sum minus twice the best possible subset sum yields the minimum difference
        return sum - 2 * dp[static_cast<std::size_t>(target)];
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> stones1 = {2, 7, 4, 1, 8, 1};
    std::cout << "Example 1 Result: " << solver.lastStoneWeightII(stones1) << std::endl; // Expected: 1

    // Test Example 2
    std::vector<int> stones2 = {31, 26, 33, 21, 40};
    std::cout << "Example 2 Result: " << solver.lastStoneWeightII(stones2) << std::endl; // Expected: 5

    return 0;
}