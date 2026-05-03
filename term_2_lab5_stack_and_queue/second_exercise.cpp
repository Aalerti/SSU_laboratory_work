// #include <iostream>
//
// struct Queue {
//     int* data;
//     int head;
//     int tail;
//     int size;
//     int capacity;
//
//     Queue() : head(0), tail(0), size(0), capacity(8) {
//         data = new int[capacity];
//     }
//
//     ~Queue() {
//         delete[] data;
//     }
//
//     void push(int val) {
//         if (size == capacity) {
//             capacity *= 2;
//             int* newData = new int[capacity];
//             for (int i = 0; i < size; i++)
//                 newData[i] = data[(head + i) % (capacity / 2)];
//             delete[] data;
//             data = newData;
//             head = 0;
//             tail = size;
//         }
//         data[tail] = val;
//         tail = (tail + 1) % capacity;
//         size++;
//     }
//
//     int pop() {
//         int val = data[head];
//         head = (head + 1) % capacity;
//         size--;
//         return val;
//     }
//
//     bool empty() const {
//         return size == 0;
//     }
//
//     void print() {
//         int n = size;
//         for (int i = 0; i < n; i++) {
//             int val = pop();
//             std::cout << val << ' ';
//             push(val);
//         }
//         std::cout << '\n';
//     }
// };
//
// bool isComposite(int n) {
//     if (n < 4) return false;
//     for (int i = 2; i * i <= n; i++)
//         if (n % i == 0) return true;
//     return false;
// }
//
// int main() {
//     int n;
//     std::cin >> n;
//
//     Queue q;
//     for (int i = 0; i < n; i++) {
//         int x;
//         std::cin >> x;
//         q.push(x);
//     }
//
//     std::cout << "Original: ";
//     q.print();
//
//
//     int total = q.size;
//     int idx = -1;
//     for (int i = 0; i < total; i++) {
//         int val = q.pop();
//         q.push(val);
//         if (idx == -1 && isComposite(val))
//             idx = i;
//     }
//
//     if (idx == -1) {
//         std::cout << "No composite numbers found.\n";
//         return 0;
//     }
//
//     for (int i = 0; i < idx; i++)
//         q.push(q.pop());
//
//     std::cout << "Shifted:  ";
//     q.print();
//
//     return 0;
// }





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

bool isComposite(int n) {
    if (n < 4) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return true;
    return false;
}

int main() {
    int n;
    std::cin >> n;

    Queue q;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        q.push(x);
    }

    std::cout << "Original: ";
    q.print();

    int total = q.size();
    int idx = -1;
    for (int i = 0; i < total; i++) {
        int val = q.pop();
        q.push(val);
        if (idx == -1 && isComposite(val))
            idx = i;
    }

    if (idx == -1) {
        std::cout << "No composite numbers found.\n";
        return 0;
    }

    for (int i = 0; i < idx; i++)
        q.push(q.pop());

    std::cout << "Shifted:  ";
    q.print();

    return 0;
}