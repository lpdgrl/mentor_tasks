#include <iostream>
#include <bitset>
#include <cassert>

// setNthBit - функция, которая принимает uint64 и ставит n-ый бит в значение x
uint64_t set_nth_bit(uint64_t num, uint64_t n, bool x);

// template <typename T, typename B>
// void print_bit();

int main() {
    using bin64 = std::bitset<64>;
    {    
        uint64_t num = 1000000;
        uint64_t answer = 999936;
        assert(set_nth_bit(num, 6, 0) == answer);
    }

    {    
        uint64_t num = 10;
        uint64_t answer = 5;
        num = set_nth_bit(num, 1, 0);
        num = set_nth_bit(num, 3, 0);
        num = set_nth_bit(num, 2, 1);
        num = set_nth_bit(num, 0, 1);
        assert(num == answer);
    }

    {    
        uint64_t num = 0;
        uint64_t answer = UINT64_MAX;
        for (size_t i = 0; i < 64; ++i) num = set_nth_bit(num, i, 1);
        assert(num == answer);
    }

    {
        uint64_t num = 1;
        uint64_t answer = 4;
        num = set_nth_bit(num, 0, 0);
        num = set_nth_bit(num, 2, 1);
        assert(num == answer);
    }

    {
        // Assert trigger inside set_nth_bit
        set_nth_bit(1, -1, 1);
    }

    return EXIT_SUCCESS;
}


uint64_t set_nth_bit(uint64_t num, uint64_t n, bool x) {
    assert(!(n >= 64));
    return x ? (num | (1ull << n)) : (num & ~(1ull << n));
}
