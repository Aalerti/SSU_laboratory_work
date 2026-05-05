#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Node {
    char inf;
    Node* right;
    Node* left;
    Node* parent;
};

class Expression_Tree {

    Node* root;

    Node* new_node(char x) {
        Node* n = new Node;
        n->inf = x;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        return n;
    }

    void pre_order_helper(Node* tr) {

        if (tr != nullptr) {
            cout << tr->inf << " ";
            pre_order_helper(tr->left);
            pre_order_helper(tr->right);
        }
    }

    void post_order_helper(Node* tr) {

        if (tr != nullptr) {
            post_order_helper(tr->left);
            post_order_helper(tr->right);
            cout << tr->inf << " ";
        }
    }

public:
    Expression_Tree() {
        root = nullptr;
    }

    void create_tree(string str) {
        Node* tr = nullptr;

        for (size_t i = 0; i < str.length(); i++) {
            Node* n = new_node(str[i]);

            if (str[i] == '-' || str[i] == '+') {
                if (tr != nullptr) {
                    tr->parent = n;
                }

                n->left = tr;
                tr = n;

            } else if (str[i] == '/' || str[i] == '*') {

                if (tr != nullptr && isdigit(tr->inf)) {
                    tr->parent = n;
                    n->left = tr;
                    tr = n;
                } else if (tr != nullptr) {
                    n->parent = tr;
                    n->left = tr->right;
                    if (tr->right != nullptr) {
                        tr->right->parent = n;
                    }
                    tr->right = n;


                }
            } else {

                if (tr == nullptr) {
                    tr = n;
                } else {

                    if (tr->right == nullptr) {
                        n->parent = tr;
                        tr->right = n;
                    } else {
                        Node* x = tr->right;
                        while (x->right != nullptr) {
                            x = x->right;
                        }

                        n->parent = x;
                        x->right = n;
                    }
                }
            }
        }
        root = tr;
    }

    void pre_order() {
        pre_order_helper(root);
        cout << endl;
    }

    void post_order() {
        post_order_helper(root);
        cout << endl;
    }
};

int main() {
    Expression_Tree expr_tree;
    string expr;

    cout << "Enter expression: ";
    cin >> expr;

    expr_tree.create_tree(expr);

    cout << "Prefix form: ";
    expr_tree.pre_order();

    cout << "\n\n\n";

    cout << "Postfix form: ";
    expr_tree.post_order();

    return 0;
}