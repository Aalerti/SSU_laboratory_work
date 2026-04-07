#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    double data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};


struct Stack {
    Node* top;

    Stack() : top(nullptr) {}

    ~Stack() {
        while (!empty()) pop();
    }

    void push(double val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    double pop() {
        if (empty()) return 0;
        double val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool empty() const {
        return top == nullptr;
    }
};

int main() {
    string primer;
    cout << "Enter a postfix expression: " << '\n';
    getline(cin, primer);

    Stack stack;
    stringstream ss(primer);
    string elem;


    while (ss >> elem) {
        if (elem == "+" || elem == "-" || elem == "*" || elem == "/") {
            int b = stack.pop();
            int a = stack.pop();

            if (elem == "+") stack.push(a + b);
            else if (elem == "-") stack.push(a - b);
            else if (elem == "*") stack.push(a * b);
            else if (elem == "/") {
                if (b != 0) stack.push(a / b);
                else {
                    cout << "Error: Division by zero!" << '\n';
                    return 1;
                }
            }
        }
        else {
            stack.push(stoi(elem));
        }
    }

    cout << "Answer: " << stack.pop() << endl;

    return 0;
}