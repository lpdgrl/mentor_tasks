#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <ranges>

int main() {
    auto print = [](const auto& n) { std::cout << ' ' << n;};

    std::vector<int> origin_vec(20);
    std::iota(origin_vec.begin(), origin_vec.end(), (rand() % 50));

    std::cout << "Filling vector: ";
    std::ranges::for_each(origin_vec.begin(), origin_vec.end(), print);
    std::cout << std::endl;

    std::unordered_set<int> even_set;
    std::copy_if(origin_vec.begin(), origin_vec.end(), std::inserter(even_set, even_set.end()), [](int element) { return (element % 2) != 0; });

    std::cout << "Unordered set: ";
    std::ranges::for_each(even_set.begin(), even_set.end(), print);
    std::cout << std::endl;

    size_t k = 15;
    std::sort(origin_vec.begin(), origin_vec.end(), std::greater<int>());
    origin_vec.erase(origin_vec.begin() + k, origin_vec.end());

    std::cout << "Vector after deleted: ";
    std::ranges::for_each(origin_vec.begin(), origin_vec.end(), print);
    std::cout << std::endl;

    std::vector<int> vec_n;

    std::transform(origin_vec.cbegin(), origin_vec.cbegin() + k, std::move(std::back_inserter(vec_n)), [](int x) { return x * rand(); });
    std::sort(vec_n.begin(), vec_n.end());

    std::cout << "New vector: ";
    std::ranges::for_each(vec_n.begin(), vec_n.end(), print);
    std::cout << std::endl;

    return 0;
}