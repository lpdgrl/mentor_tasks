#include <iostream>
#include <vector>

// Написать заготовку бинарной кучи + компаратор
template <typename Comparator = std::greater<>>
class BinaryHeap {
public:
    // Инвариант кучи 
    // Значение в любой вершине не больше, чем значения её потомков 
    // или значение в любой вершине меньше, чем значения её потомков
    // У любой вершины не более двух сыновей.
    // Слои заполняются последовательно сверху вниз и слева направо, без «дырок».

    BinaryHeap() = delete;
    // Копируем вектор внутрь
    BinaryHeap(const std::vector<int>& tree) : tree_(tree) { BuildHeap(); }

    size_t HeapSize() const {
        return tree_.size();
    }

    bool Empty() const {
        return tree_.empty();
    }

    void Insert(int value) {
        tree_.push_back(value);
        SiftUp(tree_.size() - 1);
    }

    int Top() const {
        if (tree_.empty()) throw std::runtime_error("Heap is empty");
        return tree_.front();
    }

    int Remove() {
        if (tree_.empty()) throw std::runtime_error("Heap is empty");

        int top = tree_.front();
        tree_[0] = tree_.back();
        tree_.pop_back();
        if (!tree_.empty()) {
            SiftDown(0);
        }
        return top;
    }

private:
    void Heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < tree_.size() && cmp_(tree_[left], tree_[largest])) {
            largest = left;
        }
        if (right < tree_.size() && cmp_(tree_[right], tree_[largest])) {
            largest = right;
        }
        if (largest != i) {
            std::swap(tree_[i], tree_[largest]);
            Heapify(largest);
        }
    }

    void BuildHeap() {
        for (int i = tree_.size() / 2 - 1; i >= 0; --i) {
            Heapify(i);
        }
    }

    void SiftDown(int i) {
        Heapify(i);
    }
    
    void SiftUp(int i) {
        int parent = (i - 1) / 2;
        while (i > 0 && cmp_(tree_[i], tree_[parent])) {
            std::swap(tree_[i], tree_[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    Comparator cmp_;
    std::vector<int> tree_;
};

int main() {
    std::vector<int> data{3, 2, 4, 1, 5, 9};
    BinaryHeap<> heap(data); // max-heap

    std::cout << "Top: " << heap.Top() << std::endl;

    heap.Insert(10);
    std::cout << "Top after insert 10: " << heap.Top() << std::endl;

    int removed = heap.Remove();
    std::cout << "Removed top: " << removed << std::endl;
    std::cout << "New top: " << heap.Top() << std::endl;

    return EXIT_SUCCESS;
}