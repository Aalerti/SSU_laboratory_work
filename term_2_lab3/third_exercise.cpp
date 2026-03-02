#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>

struct Employee {
    std::string surname;
    std::string position;
    int day;
    int month;
    int year;
    int experience;
    double salary;
};

bool compareEmployees(const Employee &a, const Employee &b) {
    if (a.surname != b.surname) {
        return a.surname < b.surname;
    }

    if (a.experience != b.experience) {
        return a.experience < b.experience;
    }

    return a.year < b.year;
}

void insert_sort(std::vector<Employee> &employees) {
    for (int i = 1; i < employees.size(); i++) {
        int min_id = i;
        while (min_id > 0 && compareEmployees(employees[min_id],employees[min_id - 1])) {
            std::swap(employees[min_id], employees[min_id - 1]);
            min_id--;
        }
    }
}



int main() {
    std::ifstream inputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_input.txt");
    std::ofstream outputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_output.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error when opening input.txt!" << '\n';
        return 1;
    }

    std::vector<Employee> employees;
    Employee emp;


    while (inputFile >> emp.surname >> emp.position >> emp.day
                     >> emp.month >> emp.year >> emp.experience >> emp.salary) {
        employees.push_back(emp);
                     }
    inputFile.close();

    insert_sort(employees);

    if (!outputFile.is_open()) {
        std::cerr << "Error when creating output.txt!" << '\n';
        return 1;
    }


    outputFile << std::left << std::setw(15) << "Surname"
               << std::setw(15) << "Position"
               << std::setw(15) << "Data"
               << std::setw(10) << "Experience"
               << std::setw(10) << "Salary" << '\n';
    outputFile << std::string(65, '-') << '\n';

    for (const auto& e : employees) {
        std::string date = (e.day < 10 ? "0" : "") + std::to_string(e.day) + "." +
                      (e.month < 10 ? "0" : "") + std::to_string(e.month) + "." +
                      std::to_string(e.year);

        outputFile << std::left << std::setw(15) << e.surname
                   << std::setw(15) << e.position
                   << std::setw(15) << date
                   << std::setw(10) << e.experience
                   << std::fixed << std::setprecision(2) << e.salary << '\n';
    }

    return 0;
}