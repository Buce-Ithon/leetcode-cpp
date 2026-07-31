#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @file lc0354.cpp
 * @brief LeetCode 354. Russian Doll Envelopes
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi]
 * represents the width and the height of an envelope.
 *
 * One envelope can fit into another if and only if both the width and height of
 * one envelope are greater than the other envelope's width and height.
 *
 * Return the maximum number of envelopes you can Russian doll (i.e., put one
 * inside the other).
 *
 * Note: You cannot rotate an envelope.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `envelopes = [[5,4],[6,4],[6,7],[2,3]]`
 *   - Output: `3`
 *   - Explanation: The maximum number of envelopes you can Russian doll is 3
 * ([2,3] => [5,4] => [6,7]).
 * - **Example 2:**
 *   - Input: `envelopes = [[1,1],[1,1],[1,1]]`
 *   - Output: `1`
 *
 * ### Constraints:
 * - $1 \le \text{envelopes.length} \le 10^5$
 * - $\text{envelopes}[i].\text{length} == 2$
 * - $1 \le w_i, h_i \le 10^5$
 */

class Solution {
public:
    /**
     * @brief Find the maximum number of envelopes that can be nested
     *
     * @param envelopes Reference to a 2D vector where envelopes[i] = [width, height]
     * @return int The maximum number of nested envelopes
     */
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        if (envelopes.empty()) {
            return 0;
        }

        // 1. Custom sort: Ascending by width; if widths are equal, descending by height
        std::sort(envelopes.begin(), envelopes.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
                  });

        // 2. Extract height array to perform Longest Increasing Subsequence (LIS) - DP
        // 3. Perform LIS using binary search (std::lower_bound) O(N log N)
        std::vector<int> tails;
        for (const auto& env : envelopes) {
            int h = env[1];
            auto it = std::lower_bound(tails.begin(), tails.end(), h);
            if (it == tails.end()) {
                tails.push_back(h);
            } else {
                *it = h;
            }
        }

        // 4. The length of tails is the max number of envelopes
        return static_cast<int>(tails.size());
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<std::vector<int>> envelopes1 = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int res1 = solver.maxEnvelopes(envelopes1);
    std::cout << "Example 1 Result: " << res1 << std::endl;

    // Test Example 2
    std::vector<std::vector<int>> envelopes2 = {{1, 1}, {1, 1}, {1, 1}};
    int res2 = solver.maxEnvelopes(envelopes2);
    std::cout << "Example 2 Result: " << res2 << std::endl;

    return 0;
}