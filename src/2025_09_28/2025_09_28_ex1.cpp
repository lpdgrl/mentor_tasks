#include <iostream>
#include <vector>
#include <utility>


// Написать заготовку бинарного поиска
std::pair<int, int> BinarySearch(const std::vector<int>& vec, int value) {
    int left = 0;
    int right = vec.size() - 1;
    int operations = 0;

    while (left <= right) {
        int medium = (left + right) / 2;
        ++operations;

        if (vec[medium] == value) {
            return { vec[medium], operations };
        } else if (vec[medium] < value) {
            left = medium + 1;
        }
        else {
            right = medium - 1;
        }
    }
    return {-1, operations};
}

int main() {
    std::vector<int> vec{4, 8, 9, 25};
    auto [find_num, operations] = BinarySearch(vec, 9);
    std::cout << "Find number: " << find_num << " Operations cost: " << operations << std::endl;

    return EXIT_SUCCESS;
}