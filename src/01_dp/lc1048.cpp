#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @file lc1048.cpp
 * @brief LeetCode 1048. Longest String Chain
 *
 * You are given an array of words where each word consists of lowercase English letters.
 *
 * wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere
 * in wordA without changing the order of the other characters to make it equal to wordB.
 *
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1
 * is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word
 * is trivially a word chain with k == 1.
 *
 * Return the length of the longest possible word chain with words chosen from the given list of words.
 *
 * ### Examples:
 * - **Example 1:**
 *   - Input: `words = ["a","b","ba","bca","bda","bdca"]`
 *   - Output: `4`
 *   - Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
 * - **Example 2:**
 *   - Input: `words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]`
 *   - Output: `5`
 *   - Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].
 * - **Example 3:**
 *   - Input: `words = ["abcd","dbqca"]`
 *   - Output: `1`
 *   - Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
 *     ["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
 *
 * ### Constraints:
 * - $1 \le \text{words.length} \le 1000$
 * - $1 \le \text{words}[i].\text{length} \le 16$
 * - `words[i]` only consists of lowercase English letters.
 */

class Solution {
public:
    /**
     * @brief Find the length of the longest possible word chain
     *
     * @param words Reference to a vector of strings
     * @return int Length of the longest word chain
     */
    int longestStrChain(std::vector<std::string>& words) {
        if (words.empty()) {
            return 0;
        }

        // 1. Sort words in ascending by length order to process shorter words first
        std::sort(words.begin(), words.end(),
                  [](const std::string& a, const std::string& b) {
                      return a.length() < b.length();
                  });

        // 2. Hash map to store the maximum chain length ending at each word
        std::unordered_map<std::string, int> dp;
        int max_chain = 1;

        // 3. Dynamic Programming via removing one character at a time
        for (const std::string& word : words) {
            int current_best = 1;
            const std::size_t len = word.length();

            for (std::size_t i = 0; i < len; ++i) {
                // Generate predecessor candidate by deleting character at index i
                std::string prev = word.substr(0, i) + word.substr(i + 1);

                auto it = dp.find(prev);
                if (it != dp.end()) {
                    current_best = std::max(current_best, it->second + 1);
                }
            }

            dp[word] = current_best;
            max_chain = std::max(max_chain, current_best);
        }

        return max_chain;
    }
};

int main() {
    Solution solver;

    // Test Example 1
    std::vector<std::string> words1 = {"a", "b", "ba", "bca", "bda", "bdca"};
    int res1 = solver.longestStrChain(words1);
    std::cout << "Example 1 Result: " << res1 << std::endl;

    // Test Example 2
    std::vector<std::string> words2 = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
    int res2 = solver.longestStrChain(words2);
    std::cout << "Example 2 Result: " << res2 << std::endl;

    // Test Example 3
    std::vector<std::string> words3 = {"abcd", "dbqca"};
    int res3 = solver.longestStrChain(words3);
    std::cout << "Example 3 Result: " << res3 << std::endl;

    return 0;
}