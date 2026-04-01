#include <iostream>

struct node {
    int inf;
    node* next;
};

struct Queue {
    node* head;
    node* tail;

    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int val) {
        node* r = new node;
        r->inf = val;
        r->next = nullptr;
        if (!head && !tail) {
            head = tail = r;
        } else {
            tail->next = r;
            tail = r;
        }
    }

    int pop() {
        int i = head->inf;
        node* r = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete r;
        return i;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        int count = 0;
        node* p = head;
        while (p) {
            count++;
            p = p->next;
        }
        return count;
    }

    void print() {
        node* p = head;
        while (p) {
            std::cout << p->inf << ' ';
            p = p->next;
        }
        std::cout << '\n';
    }
};

int main() {
    int n;
    std::cin >> n;

    Queue q;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        q.push(x);
    }


    int total = q.size();
    int val = q.pop();
    int minVal = val;
    q.push(val);
    for (int i = 1; i < total; i++) {
        val = q.pop();
        if (val < minVal) minVal = val;
        q.push(val);
    }


    int lastOdd = 0;
    bool foundOdd = false;
    for (int i = 0; i < total; i++) {
        val = q.pop();
        if (val % 2 != 0) {
            lastOdd = val;
            foundOdd = true;
        }
        q.push(val);
    }

    if (!foundOdd) {
        std::cout << "No odd elements found.\n";
        return 0;
    }

    Queue result;
    for (int i = 0; i < total; i++) {
        val = q.pop();
        result.push(val);
        if (val == minVal)
            result.push(lastOdd);
    }

    result.print();
    return 0;
}