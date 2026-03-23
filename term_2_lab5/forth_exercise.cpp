#include <iostream>

struct Stack {
    int* data;
    int size;
    int capacity;

    Stack() : size(0), capacity(4) {
        data = new int[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(int c) {
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        data[size++] = c;
    }

    int pop() {
        return data[--size];
    }

    bool empty() const {
        return size == 0;
    }

    void printBottomToTop() {
        Stack temp;
        while (!empty()) temp.push(pop());
        while (!temp.empty()) {
            int c = temp.pop();
            std::cout << c << ' ';
            push(c);
        }
        std::cout << '\n';
    }
};

int main() {
    int n;
    std::cin >> n;

    Stack s;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        s.push(x);
    }


    Stack temp;
    int val = s.pop();
    int minVal = val, maxVal = val;
    temp.push(val);
    while (!s.empty()) {
        val = s.pop();
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
        temp.push(val);
    }

    int firstMinIdx = -1, lastMinIdx = -1, idx = 0;
    while (!temp.empty()) {
        val = temp.pop();
        if (val == minVal) {
            if (firstMinIdx == -1) firstMinIdx = idx;
            lastMinIdx = idx;
        }
        s.push(val);
        idx++;
    }


    while (!s.empty()) temp.push(s.pop());


    Stack result;
    idx = 0;
    while (!temp.empty()) {
        val = temp.pop();
        result.push(val);
        if (idx == firstMinIdx || (idx == lastMinIdx && firstMinIdx != lastMinIdx))
            result.push(maxVal);
        idx++;
    }

    result.printBottomToTop();

    return 0;
}