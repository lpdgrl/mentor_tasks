#include <string>
#include <iostream>


void RemoveZeros(std::string& str) {
    if (str.empty()) {
        return;
    }

    size_t count_zeros = 0;

    for (auto read = str.begin(), write = str.begin(); write != str.end(); ++write) {
        if (*read != '0') {
            ++read;
        }
        else if (*read == '0' && *write != '0') {
            std::swap(*read, *write);
            ++read;
        }
        else {
            ++count_zeros;
        }
        
    }

    std::cout << "Count: " << count_zeros << " Size: " << str.size() << " Capacity: " << str.capacity() << std::endl;
    if (count_zeros > 0) {
        str.resize(str.size() - count_zeros);
    }
    std::cout << "Count: " << count_zeros << " Resize: " << str.size() << " Capacity: " << str.capacity() << std::endl;
}

void Tests() {
    std::string str("105230601 20301203120");
    std::string str1("0012312300");
    std::string str_zero("000");
    std::string str_zero_one("01");
    std::string str_one("1");

    std::cout << "Source str: " << str << std::endl;
    RemoveZeros(str);
    std::cout << "After remove zeros: " << str << std::endl;

    std::cout << "Source str: " << str1 << std::endl;
    RemoveZeros(str1);
    std::cout << "After remove zeros: " << str1 << std::endl;

    std::cout << "Source str: " << str_zero << std::endl;
    RemoveZeros(str_zero);
    std::cout << "After remove zeros: " << str_zero << std::endl;

    std::cout << "Source str: " << str_zero_one << std::endl;
    RemoveZeros(str_zero_one);
    std::cout << "After remove zeros: " << str_zero_one << std::endl;

    std::cout << "Source str: " << str_one << std::endl;
    RemoveZeros(str_one);
    std::cout << "After remove zeros: " << str_one << std::endl;
}

int main() {
    
    Tests();

    return EXIT_SUCCESS;
}