#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Employee {
    string lastName;
    string position;
    int day, month, year;
    int experience;
    int salary;
};

struct Node {
    Employee data;
    Node* prev;
    Node* next;

    Node(const Employee& emp) : data(emp), prev(nullptr), next(nullptr) {}
};

struct  DoublyLinkedList {

    Node* head;
    Node* tail;
    int size;

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() { clear(); }

    void pushBack(const Employee& emp) {
        Node* newNode = new Node(emp);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void remove(Node* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next != nullptr)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        delete node;
        size--;
    }

    bool findBySalary(int targetSalary) const {
        bool found = false;
        Node* current = head;
        while (current != nullptr) {
            if (current->data.salary == targetSalary) {
                printEmployee(current->data);
                found = true;
            }
            current = current->next;
        }
        return found;
    }

    int removeBySalary(int targetSalary) {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            if (current->data.salary == targetSalary) {
                remove(current);
                count++;
            }
            current = nextNode;
        }
        return count;
    }

    void printAll() const {
        if (head == nullptr) {
            cout << "  (empty)\n";
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            printEmployee(current->data);
            current = current->next;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    static void printEmployee(const Employee& e) {
        cout << e.lastName << " " << e.position << " "
             << e.day << "." << e.month << "." << e.year << " "
             << e.experience << "yr " << e.salary << " | ";
    }
};

struct HashTable {
    vector<DoublyLinkedList> table;
    int M;

    HashTable(int m) : M(m), table(m) {}

    int hash(int salary) {
        return salary % M;
    }

    void insert(const Employee& e) {
        int index = hash(e.salary);
        table[index].pushBack(e);
    }

    void search(int salary) {
        int index = hash(salary);
        table[index].findBySalary(salary);
    }

    void remove(int salary) {
        int index = hash(salary);
        table[index].removeBySalary(salary);
    }

    void print() {
        for (int index = 0; index < M; index++) {
            cout << "backet " << index << ": ";
            table[index].printAll();
            cout << '\n';
        }
    }
};


#include <stdbool.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

int next_prime(int n) {
    if (n <= 1) return 2;
    if (n % 2 == 0) {
        n++;
    }
    while (!is_prime(n)) {
        n += 2;
    }

    return n;
}

int main() {
    ifstream fin("/home/alert/Projects/CLionProjects/SSU_laboratory_work/term_2_lab9_hash/first_file_input.txt");
    if (!fin) {
        cerr << "Cannot open file\n";
        return 1;
    }

    vector<Employee> employees;
    Employee e;
    while (fin >> e.lastName >> e.position >> e.day >> e.month >> e.year >> e.experience >> e.salary)
        employees.push_back(e);
    fin.close();


    int M = next_prime(employees.size() / 3);
    HashTable hash_table(M);

    for (auto& emp : employees)
        hash_table.insert(emp);

    hash_table.print();

    int salary;
    cout << "\nEnter salary to search: ";
    cin >> salary;
    hash_table.search(salary);

    cout << '\n';

    cout << "\nEnter salary to remove: ";
    cin >> salary;
    hash_table.remove(salary);

    cout << '\n';

    cout << "\nAfter removal:\n";
    hash_table.print();

    return 0;
}