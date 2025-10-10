#include <iostream>
#include <string>
#include <cassert>

// int expand_find_palindrome(const std::string& str, int left, int right) {
//     int len_palindrome = 0;
//     while (left >= 0 && right < str.size() && str[left] == str[right]) {
//         // max = right - left + 1;
//         ++len_palindrome;
//         --left;
//         ++right;
//     }

//     return len_palindrome;
// }

int count_palindrome_substrings(const std::string& str) {
    size_t count_palindrome = 0;
    size_t center = 0;

    auto expand = [&] (int left, int right) {
        while (left >= 0 && right < str.size() && str[left] == str[right]) {
            ++count_palindrome;
            --left;
            ++right;
        }
    };

    while (center < str.size()) {
        // Expanding from odd center
        expand(center, center);
        // Expanding from even center
        expand(center, center + 1);
        
        // Shifting center
        ++center;
    }
    
    return count_palindrome;
}

void tests() {
     // 1. Пустая строка
     assert(count_palindrome_substrings("") == 0);

     // 2. Один символ
     assert(count_palindrome_substrings("a") == 1);
 
     // 3. Два разных символа
     // "a", "b" → 2
     assert(count_palindrome_substrings("ab") == 2);
 
     // 4. Два одинаковых символа
     // "a", "a", "aa" → 3
     assert(count_palindrome_substrings("aa") == 3);
 
     // 5. "aba" → "a"(2), "b", "aba" → 4
     assert(count_palindrome_substrings("aba") == 4);
 
     // 6. "aaa" → "a"(3), "aa"(2), "aaa"(1) → 6
     assert(count_palindrome_substrings("aaa") == 6);
 
     // 7. "abba" → "a"(2), "b"(2), "bb", "abba" → 6
     assert(count_palindrome_substrings("abba") == 6);
 
     // 8. "abc" → "a", "b", "c" → 3
     assert(count_palindrome_substrings("abc") == 3);
 
     // 9. "abccba" → "a"(2), "b"(2), "c"(2), "cc", "bccb", "abccba" → 8
     assert(count_palindrome_substrings("abccba") == 9);
 
     // 10. "abcdedcba" → 13 палиндромов
     assert(count_palindrome_substrings("abcdedcba") == 13);
}

int main() {
    tests();
    return EXIT_SUCCESS;
}

