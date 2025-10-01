#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

/*
    658. Find K Closest Elements
    Given a sorted integer array arr, two integers k and x, 
    return the k closest integers to x in the array. 
    The result should also be sorted in ascending order.
    link: https://leetcode.com/problems/find-k-closest-elements
*/

std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
    // |a - x| < |b < x| 
    //          or
    // |a - x| == |b - x| && a < b

    if (k == arr.size()) {
       return arr;
    }

    std::vector<int> res;


    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int medium = (left + right) / 2;

        if (arr[medium] < x) {
            left = medium + 1;
        }
        else {
            right = medium - 1;
        }
    }

    int L = left - 1;
    int R = left;
    while (k > 0) {
        if (R == arr.size()) {
            res.push_back(arr[L--]);
            --k;
        }
        else if ((L >= 0) && (R < arr.size()) && std::abs(arr[L] - x) <= std::abs(arr[R] - x)) {
            res.push_back(arr[L--]);
            --k;
        }
        else if (R < arr.size()) {
            res.push_back(arr[R++]);
            --k;
        }
    }
    std::sort(res.begin(), res.end());

    return res;
}

void Tests() {
    std::vector<int> vec_simple{1, 2, 3, 4, 5};
    std::vector<int> expected_vec_simple{1, 2, 3, 4};
    assert(findClosestElements(vec_simple, 4, 3) == expected_vec_simple);

    std::vector<int> vec_two_num_in_begin{1, 1, 2, 3, 4, 5};
    std::vector<int> expected_vec_two_num_in_begin{1, 1, 2, 3};
    assert(findClosestElements(vec_two_num_in_begin, 4, -1) == expected_vec_two_num_in_begin);

    std::vector<int> vec_one_num{1};
    assert(findClosestElements(vec_one_num, 1, 1) == vec_one_num);

    std::vector<int> vec1{3, 5, 8, 10};
    std::vector<int> expected_vec1{3, 5, 8, 10};
    assert(findClosestElements(vec1, 4, 10) == vec1);

    std::vector<int> vec2{0, 1, 2, 2, 2, 3, 6, 8, 8, 9};
    std::vector<int> expected_vec2{3, 6, 8, 8, 9};
    assert(findClosestElements(vec2, 5, 9) == expected_vec2);
}

int main() {
    Tests();

    return EXIT_SUCCESS;
}