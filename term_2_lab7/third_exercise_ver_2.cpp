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

    Node* insert(Node* node, int val, int order) {
        if (node == nullptr) return new Node(val, order);
        if (val < node->val)
            node->left = insert(node->left, val, order);
        else if (val > node->val)
            node->right = insert(node->right, val, order);
        return node;
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

    Node* findParent(Node* node, Node* target) {
        if (node == nullptr) return nullptr;
        if (node->left == target || node->right == target) return node;

        if (target->val < node->val)
            return findParent(node->left, target);
        else
            return findParent(node->right, target);
    }

    void collectAndFreeElements(Node* node, vector<pair<int, int>>& elements) {
        if (node == nullptr) return;
        elements.push_back({node->val, node->insertOrder});
        collectAndFreeElements(node->left, elements);
        collectAndFreeElements(node->right, elements);
        delete node;
    }

    Node* removeNodeCustom(Node* root_node, int key) {
        if (root_node == nullptr) return nullptr;

        Node* parent = nullptr;
        Node* curr = root_node;

        while (curr != nullptr && curr->val != key) {
            parent = curr;
            if (key < curr->val) curr = curr->left;
            else curr = curr->right;
        }

        if (curr == nullptr) return root_node;

        vector<pair<int, int>> descendants;
        collectAndFreeElements(curr->left, descendants);
        collectAndFreeElements(curr->right, descendants);

        if (parent == nullptr) {
            root_node = nullptr;
        } else {
            if (parent->left == curr) parent->left = nullptr;
            else parent->right = nullptr;
        }

        delete curr;

        sort(descendants.begin(), descendants.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        for (const auto& el : descendants) {
            root_node = insert(root_node, el.first, el.second);
        }

        return root_node;
    }

    void deleteNephews(Node* medianLeaf) {
        if (medianLeaf == nullptr) return;

        Node* parent = findParent(root, medianLeaf);
        if (parent == nullptr) {
            cout << "Median node is root, it has no parent\n";
            return;
        }

        Node* brother = nullptr;
        if (parent->left == medianLeaf) {
            brother = parent->right;
        } else {
            brother = parent->left;
        }

        if (brother == nullptr) {
            cout << "Parent has no sibling, hence no nephews\n";
            return;
        }

        vector<int> nephewValues;
        if (brother->left != nullptr) nephewValues.push_back(brother->left->val);
        if (brother->right != nullptr) nephewValues.push_back(brother->right->val);

        if (nephewValues.empty()) {
            cout << "Sibling has no children (no nephews)\n";
            return;
        }

        for (int val : nephewValues) {
            root = removeNodeCustom(root, val);
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
            cout << "  Level " << i << ": ";
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

    cout << "\nInitial tree:\n";
    tree->printTree(K + 1);

    vector<Node*> leaves;
    tree->getLeavesAtLevel(tree->root, 0, K, leaves);

    if (leaves.empty()) {
        cout << "No leaves on level " << K << ".\n";
        tree->deleteTree(tree->root);
        delete tree;
        return 0;
    }

    cout << "Leaves on level " << K << ": ";
    for (Node* l : leaves) cout << l->val << " ";
    cout << "\n";

    Node* median = tree->getMedianLeaf(leaves);
    cout << "Median leaf: " << median->val << "\n\n";

    tree->deleteNephews(median);

    cout << "Tree after deleting nephews:\n";
    tree->printTree(K + 1);

    tree->deleteTree(tree->root);
    delete tree;
    return 0;
}