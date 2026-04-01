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

    TreeNode() : root(nullptr) {}

    Node* insert(Node* root, int val) {
        if (root == nullptr) return new Node(val);
        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        return root;
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void getLeavesAtLevel(Node* node, int level, int K, vector<Node*>& leaves) {
        if (node == nullptr) return;


        if (level == K) {
            bool isLeaf = (node->left == nullptr && node->right == nullptr);
            if (isLeaf) leaves.push_back(node);
            return;
        }

        getLeavesAtLevel(node->left,  level + 1, K, leaves);
        getLeavesAtLevel(node->right, level + 1, K, leaves);
    }

    Node* getMedianLeaf(vector<Node*>& leaves) {
        if (leaves.empty()) return nullptr;

        sort(leaves.begin(), leaves.end(), [](Node* a, Node* b) {
            return a->val < b->val;
        });


        int medianIdx = leaves.size() / 2;
        return leaves[medianIdx];
    }


    Node* findParent(Node* root, Node* target) {
        if (root == nullptr) return nullptr;

        if (root->left == target || root->right == target) return root;

        if (target->val < root->val)
            return findParent(root->left, target);
        else
            return findParent(root->right, target);
    }


    void deleteNephews(Node* medianLeaf) {
        if (medianLeaf == nullptr) return;

        Node* parent = findParent(root, medianLeaf);
        if (parent == nullptr) {
            cout << "Average node is root. It don't have parent\n";
            return;
        }

        Node* brother;
        if (parent->left == medianLeaf) {
            brother = parent->right;
        }
        else {
            brother = parent->left;
        }

        if (brother->left != nullptr) {
            deleteTree(brother->left);
            brother->left = nullptr;
        }

        if (brother->right != nullptr) {

            deleteTree(brother->right);
            brother->right = nullptr;
        }

        // Node* grandparent = findParent(root, parent);
        // if (grandparent == nullptr) {
        //     cout << "The parent of average node is root. Grandparent don't exist\n";
        //     return;
        // }
        //
        // Node* uncle = nullptr;
        // if (grandparent->left == parent)
        //     uncle = grandparent->right;
        // else
        //     uncle = grandparent->left;

        // if (uncle == nullptr) {
        //     cout << "Uncle don't exist, so nephews don't exist \n";
        //     return;
        // }
        //
        // bool hasNephews = (uncle->left != nullptr || uncle->right != nullptr);
        // if (!hasNephews) {
        //     cout << "Uncle don't have a children, so nephews don't exist\n";
        //     return;
        // }
        //
        //
        // if (uncle->left != nullptr) {
        //     deleteTree(uncle->left);
        //     uncle->left = nullptr;
        // }
        //
        // if (uncle->right != nullptr) {
        //     deleteTree(uncle->right);
        //     uncle->right = nullptr;
        // }
    }

    void printLevel(Node* node, int level, int target) {
        if (node == nullptr) return;
        if (level == target) {
            cout << node->val << " "; return;
        }
        printLevel(node->left,  level + 1, target);
        printLevel(node->right, level + 1, target);
    }

    void printTree(int maxLevel) {
        for (int i = 0; i <= maxLevel; i++) {
            cout << "  Уровень " << i << ": ";
            printLevel(root, 0, i);
            cout << "\n";
        }
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

    int K;
    cout << "Enter K >= 2: ";
    cin >> K;


    tree->printTree(K + 1);

    vector<Node*> leaves;
    tree->getLeavesAtLevel(tree->root, 0, K, leaves);

    if (leaves.empty()) {
        cout << "On level " << K << " leaves don't exist.\n";
        return 0;
    }

    for (Node* l : leaves) cout << l->val << " ";
    cout << "\n";

    Node* median = tree->getMedianLeaf(leaves);
    cout << "Average leaf: " << median->val << "\n\n";

    tree->deleteNephews(median);

    cout << "\n\n";
    tree->printTree(K + 1);

    tree->deleteTree(tree->root);
    delete tree;
    return 0;
}