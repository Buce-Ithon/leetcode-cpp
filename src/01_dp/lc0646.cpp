#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

/**
 * @file lc0646.cpp
 * @brief LeetCode 646. Maximum Length of Pair Chain
 *
 * You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and
 * lefti < righti.
 *
 * A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can
 * be formed in this fashion.
 *
 * Return the length longest chain which can be formed.
 *
 * You do not need to use up all the given intervals. You can select pairs in
 * any order.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `pairs = [[1,2],[2,3],[3,4]]`
 *   - Output: `2`
 *   - Explanation: The longest chain is [1,2] -> [3,4].
 * - **Example 2:**
 *   - Input: `pairs = [[1,2],[7,8],[4,5]]`
 *   - Output: `3`
 *   - Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
 *
 * ### Constraints:
 * - $n == \text{pairs.length}$
 * - $1 \le n \le 1000$
 * - $-1000 \le \text{left}_i < \text{right}_i \le 1000$
 */

class Solution {
public:
    /**
     * @brief Find the maximum length of pair chain that can be formed
     *
     * @param pairs Reference to a 2D vector where pairs[i] = [left, right]
     * @return int The maximum length of the pair chain
     */
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        if (pairs.empty()) {
            return 0;
        }

        // 1. Greedy strategy: Sort pairs by their right value (end point) in ascending order
        std::sort(pairs.begin(), pairs.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[1] < b[1];
                  });

        // 2. Traversal and greedy choice
        int count = 0;
        int curr_end = INT_MIN;

        for (const auto& pair : pairs) {
            if (curr_end < pair[0]) {
                curr_end = pair[1];
                count++;
            }
        }

        return count;
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<std::vector<int>> pairs1 = {{1, 2}, {2, 3}, {3, 4}};
    int res1 = solver.findLongestChain(pairs1);
    std::cout << "Example 1 Result: " << res1 << std::endl;

    // Test Example 2
    std::vector<std::vector<int>> pairs2 = {{1, 2}, {7, 8}, {4, 5}};
    int res2 = solver.findLongestChain(pairs2);
    std::cout << "Example 2 Result: " << res2 << std::endl;

    return 0;
}