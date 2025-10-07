#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

/* Дан массив неотрицательных чисел, 
задача найти подмассив с суммой элементов равной k */

using PairIdx = std::pair<int, int>;

PairIdx find_subarr_sum_k(const std::vector<size_t>& v, size_t k) {
    if (v.empty()) {
        return {};
    }
    
    
    // // Calculate first sum
    // for (size_t i = 0; i < k; ++i) {
    //     sum += v[i];
    // }
    // if (sum == k) return {0, k - 1};

    // // The rest sums are calculating
    // for (size_t i = k; i < v.size(); ++i) {
    //     sum += v[i] - v[i - k];

    //     if (sum == k) {
    //         std::cout << "first index: " << i << " last index " << i - k << std::endl;
    //         return {i, i - k};
    //     }
    // }

    size_t sum = 0, left = 0, right = 0;
    sum += v[left];
    while (right < v.size() - 1) {
        if (sum < k) {
            sum += v[++right];
        }
        else if (sum > k && left <= right) {
            sum -= v[left++];
        }

        if (sum == k) {
            return {left, right};
        }
    }
   

    return {-1, -1};
}


std::ostream& operator<<(std::ostream& out, PairIdx pair) {
    return out << pair.first << " " << pair.second;
}

void Tests() {
    struct TestCase {
        std::vector<size_t> arr;
        int k;
        PairIdx expected;
    };

    std::vector<TestCase> test_cases;

    test_cases.push_back({{1, 2, 3, 4, 5, 1, 4, 3, 8}, 9, {1, 3}});
    test_cases.push_back({{1, 3, 7, 9}, 7, {2, 2}});
    test_cases.push_back({{5, 2, 3, 1, 6, 7}, 5, {0, 0}});
    test_cases.push_back({{1, 2, 3, 4, 6, 2, 1, 5, 7, 8, 9}, 10, {0, 3}});
    test_cases.push_back({{2, 4, 6, 8, 1, 2, 4}, 5, {-1, -1}}); // нет решения
    test_cases.push_back({{2, 2, 2, 2, 2, 2, 2}, 6, {0, 2}});
    test_cases.push_back({{0, 0, 0, 5, 0, 0, 0}, 5, {0, 3}});
    test_cases.push_back({{10, 1, 2, 3, 4, 5, 20, 8, 1, 2, 7}, 9, {2, 4}});

    for (const auto& test_case : test_cases) {
        auto [arr, k, expected] = test_case;
        std::cout << "Test case expected: " << expected << std::endl;
        auto res = find_subarr_sum_k(arr, k);
        bool test = expected == res;
        std::cout << (test ? "Test ok!" : "Test bad!") << std::endl;
    }
}

int main() {

    Tests();
}