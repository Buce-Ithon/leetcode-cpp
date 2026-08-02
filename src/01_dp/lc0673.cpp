#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @file lc0673.cpp
 * @brief LeetCode 673. Number of Longest Increasing Subsequence
 *
 * Given an integer array nums, return the number of longest increasing subsequences.
 *
 * Notice that the sequence has to be strictly increasing.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `nums = [1,3,5,4,7]`
 *   - Output: `2`
 *   - Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
 * - **Example 2:**
 *   - Input: `nums = [2,2,2,2,2]`
 *   - Output: `5`
 *   - Explanation: The length of the longest increasing subsequence is 1, and there are 5
 *     increasing subsequences of length 1, so output 5.
 *
 * ### Constraints:
 * - $1 \le \text{nums.length} \le 2000$
 * - $-10^6 \le \text{nums}[i] \le 10^6$
 * - The answer is guaranteed to fit inside a 32-bit integer.
 */

class Solution {
public:
    /**
     * @brief Find the number of longest increasing subsequences
     *
     * @param nums Reference to a vector of integers
     * @return int The total count of longest increasing subsequences
     */
    int findNumberOfLIS(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        const std::size_t n = nums.size();
        // length[i]: length of the longest increasing subsequence ending at nums[i]
        std::vector<int> length(n, 1);
        // count[i]: number of longest increasing subsequences ending at nums[i]
        std::vector<int> count(n, 1);

        int max_len = 1;

        // Dynamic Programming state transitions
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j]; // Reset count to the number of paths from j
                    } else if (length[j] + 1 == length[i]) {
                        count[i] += count[j]; // Accumulate additional paths of the same max length
                    }
                }
            }
            max_len = std::max(max_len, length[i]);
        }

        // Sum up the counts of all subsequences that achieve the maximum length
        int result = 0;
        for (std::size_t i = 0; i < n; ++i) {
            if (length[i] == max_len) {
                result += count[i];
            }
        }

        return result;
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<int> nums1 = {1, 3, 5, 4, 7};
    int res1 = solver.findNumberOfLIS(nums1);
    std::cout << "Example 1 Result: " << res1 << std::endl;

    // Test Example 2
    std::vector<int> nums2 = {2, 2, 2, 2, 2};
    int res2 = solver.findNumberOfLIS(nums2);
    std::cout << "Example 2 Result: " << res2 << std::endl;

    return 0;
}