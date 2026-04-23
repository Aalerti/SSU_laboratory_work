#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

struct TreeNode {
    Node* root;

    TreeNode(): root(nullptr) {}

    TreeNode(int val): root(new Node(val)) {}

    Node* insert(Node* root, int val) {
        if (root == nullptr) return new Node(val);

        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);

        return root;
    }

    Node* search(Node* root, int val) {
        if (root == nullptr) return nullptr;

        if (val == root->val) return root;

        if (val < root->val) {
            return search(root->left, val);
        }
        else {
            return search(root->right, val);
        }
    }

    int height(Node* node) {
        if (node == nullptr) return -1;

        int leftH  = height(node->left);
        int rightH = height(node->right);
        return max(leftH, rightH) + 1;
    }

    void deleteTree(Node* root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }


    int sumLeaves(Node* root) {
        if (root == nullptr) return 0;
        if (isLeaf(root)) return root->val;

        return sumLeaves(root->left) + sumLeaves(root->right);
    }

private:
    bool isLeaf(Node* node) {
        return  (node->left == nullptr && node->right == nullptr) ;
    }
};


int main() {
    int n;
    cin >> n;

    TreeNode* tree = new TreeNode();
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        tree->root = tree->insert(tree->root, num);
    }

    cout << tree->sumLeaves(tree->root);
    
    tree->deleteTree(tree->root);
    delete tree;

    return 0;
}


