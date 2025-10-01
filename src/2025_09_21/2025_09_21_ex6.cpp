#include <iostream>
#include <cassert>
#include <memory>

struct BinaryTree {
    BinaryTree(int val) : data{val} {}

    int data;
    std::unique_ptr<BinaryTree> left;
    std::unique_ptr<BinaryTree> right;
};

void FillBinaryTree(BinaryTree* root) {
    // Fill left under tree
    root->left = std::make_unique<BinaryTree>(4);
    root->left->left = std::make_unique<BinaryTree>(2);

    root->left->right = std::make_unique<BinaryTree>(5);
    root->left->right->right = std::make_unique<BinaryTree>(7);
    root->left->left->right = std::make_unique<BinaryTree>(3);

    // Fill right under tree
    root->right = std::make_unique<BinaryTree>(12);
    root->right->right = std::make_unique<BinaryTree>(14);
    root->right->left = std::make_unique<BinaryTree>(9);
    root->right->left->right = std::make_unique<BinaryTree>(10);

      // Tree is has view 
    /*             8
                  /  \
                 4    12
                / \   /  \
               2   5  9   14
                \   \  \
                 3   7  10
    */
}

int FindNhtHighest(BinaryTree* root, int& n) {
    if (root == nullptr) {
        return -1;
    }

    int left_res = FindNhtHighest(root->left.get(), n);
    if (left_res != -1) {
        return left_res;
    }

    n--;

    if (n == 0) {
        return root->data;
    }
 
    return FindNhtHighest(root->right.get(), n);
}

int main() {

    std::unique_ptr<BinaryTree> root = std::make_unique<BinaryTree>(8);

     // Create balanced tree
    FillBinaryTree(root.get());
    int n = 1;
    // std::cout << "n = 1, res = " << FindNhtHighest(root.get(), n) << std::endl;
    n = 3;
    std::cout << "n = 3, res = " << FindNhtHighest(root.get(), n) << std::endl;
    n = 8;
    std::cout << "n = 8, res = " << FindNhtHighest(root.get(), n) << std::endl;
    n = 0;
    std::cout << "n = 0, res = " << FindNhtHighest(root.get(), n) << std::endl;;
    return 0;
}