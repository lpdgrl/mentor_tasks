#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <cassert>

/* 
                ### LeetCode ###
Первая очень элегантно решается через кастомные компараторы и два указателя. Можно положить в два сета (элементы слева от оси и справа от оси), дальше решение будет само писаться.

Given n points on a 2D plane, find if there is such a line parallel to the y-axis that reflects the given points symmetrically.

In other words, answer whether or not if there exists a line that after reflecting all points over the given line, the original points' set is the same as the reflected ones.

Note that there can be repeated points.

Example 1:
    Input: points = [[1,1],[-1,1]]
    Output: true
    Explanation: We can choose the line x = 0.

Example 2:
    Input: points = [[1,1],[-1,-1]]
    Output: false 
    Explanation: We can't choose a line.

Constraints:
    n == points.length
    1 <= n <= 104
    -108 <= points[i][j] <= 108

https://leetcode.com/problems/line-reflection/
*/

using Points = std::vector<std::vector<int>>;

struct Point {
    int x;
    int y;

    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

struct HashPoint {
    size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

bool isSymmetricPoints(const Points& points) {
    if (points.empty()) {
        return false;
    }

    auto min_element = *std::min_element(points.begin(), points.end(), [&](auto a, auto b) { return a[0] < b[0]; });
    auto max_element = *std::max_element(points.begin(), points.end(), [&](auto a, auto b) { return a[0] < b[0]; });
    
    int mid = min_element[0] + max_element[0];

    std::unordered_set<Point, HashPoint> set_points;

    for (const auto& point : points) {
        int x = point[0];
        int y = point[1];
        set_points.insert(Point(x, y));
    }

    for (const auto& point : set_points) {
        int x_reflection = mid - point.x;
        Point point_reflection{x_reflection, point.y};

        if (!set_points.contains(point_reflection)) {
            return false;
        }
    }

    return true;
}

void tests() {
    Points vec1{{1, 1}, {-1, 1}};
    Points vec2{{1, 1}, {-1, -1}};
    Points vec3{{1, 2}, {0, -3}, {-1, 2}, {5, 2}, {2, 0}, {4, -3}, {3, 2}};
    Points vec4{{1, 1}};
    Points vec5{{1, 1}, {2, 1}};
    Points vec6{{1, 1}, {-1, 1}, {2, 2}, {-2, 2}};
    Points vec7{{2, 3}, {4, 3}, {3, 5}, {3, 1}};
    Points vec8{{0, 0}, {2, 0}, {1, 1}, {1, -1}};
    Points vec9{{1, 1}, {3, 1}, {2, 2}};
    Points vec10{{0, 0}, {2, 0}, {1, 1}};
    Points vec11{{1, 1}, {2, 1}, {3, 2}};
    Points vec12{{0, 0}, {2, 0}, {1, 2}};
    Points vec13{{-1, 0}, {0, 1}, {1, 0}};
    Points vec14{{0, 0}, {3, 0}, {2, 1}, {1, 1}, {2, 2}};
    Points vec15{{-2, 2}, {0, 2}, {2, 2}, {0, 0}, {0, -2}};
    
    assert(isSymmetricPoints(vec1));
    assert(!isSymmetricPoints(vec2));
    assert(isSymmetricPoints(vec3));
    assert(isSymmetricPoints(vec4));
    assert(isSymmetricPoints(vec5));
    assert(isSymmetricPoints(vec6));
    assert(isSymmetricPoints(vec7));
    assert(isSymmetricPoints(vec8));
    assert(isSymmetricPoints(vec9));
    assert(isSymmetricPoints(vec10));
    assert(!isSymmetricPoints(vec11));
    assert(isSymmetricPoints(vec12));
    assert(isSymmetricPoints(vec13));
    assert(!isSymmetricPoints(vec14));
    assert(isSymmetricPoints(vec15));

}

int main() {
    
    tests();
    
    return EXIT_SUCCESS;
}