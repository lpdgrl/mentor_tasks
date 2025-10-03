#include <iostream>
#include <vector>
#include <cassert>
#include <map>

std::map<int, int> Histogram(const std::vector<int>& v) {
    std::map<int, int> hist;
    size_t sz_v = v.size() - 1;

    if (v.empty()) {
        hist;
    }

    if (v[0] == v[sz_v]) {
        hist[v[0]] = v.size();
        return hist;
    }

    int first = 0; int last = sz_v / 2;
    while (first <= last) {
        if (v[first] != v[last]) {
            last = (last + first) / 2;
        }
        else if (v[first] == v[last]) {
            size_t len = last - first + 1;
            hist[v[first]] += len;
            first += len;
            last = sz_v;
        }
    }

    return hist;
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    assert((std::map<int, int>{{1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}}) == Histogram(v));
    
    std::vector<int> v1{1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3};
    assert((std::map<int, int>{{1, 4}, {2, 3}, {3, 6}}) == Histogram(v1));

    std::vector<int> v2{1, 2, 2};
    assert((std::map<int, int>{{1, 1}, {2, 2}}) == Histogram(v2));

    std::vector<int> v3{4, 4, 5};
    assert((std::map<int, int>{{4, 2}, {5, 1}}) == Histogram(v3));

    std::vector<int> v4{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4};
    assert((std::map<int, int>{{1, 5}, {2, 6}, {3, 6}, {4, 6}}) == Histogram(v4));

    std::vector<int> v5{1};
    assert((std::map<int, int>{{1, 1}}) == Histogram(v5));

    return EXIT_SUCCESS;
}