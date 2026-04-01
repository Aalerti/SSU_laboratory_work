// #include <iostream>
//
// struct Stack {
//     char* data;
//     int size;
//     int capacity;
//
//     Stack() : size(0), capacity(4) {
//         data = new char[capacity];
//     }
//
//     ~Stack() {
//         delete[] data;
//     }
//
//     void push(char c) {
//         if (size == capacity) {
//             capacity *= 2;
//             char* newData = new char[capacity];
//             for (int i = 0; i < size; i++) newData[i] = data[i];
//             delete[] data;
//             data = newData;
//         }
//         data[size++] = c;
//     }
//
//     char pop() {
//         return data[--size];
//     }
//
//     bool empty() const {
//         return size == 0;
//     }
//
//     void printBottomToTop() {
//         Stack temp;
//         while (!empty()) temp.push(pop());
//         while (!temp.empty()) {
//             char c = temp.pop();
//             std::cout << c << ' ';
//             push(c);
//         }
//         std::cout << '\n';
//     }
// };
//
// bool isConsonant(char c) {
//     if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
//     if (c < 'a' || c > 'z') return false;
//     return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y';
// }
//
// int main() {
//     int n;
//     std::cin >> n;
//
//     Stack stack;
//     for (int i = 0; i < n; i++) {
//         char c;
//         std::cin >> c;
//         stack.push(c);
//     }
//
//     std::cout << "Original: ";
//     stack.printBottomToTop();
//
//     Stack temp;
//     while (!stack.empty()) {
//         temp.push(stack.pop());
//     }
//
//     Stack newStack;
//     bool found = false;
//     while (!temp.empty()) {
//         char c = temp.pop();
//         newStack.push(c);
//         if (!found && isConsonant(c)) {
//             found = true;
//             newStack.push('!');
//         }
//     }
//
//     std::cout << "New:      ";
//     newStack.printBottomToTop();
//
//     return 0;
// }



#include <iostream>

struct node {
    char inf;
    node* next;
};

struct Stack {
    node* head;

    Stack() : head(nullptr) {}

    ~Stack() {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(char c) {
        node* r = new node;
        r->inf = c;
        r->next = head;
        head = r;
    }

    char pop() {
        char i = head->inf;
        node* r = head;
        head = head->next;
        delete r;
        return i;
    }

    bool empty() const {
        return head == nullptr;
    }

    void printBottomToTop() {
        Stack temp;
        while (!empty()) temp.push(pop());
        while (!temp.empty()) {
            char c = temp.pop();
            std::cout << c << ' ';
            push(c);
        }
        std::cout << '\n';
    }
};

bool isConsonant(char c) {
    if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
    if (c < 'a' || c > 'z') return false;
    return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y';
}

int main() {
    int n;
    std::cin >> n;

    Stack stack;
    for (int i = 0; i < n; i++) {
        char c;
        std::cin >> c;
        stack.push(c);
    }

    std::cout << "Original: ";
    stack.printBottomToTop();

    Stack temp;
    while (!stack.empty()) temp.push(stack.pop());

    Stack newStack;
    bool found = false;

    while (!temp.empty()) {
        char c = temp.pop();
        newStack.push(c);
        if (!found && isConsonant(c)) {
            found = true;
            newStack.push('!');
        }
    }

    std::cout << "New: ";
    newStack.printBottomToTop();

    return 0;
}