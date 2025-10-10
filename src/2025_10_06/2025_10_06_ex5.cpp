#include <iostream>
#include <string>
#include <cassert>
#include <string_view>
#include <ranges>

bool is_spec_ch(char c) {
    static constexpr std::string_view specs = ":;<=>?!\"$%&'()*+-,./ ";
    return specs.find(c) != std::string_view::npos;
}

bool is_palindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }

    // Just new str from filtered ranges. This feature is new to me :)
    std::string str_ = str
                       | std::ranges::views::filter([](char ch) { return !is_spec_ch(ch); })
                       | std::ranges::to<std::string>();

    int center = str_.size() / 2;
    bool odd = (str_.size() % 2) != 0 ? true : false;
    int left = odd ? center : center - 1;
    int right = center;

    while (left >= 0 && right < str.size()) {
        if (std::tolower(str_[left--]) != std::tolower(str_[right++])) {
            return false;
        }
    }

    return true;
}

void tests() {
    // Простые положительные случаи
    assert(is_palindrome("mom"));
    assert(is_palindrome("dad"));
    assert(is_palindrome("level"));
    assert(is_palindrome("a"));
    assert(is_palindrome("aa"));
    assert(is_palindrome("aabaa"));
  
    // Простые отрицательные случаи
    assert(!is_palindrome("ab"));
    assert(!is_palindrome("hello"));
    assert(!is_palindrome("aab"));
    assert(!is_palindrome("palindrome"));

    // Смешанный регистр
    assert(is_palindrome("Taco cat"));
    assert(is_palindrome("Noon"));
    assert(is_palindrome("MadAm"));
    assert(is_palindrome("RaceCar"));

    // С пробелами и пунктуацией
    // amanaplanacanalpanama
    assert(is_palindrome("A man, a plan, a canal: Panama"));
    assert(is_palindrome("Go deliver a dare vile dog"));
    assert(!is_palindrome("race a car"));
    assert(is_palindrome("'Never odd or even'"));
    assert(is_palindrome("Was it a car or a cat I saw?"));
    assert(is_palindrome("Murder for a jar of red rum!"));

    // С числами и символами
    assert(is_palindrome("12321"));
    assert(!is_palindrome("123421"));
    assert(is_palindrome("1a2b2a1"));
}


int main() {
    tests();
    return EXIT_SUCCESS;
}