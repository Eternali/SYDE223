#include <iostream>
#include <vector>

using namespace std;

class BSTNode {
public:
    int key;
    int data;

    BSTNode* left;
    BSTNode* right;

    BSTNode() {}
    ~BSTNode() {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
};

void _create_BST(BSTNode* parent, vector<int> A) {
    if (A.size() < 1) return;
    int middle = A.size() / 2;
    parent->key = A[middle];
    parent->left = new BSTNode();
    parent->right = new BSTNode();
    vector<int> first(A.begin(), A.begin() + middle);
    vector<int> last(A.begin() + middle + 1, A.end());
    _create_BST(parent->left, first);
    _create_BST(parent->right, last);
}

BSTNode* create_minimal_BST(vector<int> A) {
    BSTNode* root = new BSTNode();
    _create_BST(root, A);
    return root;
}

int main() {

    vector<int> A = { 0, 2, 4, 6, 8, 10, 12 };
    BSTNode* node = create_minimal_BST(A);

    return 0;
}

