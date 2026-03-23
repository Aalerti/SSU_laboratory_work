#include <iostream>

struct Queue {
    int* data;
    int head;
    int tail;
    int size;
    int capacity;

    Queue() : head(0), tail(0), size(0), capacity(8) {
        data = new int[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void push(int val) {
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++)
                newData[i] = data[(head + i) % (capacity / 2)];
            delete[] data;
            data = newData;
            head = 0;
            tail = size;
        }
        data[tail] = val;
        tail = (tail + 1) % capacity;
        size++;
    }

    int pop() {
        int val = data[head];
        head = (head + 1) % capacity;
        size--;
        return val;
    }

    bool empty() const {
        return size == 0;
    }

    void print() {
        int n = size;
        for (int i = 0; i < n; i++) {
            int val = pop();
            std::cout << val << ' ';
            push(val);
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


    int total = q.size;
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