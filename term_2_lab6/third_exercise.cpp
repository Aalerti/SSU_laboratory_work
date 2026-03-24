#include <iostream>


struct Node {
    int data;
    Node *next;
    Node *prev;

    Node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

struct DoubleLinkedList {
    Node *head;
    Node *tail;
    int size;

    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        Node *curr = head;
        while (curr != nullptr) {
            Node *next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }

    void push(int d) {
        Node *new_node = new Node(d);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void print() {
        Node *curr = head;
        while (curr != nullptr) {
            std::cout << curr->data;
            if (curr->next != nullptr) std::cout << " ";
            curr = curr->next;
        }
    }

    
    void detach(Node *node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        node->prev = nullptr;
        node->next = nullptr;
        size--;
    }


    void insert_before(Node *target, Node *node) {
        node->next = target;
        node->prev = target->prev;
        if (target->prev) target->prev->next = node;
        else head = node;
        target->prev = node;
        size++;
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

    Node *curr = list.head->next;
    while (curr != nullptr) {
        Node *next_node = curr->next;

        Node *found_pos = curr->prev;
        while (found_pos != nullptr && found_pos->data > curr->data) {
            found_pos = found_pos->prev;
        }

        if (found_pos != curr->prev) {
            list.detach(curr);
            if (found_pos == nullptr) list.insert_before(list.head, curr);
            else list.insert_before(found_pos->next, curr);
        }
        curr = next_node;
    }

    list.print();

    return 0;
}