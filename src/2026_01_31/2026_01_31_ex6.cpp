#include <memory>
#include <iostream>
#include <cassert>
#include <format>
#include <cstring>
#include <print>

// Отличие memcpy от memmove? Как написать свой memcpy? А memmove?

// memcpy копирует без учета перекрытия (overlap) памяти и поэтому можно затереть объект. 
// memmove копирует из source в временный буфер и только затем в dest
struct Point {
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Size {
    short x = 0;
    short y = 0;
};

void _memcpy(void* dest, const void* source, std::size_t count) {
    // This is works only LP64 because long equal 8 bytes in this model
    if (uintptr_t(dest) % sizeof(long) == 0 && uintptr_t(source) % sizeof(long) == 0 && count % sizeof(long) == 0) {
        long* d = static_cast<long*>(dest);
        const long* s = static_cast<const long*>(source);

        for (long i = 0; i < sizeof(long) / 2; ++i) {
            d[i] = s[i];
        }
    } else {
        unsigned char* d = reinterpret_cast<unsigned char*>(dest);
        const unsigned char* s = reinterpret_cast<const unsigned char*>(source);

        // побайтово копируем, что неэффективно
        while(count--) {
            *d++ = *s++;
        }
    }
}

// This implementation memmove is not effective!!!
void _memmove(void* dest, const void* source, std::size_t count) {
    unsigned char* d = static_cast<unsigned char*>(dest);
    const unsigned char* s = static_cast<const unsigned char*>(source);

    unsigned char buffer[count];
    
    _memcpy(&buffer, &source, count);
    _memcpy(d, &buffer, count);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // Coping is structs on stack
    Point a{.x = 16.3, .y = 16.5, .z = 25.34};
    Point a_copy;
    Point std_a_copy;

    _memcpy(&a_copy, &a, sizeof(a));
    std::memcpy(&std_a_copy, &a, sizeof(a));
    
    assert(a.x == std_a_copy.x && a.y == std_a_copy.y && a.z == std_a_copy.z);
    assert(a.x == a_copy.x && a.y == a_copy.y && a.z == a_copy.z);

    Size sz{.x = 10, .y = 50};
    Size sz_copy;
    Size std_sz_copy;

    _memcpy(&sz_copy, &sz, sizeof(sz));
    std::memcpy(&std_sz_copy,  &sz, sizeof(sz));

    assert(sz.x == sz_copy.x && sz.y == sz_copy.y);
    assert(sz.x == std_sz_copy.x && sz.y == std_sz_copy.y);

    // Coping is array on stack
    int ch_arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::println("Original ch_arr {}", ch_arr);

    int ch_arr_n[10]{};
    std::println("New arr: {}", ch_arr_n);

    _memmove(ch_arr_n, ch_arr, sizeof(ch_arr));
    std::println("New arr changed: {}", ch_arr);

    char buffer[] = "hello";
    char n_buffer[sizeof(buffer)];

    _memmove(n_buffer, buffer, sizeof(buffer));
    std::println("Changed buffer: {}", buffer);
    
    
    return EXIT_SUCCESS;
}