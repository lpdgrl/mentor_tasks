#include <iostream>
#include <deque>

/*
Спроектируйте счётчик обращений, который считает количество хитов (hits), 
полученных за последние 5 минут (то есть за последние 300 секунд).

Система должна принимать параметр timestamp (в секундах), и можно считать, 
что вызовы происходят в хронологическом порядке (время не убывает).
Несколько обращений могут происходить в одну и ту же секунду.

https://leetcode.com/problems/design-hit-counter/description/
*/

class HitCounter {
public:
    HitCounter() = default;

    void hit(int timestamp) {
        queue_.push_back(timestamp);
    }

    int getHits(int timestamp) {
        while (!queue_.empty() && (timestamp - queue_.front()) >= INTERVAL_LAST_MESSAGES_) {
            queue_.pop_front();
        }
        return queue_.size();
    }

private:
    std::deque<int> queue_;
    const int INTERVAL_LAST_MESSAGES_ = 300; 
};

void runTests() {
    HitCounter hitCounter;

    // --- Тест 1: базовый из примера ---
    hitCounter.hit(1);
    hitCounter.hit(2);
    hitCounter.hit(3);
    std::cout << (hitCounter.getHits(4) == 3 ? "PASS" : "FAIL") << " - Test 1.1\n";

    hitCounter.hit(300);
    std::cout << (hitCounter.getHits(300) == 4 ? "PASS" : "FAIL") << " - Test 1.2\n";
    std::cout << (hitCounter.getHits(301) == 3 ? "PASS" : "FAIL") << " - Test 1.3\n";

    // --- Тест 2: все хиты в одной секунде ---
    HitCounter hc2;
    hc2.hit(1);
    hc2.hit(1);
    hc2.hit(1);
    std::cout << (hc2.getHits(1) == 3 ? "PASS" : "FAIL") << " - Test 2.1\n";
    std::cout << (hc2.getHits(301) == 0 ? "PASS" : "FAIL") << " - Test 2.2\n";

    // --- Тест 3: редкие хиты ---
    HitCounter hc3;
    hc3.hit(10);
    hc3.hit(100);
    std::cout << (hc3.getHits(300) == 2 ? "PASS" : "FAIL") << " - Test 3.1\n";
    hc3.hit(301);
    std::cout << (hc3.getHits(600) == 1 ? "PASS" : "FAIL") << " - Test 3.2\n";

    // --- Тест 4: частые вызовы ---
    HitCounter hc4;
    hc4.hit(1);
    hc4.hit(2);
    hc4.hit(3);
    hc4.hit(300);
    hc4.hit(301);
    std::cout << (hc4.getHits(301) == 4 ? "PASS" : "FAIL") << " - Test 4.1\n";

    std::cout << "All tests finished.\n";
}

int main() {

    runTests();
    return EXIT_SUCCESS;
}