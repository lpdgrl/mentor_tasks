#include <iostream>
#include <unordered_set>
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

bool isSymmetricPoints(const Points& points) {
    if (points.empty()) {
        return false;
    }

}

int main() {
    
    Points vec1{{1, 1}, {-1, 1}};
    Points vec2{{1, 1}, {-1, -1}};

    assert(isSymmetricPoints(vec1));
    assert(!isSymmetricPoints(vec2));

    return EXIT_SUCCESS;
}