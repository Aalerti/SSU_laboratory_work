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

    static void printEmployee(const Employee& e) {
        cout << e.lastName << " " << e.position << " "
             << e.day << "." << e.month << "." << e.year << " "
             << e.experience << "yr " << e.salary;
    }
};

struct HashTable {
    vector<Employee> table;
    vector<bool> occupied;
    int M;

    HashTable(int m) : M(m), table(m), occupied(m, false) {}


    int h_supporting(int year) {
        return year % M;
    }

    int hash_main(int year, int i) {
        return (h_supporting(year) + i) % M;
    }

    void insert(const Employee& e) {
        int i = 0;
        int index = hash_main(e.year, i);
        while (i < M && occupied[index]) {
            i++;
            index = hash_main(e.year, i);
        }
        if (!occupied[index]) {
            table[index] = e;
            occupied[index] = true;
        }
        else {
            cout << "Table is full\n";
        }
    }

    void search(int year) {
        int i = 0;
        while (i < M) {
            int index = hash_main(year, i);
            if (table[index].year == year)
                Employee::printEmployee(table[index]);
                cout << '\n';
            i++;
        }
    }

    void print() {
        for (int index = 0; index < M; index++) {
            cout << "bucket " << index << ": ";
            if (occupied[index]) {
                Employee::printEmployee(table[index]);
                cout << '\n';
            } else {
                cout << "NULL\n";
            }
        }
    }
};


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


    int M = employees.size();
    HashTable hash_table(M);

    for (auto& emp : employees)
        hash_table.insert(emp);

    hash_table.print();

    int year;
    cout << "\nEnter year to search: ";
    cin >> year;
    hash_table.search(year);

    cout << '\n';


    return 0;
}