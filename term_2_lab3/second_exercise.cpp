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

    bool operator<(const Employee& other) const {
        if (surname != other.surname) {
            return surname < other.surname;
        }
        return position < other.position;
    }
};

void shell_sort(std::vector<Employee> &employees) {
    int n = employees.size();

    for (int d = n / 2; d >= 1; d/=2) {

        for (int i = d; i < n; i++) {
            Employee temp = employees[i];
            int j;
            for (j = i; j >= d && temp < employees[j - d]; j-=d) {
                employees[j] = employees[j - d];
            }
            employees[j] = temp;
        }
    }

}



int main() {
    //std::ifstream inputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_input.txt.txt");
    std::ifstream inputFile("C:\\Users\\Max\\CLionProjects\\laboratory\\term_2_lab3\\first_file_input.txt");
    //std::ofstream outputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_output.txt");
    std::ofstream outputFile("C:\\Users\\Max\\CLionProjects\\laboratory\\term_2_lab3\\first_file_output.txt");

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

    shell_sort(employees);

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