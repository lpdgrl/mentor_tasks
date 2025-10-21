#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_map>

/* 

            ### LeetCode ###
15.3Sum 
https://leetcode.com/problems/3sum/description/ 
Medium

Given an integer array nums, return all the triplets 
[nums[i], nums[j], nums[k]] such that i != j, i != k, 
and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

*/

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());

    size_t n = nums.size();
    
    size_t base = 0, left = 0, right = 0;

    for (size_t base = 0; base < n; ++base) {
        if (base > 0 && nums[base] == nums[base - 1]) {
            continue;
        }

        left = base + 1;
        right = n - 1;

        int target = -nums[base];
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                result.push_back({nums[base], nums[left], nums[right]});
                ++left;
                --right;

                while (left < right && nums[left] == nums[left - 1]) {
                    ++left;
                }

                while (left < right && nums[right] == nums[right + 1]) {
                    --right;
                }
            }
            else if (nums[left] + nums[right] < target) {
                ++left;
            }
            else {
                --right;
            }
        }
    }

    return result;
}

void tests() {
    std::vector<int> vec1{-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> answer1{std::vector<int>{-1, -1, 2}, std::vector<int>{-1, 0, 1}};
    assert(threeSum(vec1) == answer1);

    std::vector<int> vec2{0, 1, 1};
    std::vector<std::vector<int>> answer2;
    assert(threeSum(vec2) == answer2);

    std::vector<int> vec3{0, 0, 0};
    std::vector<std::vector<int>> answer3{std::vector<int>{0, 0, 0}};
    assert(threeSum(vec3) == answer3);

    std::vector<int> vec4{0,0,0,0};
    std::vector<std::vector<int>> asnwer4{std::vector<int>{0,0,0}};
    assert(threeSum(vec4) == asnwer4);

}

int main() {

    tests();
    return EXIT_SUCCESS;
}