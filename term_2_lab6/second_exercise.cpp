#include <iostream>


struct Node {
    int data;
    Node *next;
    Node *prev;

    Node(int d) : data(d), next(nullptr), prev(nullptr) {
    }
};

struct DoubleLinkedList {
    Node *head;
    Node *tail;
    int size;

    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        Node *curr = head;
        while (size > 0) {
            Node *next_node = curr->next;
            delete curr;
            curr = next_node;
            size--;
        }
    }

    void push(int d) {

        Node *new_node = new Node(d);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->next = nullptr;
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;

    }

    void print() {
        Node *curr = head;
        for (int i=0; i < size; i++) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
    }

    Node* find(int val) {
        Node *curr = head;
        while (curr != nullptr) {
            if (curr->data == val) break;
            curr = curr->next;
        }
        return curr;
    }

    Node* insert_after(Node* node, Node* new_node) {
        if (node == tail) {
            push(new_node->data);
        }
        else {
            Node *next_node = node->next;

            new_node->next = node->next;
            new_node->prev = node;
            node->next = new_node;
            next_node->prev = new_node;
            size++;
        }
        return new_node;
    }

    void del_node(Node* node) {
        if (node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
            delete node;
        }
        else if (node == head) {
            Node *next_node = node->next;
            next_node->prev = nullptr;
            head = next_node;
            delete node;
        }
        else if (node == tail) {
            Node *prev_node = node->prev;
            prev_node->next = nullptr;
            tail = prev_node;
            delete node;
        }
        else {
            Node *next_node = node->next;
            Node *prev_node = node->prev;
            next_node->prev = prev_node;
            prev_node->next = next_node;
            delete node;
        }
        size--;
    }

};

int main() {
    int n;
    std::cin >> n;


    DoubleLinkedList list;
    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        list.push(val);
    }

    if (list.size == 0) {
        std::cout << "Empty list";
        return 0;
    }

    int min_val = list.head->data;
    for (Node *curr = list.head->next; curr != nullptr; curr = curr->next) {
        if (curr->data < min_val) min_val = curr->data;
    }

    for (Node *curr = list.head; curr != nullptr; curr = curr->next) {
        if (curr->data == min_val) {
            if (curr == list.head) {
                break;
            }
            else {
                Node *prev_node = curr->prev;
                list.tail->next = list.head;
                list.head->prev = list.tail;
                prev_node->next = nullptr;
                list.tail = prev_node;
                list.head = curr;
                curr->prev = nullptr;
            }
            break;
        }

    }
    list.print();

    return 0;
}