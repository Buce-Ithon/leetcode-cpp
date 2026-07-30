#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Solution {
public:
		int lengthOfLIS(std::vector<int>& nums) {
				int n = static_cast<int>(nums.size());

				std::vector<int>LIS(n, 1);

				for (auto i=0; i<n; i++) {
						for (auto j=0; j<i; j++) {
								if (nums[j] < nums[i]) {
										LIS[i] = std::max(1 + LIS[j], LIS[i]);
								}
						}
				}
				int sol = 0;
				for (auto k=0; k<n; k++) {
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
