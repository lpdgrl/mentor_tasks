#include <iostream>
#include <deque>
#include <unordered_map>
#include <ranges>
#include <algorithm>

/*
Спроектируйте счётчик обращений, который считает количество хитов (hits), 
полученных за последние 5 минут (то есть за последние 300 секунд).

Система должна принимать параметр timestamp (в секундах), и можно считать, 
что вызовы происходят в хронологическом порядке (время не убывает).
Несколько обращений могут происходить в одну и ту же секунду.

С каждым хитом приходит user_id. 
То есть мы знаем не только в какой момент произошел хит, но и какой юзер его сделал. 
И нам надо вернуть количество юзеров, которые за последние 5 минут сделали больше 5000 запросов. 

https://leetcode.com/problems/design-hit-counter/description/
*/

struct UserHit {
    int timestamp = 0;
    size_t user_id = 0;
};

struct TotalHits {
    int total_hits = 0;
};

class HitCounter {
public:
    HitCounter() = default;

    void hit(size_t user_id, int timestamp) {
        cleanup(timestamp);
    
        // добавляем новый блок
        queue_.push_back({timestamp, user_id});
        user_hit_counts_[user_id]++;

        if (user_hit_counts_[user_id] >= kCountLastUserRequests) {
            number_heavy_users_[user_id] = 1;
        }
    }

    int getHits(int timestamp) {
        cleanup(timestamp);

        return number_heavy_users_.size();
    }

private:
void cleanup(int timestamp) {
    while (!queue_.empty() && (queue_.front().timestamp) <= timestamp - kIntervalLastMessages) {
        auto& front_block = queue_.front();
        size_t dq_user = front_block.user_id;

        if (auto it_user = user_hit_counts_.find(dq_user); it_user != user_hit_counts_.end()) {
            it_user->second -= front_block.timestamp;
            if (it_user->second < 5000) {
                number_heavy_users_.erase(dq_user);
            }
            if (it_user->second <= 0) {
                user_hit_counts_.erase(it_user);
            }
        }

        queue_.pop_front();
    }
}

private:
    std::unordered_map<size_t, int> user_hit_counts_;
    std::deque<UserHit> queue_;
    std::unordered_map<size_t, int> number_heavy_users_;
    const int kIntervalLastMessages = 300;
    const int kCountLastUserRequests = 5000;
    const int kOneRequest = 1;
};

void runTests() {
    // --- Тест 1 ---
    {
        HitCounter hitCounter;
        for (int i = 0; i < 5001; ++i) hitCounter.hit(1, 1);
        std::cout << (hitCounter.getHits(300) == 1 ? "PASS" : "FAIL") << " - Test 1.1\n";

        hitCounter.hit(2, 100);
        hitCounter.hit(2, 200);
        std::cout << (hitCounter.getHits(300) == 1 ? "PASS" : "FAIL") << " - Test 1.2\n";
    }

    // --- Тест 2 ---
    {
        HitCounter hitCounter;
        for (int i = 0; i < 5001; ++i) { hitCounter.hit(1, 1); hitCounter.hit(2, 1); }
        std::cout << (hitCounter.getHits(300) == 2 ? "PASS" : "FAIL") << " - Test 2.1\n";

        hitCounter.hit(3, 10);
        std::cout << (hitCounter.getHits(300) == 2 ? "PASS" : "FAIL") << " - Test 2.2\n";
    }

    // --- Тест 3 ---
    {
        HitCounter hitCounter;
        for (int i = 0; i < 5001; ++i) hitCounter.hit(1, 1);
        std::cout << (hitCounter.getHits(300) == 1 ? "PASS" : "FAIL") << " - Test 3.1\n";
        std::cout << (hitCounter.getHits(5301) == 0 ? "PASS" : "FAIL") << " - Test 3.2\n";
    }

    // --- Тест 4 ---
    {
        HitCounter hitCounter;
        for (int i = 0; i < 4999; ++i) hitCounter.hit(42, 1);
        std::cout << (hitCounter.getHits(300) == 0 ? "PASS" : "FAIL") << " - Test 4.1\n";

        hitCounter.hit(42, 1);  // 5000-й хит
        std::cout << (hitCounter.getHits(300) == 1 ? "PASS" : "FAIL") << " - Test 4.2\n";
    }

    // --- Тест 5 ---
    {
        HitCounter hitCounter;
        // user 1: все хиты в окне
        for (int i = 0; i < 5000; ++i) hitCounter.hit(1, 1);

        // user 2: часть старых, часть свежих
        for (int i = 0; i < 2500; ++i) hitCounter.hit(2, 100);
        for (int i = 0; i < 2500; ++i) hitCounter.hit(2, 300);

        std::cout << (hitCounter.getHits(400) == 2 ? "PASS" : "FAIL") << " - Test 5.1\n";
        std::cout << (hitCounter.getHits(701) == 1 ? "PASS" : "FAIL") << " - Test 5.2\n";
    }

    // --- Тест 6 ---
    {
        HitCounter hitCounter;
        for (int i = 0; i < 4999; ++i) hitCounter.hit(7, 100);
        std::cout << (hitCounter.getHits(400) == 0 ? "PASS" : "FAIL") << " - Test 6.1\n";

        hitCounter.hit(7, 401); // становится ≥5000
        std::cout << (hitCounter.getHits(401) == 1 ? "PASS" : "FAIL") << " - Test 6.2\n";
    }
}


int main() {

    runTests();
    return EXIT_SUCCESS;
}