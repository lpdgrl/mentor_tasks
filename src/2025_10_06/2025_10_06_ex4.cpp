#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cassert>

/*
    Дана строка символов a-z, найти длину самой длинной подстроки все символы которой уникальны
*/
int find_max_length_substr(const std::string& str) {
    std::unordered_set<char> counter;

    size_t left = 0, right = 0, max = 0;
    while (right < str.size()) {
        size_t prev_position = right;
        auto [_, state_insert] = counter.insert(str[right++]);

        if (!state_insert) {
            counter.erase(str[left++]);
            right = prev_position;
        }
        max = std::max(max, counter.size());
    }
    return max;
}

void tests() {
    std::string str1{"acbaadeqwr"};
    std::string str2{"aaaaaabdacd"};
    std::string str3{"abc"};
    std::string str4{"a"};
    std::string str5{"aa"};
    std::string str6{"ad"};
    std::string str7{"abca"};
    std::string str8{"pwwkew"};
    
    assert(6 == find_max_length_substr(str1));
    assert(4 == find_max_length_substr(str2));
    assert(3 == find_max_length_substr(str3));
    assert(1 == find_max_length_substr(str4));
    assert(1 == find_max_length_substr(str5));
    assert(2 == find_max_length_substr(str6));
    assert(3 == find_max_length_substr(str7));
    assert(3 == find_max_length_substr(str8));
    
    std::string str9{"abcabcbb"};
    std::string str10{"bbbbb"};
    std::string str11{"abcdef"};
    std::string str12{"aab"};
    std::string str13{"dvdf"};
    std::string str14{"anviaj"};
    std::string str15{"tmmzuxt"};
    std::string str16{""};
    std::string str17{"abcadefgh"};
    std::string str18{"abcddefghij"};
    std::string str19{"abba"};
    std::string str20{"abcdefghijklmnopqrstuvwxyz"};
    std::string str21{"abcdabcdeabcdea"};

    assert(3 == find_max_length_substr(str9));   // "abc"
    assert(1 == find_max_length_substr(str10));  // "b"
    assert(6 == find_max_length_substr(str11));  // "abcdef"
    assert(2 == find_max_length_substr(str12));  // "ab"
    assert(3 == find_max_length_substr(str13));  // "vdf"
    assert(5 == find_max_length_substr(str14));  // "nviaj"
    assert(5 == find_max_length_substr(str15));  // "mzuxt"
    assert(0 == find_max_length_substr(str16));  // пустая строка
    assert(8 == find_max_length_substr(str17));  // "bcadefgh"
    assert(7 == find_max_length_substr(str18));  // "defghij"
    assert(2 == find_max_length_substr(str19));  // "ab" или "ba"
    assert(26 == find_max_length_substr(str20)); // все буквы уникальны
    assert(5 == find_max_length_substr(str21));  // "abcde"

}

int main() {
    tests();

    return EXIT_SUCCESS;
}