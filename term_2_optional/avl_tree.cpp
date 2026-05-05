#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVL_Tree {

    Node* root;

    int height(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return n->height;
    }

    int get_balance(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return height(n->left) - height(n->right);
    }

    Node* new_node(int key) {
        Node* node = new Node();
        node->key = key;

        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;

        return node;
    }

    Node* right_rotate(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* left_rotate(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* help_for_insert(Node* node, int key) {
        if (node == nullptr) {
            return new_node(key);
        }

        if (key < node->key) {
            node->left = help_for_insert(node->left, key);
        } else if (key > node->key) {
            node->right = help_for_insert(node->right, key);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = get_balance(node);

        if (balance > 1 && key < node->left->key) {
            return right_rotate(node);
        }

        if (balance < -1 && key > node->right->key) {
            return left_rotate(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        return node;
    }

    Node* min_val_node(Node* node) {
        Node* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    Node* delete_node_helper(Node* root, int key) {
        if (root == nullptr) {
            return root;
        }

        if (key < root->key) {
            root->left = delete_node_helper(root->left, key);
        } else if (key > root->key) {
            root->right = delete_node_helper(root->right, key);
        } else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }

                delete temp;

            } else {
                Node* temp = min_val_node(root->right);
                root->key = temp->key;
                root->right = delete_node_helper(root->right, temp->key);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = get_balance(root);

        if (balance > 1 && get_balance(root->left) >= 0) {
            return right_rotate(root);
        }

        if (balance > 1 && get_balance(root->left) < 0) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }

        if (balance < -1 && get_balance(root->right) <= 0) {
            return left_rotate(root);
        }

        if (balance < -1 && get_balance(root->right) > 0) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }

        return root;
    }

    void in_order_helper(Node* root) {
        if (root != nullptr) {
            in_order_helper(root->left);
            cout << root->key << " ";
            in_order_helper(root->right);
        }
    }

    int count_leaves_helper(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        return count_leaves_helper(node->left) + count_leaves_helper(node->right);
    }

public:
    AVL_Tree() {
        root = nullptr;
    }

    void insert(int key) {
        root = help_for_insert(root, key);
    }

    void delete_node(int key) {
        root = delete_node_helper(root, key);
    }

    void in_order() {
        in_order_helper(root);
        cout << endl;
    }

    int count_leaves() {
        return count_leaves_helper(root);
    }
};

int main() {
    AVL_Tree avl;

    cout << "Enter number of nodes: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        avl.insert(x);
    }

    cout << "Basic tree:\n";
    avl.in_order();

    int leaves_count = avl.count_leaves();

    cout << "\n\n\nLeaves count: " << leaves_count << "\n";

    return 0;
}