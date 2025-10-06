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

    size_t left = 0;
    size_t right = 0;
    size_t sum = v[left];
    while (left <= right) {
        if (sum == k) {
            return {left, right};
        }

        if (sum < k) {
            sum += v[++right];
        }    
        else if (sum > k) {
            sum -= v[left++];
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

    // test_cases.push_back({{1, 2, 3, 4, 5}, 9, {1, 3}});
    // test_cases.push_back({{1, 3, 7, 9, 10}, 7, {2, 2}});
    // test_cases.push_back({{5, 2, 3, 1}, 5, {0, 0}});
    // test_cases.push_back({{1, 2, 3, 4, 6}, 10, {0, 3}});
    test_cases.push_back({{2, 4, 6, 8}, 5, {-1, -1}}); // нет решения
    test_cases.push_back({{2, 2, 2, 2, 2}, 6, {0, 2}});
    test_cases.push_back({{0, 0, 0, 5, 0}, 5, {3, 3}});
    test_cases.push_back({{10, 1, 2, 3, 4, 5, 20}, 9, {2, 4}});

    for (const auto& test_case : test_cases) {
        auto [arr, k, expected] = test_case;
        std::cout << "Test case expected: " << expected << std::endl;
        assert(expected == find_subarr_sum_k(arr, k));
        std::cout << "Test ok!" << std::endl;
    }
}

int main() {

    Tests();
}