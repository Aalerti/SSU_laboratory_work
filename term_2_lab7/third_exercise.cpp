#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    int insertOrder;
    Node* left;
    Node* right;
    Node(int v, int order) : val(v), insertOrder(order), left(nullptr), right(nullptr) {}
};

struct TreeNode {
    Node* root;

    TreeNode() : root(nullptr) {}

    Node* insert(Node* root, int val, int order) {
        if (root == nullptr) return new Node(val, order);
        if (val < root->val)
            root->left = insert(root->left, val, order);
        else if (val > root->val)
            root->right = insert(root->right, val, order);
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

    Node* removeNode(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->val) {
            node->left = removeNode(node->left, key);
        } else if (key > node->val) {
            node->right = removeNode(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            if (node->left->insertOrder < node->right->insertOrder) {
                Node* maxLeft = node->left;
                while (maxLeft->right != nullptr) {
                    maxLeft = maxLeft->right;
                }
                maxLeft->right = node->right;

                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* minRight = node->right;
                while (minRight->left != nullptr) {
                    minRight = minRight->left;
                }
                minRight->left = node->left;

                Node* temp = node->right;
                delete node;
                return temp;
            }
        }
        return node;
    }

    void deleteNephews(Node* medianLeaf) {
        if (medianLeaf == nullptr) return;

        Node* parent = findParent(root, medianLeaf);
        if (parent == nullptr) {
            cout << "Average node is root. It doesn't have a parent\n";
            return;
        }

        Node* brother = nullptr;
        if (parent->left == medianLeaf) {
            brother = parent->right;
        } else {
            brother = parent->left;
        }

        if (brother == nullptr) {
            cout << "Brother doesn't exist, so nephews don't exist\n";
            return;
        }

        vector<int> nephewValues;
        if (brother->left != nullptr) nephewValues.push_back(brother->left->val);
        if (brother->right != nullptr) nephewValues.push_back(brother->right->val);

        if (nephewValues.empty()) {
            cout << "Brother doesn't have children (nephews)\n";
            return;
        }

        for (int val : nephewValues) {
            root = removeNode(root, val);
        }
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
    cout << "Enter number of nodes: ";
    cin >> n;

    TreeNode* tree = new TreeNode();
    cout << "Enter nodes: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        tree->root = tree->insert(tree->root, num, i);
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

    cout << "Leaves on level " << K << ": ";
    for (Node* l : leaves) cout << l->val << " ";
    cout << "\n";

    Node* median = tree->getMedianLeaf(leaves);
    cout << "Average leaf: " << median->val << "\n\n";

    tree->deleteNephews(median);

    cout << "After deleting nephews:\n";
    tree->printTree(K + 1);

    tree->deleteTree(tree->root);
    delete tree;
    return 0;
}