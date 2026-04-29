#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};

class Red_Black_Tree {
private:
    Node* root;
    Node* TNULL;


    void in_order_helper(Node* node) {

        if (node != TNULL) {

            in_order_helper(node->left);
            string colorStr = (node->color == 1) ? "Красный" : "Черный";
            cout << node->data << " - (" << colorStr << "),  ";
            in_order_helper(node->right);
        }
    }

    void collect_evens(Node* node, vector<int>& list) {
        if (node != TNULL) {
            collect_evens(node->left, list);

            if (node->data % 2 == 0) {
                list.push_back(node->data);
            }

            collect_evens(node->right, list);
        }
    }

    void left_rotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != TNULL) {
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }


        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != TNULL) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    void fix_insert(Node* k) {
        Node* u;
        while (k->parent != nullptr && k->parent->color == 1) {

            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        right_rotate(k);
                    }

                    k->parent->color = 0;

                    k->parent->parent->color = 1;

                    left_rotate(k->parent->parent);
                }
            } else {

                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        left_rotate(k);
                    }


                    k->parent->color = 0;

                    k->parent->parent->color = 1;
                    right_rotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void rb_transplant(Node* u, Node* v) {

        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        v->parent = u->parent;
    }

    Node* minim(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void fix_delete(Node* x) {
        Node* s;

        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;

                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    left_rotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        right_rotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    left_rotate(x->parent);
                    x = root;
                }

            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    right_rotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->left->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        left_rotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }

        x->color = 0;
    }

    void help_for_delete_node(Node* node, int key) {
        Node* z = TNULL;
        Node* x;
        Node* y;

        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) return;

        y = z;
        int y_original_color = y->color;

        if (z->left == TNULL) {
            x = z->right;
            rb_transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rb_transplant(z, z->left);
        } else {
            y = minim(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rb_transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rb_transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == 0) {
            fix_delete(x);
        }
    }

public:
    Red_Black_Tree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void in_order() {
        in_order_helper(this->root);
        cout << endl;
    }

    void remove_even_elements() {
        vector<int> ev;
        collect_evens(this->root, ev);

        for (int val : ev) {
            delete_node(val);
        }
    }

    void insert(int key) {
        Node* node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;

        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }

        fix_insert(node);
    }


    void delete_node(int x) {
        help_for_delete_node(this->root, x);
    }
};

int main() {
    Red_Black_Tree rbt;

    cout << "Enter number of nodes: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        rbt.insert(x);
    }

    cout << "Basic tree:\n";
    rbt.in_order();

    rbt.remove_even_elements();


    cout << "\n\n\nNew tree\n";
    rbt.in_order();

    return 0;
}