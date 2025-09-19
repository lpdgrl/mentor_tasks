#include <iostream>
#include <string>
#include <vector>

template <typename It>
struct SeqIter {
public:
    SeqIter(It begin, It end) : begin_{begin}, end_{end} {}

    It begin() const { return begin_; }
    It end()  const  { return end_; }

private:
    It begin_;
    It end_;
};

template <typename It>
// Можно вернуть pair двух итераторов или сделать класс у которого будут методы begin и end 
std::vector<SeqIter<It>> Split(It beg, It end) {
    std::vector<SeqIter<It>> res;

    // linear complexity 
    for(auto old_beg = beg; beg != end; ++beg) {
        if (*beg == ' ') {
            res.push_back({old_beg, beg});
            old_beg = beg + 1;
        }
        else if ((beg + 1) == end) {
            res.push_back({old_beg, beg + 1});
        }
    }

    return res;
}

template <typename Container>
void PrintResult(const Container& c) {
    std::cout << "Результат: ";
    for (const auto& el : c) {
        std::string word{el.begin(), el.end()};
        std::cout << word  << " ";;
    }
    std::cout << std::endl;
}

void Tests() {
    std::string rus_line("Скопировать нечетные элементы из вектора в котором изначально 20 элементов в unordered_set,"
        " удалить все после 15 элемента по величине, оставшиеся вставить в новый вектор, прибавив случайное число, новый вектор отсортировать по убыванию.");
    
    const auto rus_words = Split(rus_line.begin(), rus_line.end());

    PrintResult(rus_words);

    std::string foo("hello, world, and one more time hello! ");
    auto foo_vec = Split(foo.begin(), foo.end());
    
    PrintResult(foo_vec);
}

int main() {
    
    Tests();

    return 0;
}