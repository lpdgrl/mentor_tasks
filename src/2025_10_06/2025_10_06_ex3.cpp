#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <numeric>

int find_substr(const std::string& str, size_t k) {
    if (str.empty()) {
        return -1;
    }

    if (str.size() == k) {
        return k;
    }

    std::unordered_map<char, int> counter;

    size_t l = 0, r = 0, max = 0, old_max = 0;
    while (r < str.size()) {
        if (counter.size() <= k) {
            ++counter[str[r++]];
            ++max;
        }
        if (counter.size() > k && l <= r) {
            if (counter[str[l]] > 1) {
                --counter[str[l]];
            } else {
                counter.erase(str[l]);
            }
            ++l;
            --max;
        }
        old_max = std::max(old_max, max);
    }
    // max = std::accumulate(counter.begin(), counter.end(), 0,
    //     [](int acc, const auto& pair) { return acc + pair.second; });

    return old_max;
}

void Tests() {
    struct TestCase {
        std::string str;
        size_t k;
        int expected;
    };
    std::vector<TestCase> cases;

    cases.push_back({{"pwwkekw"}, 3, 6});
    cases.push_back({{"eceba"}, 2, 3});
    cases.push_back({{"aa"}, 1, 2});
    cases.push_back({{"aabbcc"}, 2, 4});
    cases.push_back({{"abcadcacacaca"}, 3, 11});
    cases.push_back({{"abcd"}, 4, 4});
    cases.push_back({{"abcd"}, 2, 2});

    for (const auto& case_ : cases) {
        auto [str, k, expected] = case_;

        std::cout << "Test case " << "\'" << str << "\'" << " expected: " << expected;
        auto res = find_substr(str, k);
        std::cout << " Return res: " << res << std::endl;
        bool test = expected == res;
        std::cout << (test ? "Test ok!" : "Test bad!") << std::endl;
    }
}

int main() {
    Tests();

    return EXIT_SUCCESS;
}