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

int partition(std::vector<Employee>& arr, int low, int high) {
    double pivot = arr[high].salary;
    int i = low- 1;

    for (int j = low; j < high; j++) {
        if (arr[j].salary <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i+1], arr[high]);
    return i+1;
}

void quicksort_by_salary(std::vector<Employee>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quicksort_by_salary(arr, low, pivot - 1);
        quicksort_by_salary(arr, pivot + 1 , high);
    }
}

int main() {
    std::ifstream inputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_output.txt");
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

    quicksort_by_salary(employees, 0, employees.size() - 1);

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




