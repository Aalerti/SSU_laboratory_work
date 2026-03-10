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


int partition(std::vector<Employee>& arr, int l, int r) {
    double pivot = arr[(l+r) / 2].salary;
    while (true) {
        while (arr[l].salary < pivot) l++;
        while (arr[r].salary > pivot) r--;
        if (l >= r) return r;

        std::swap(arr[l], arr[r]);
        l++;
        r--;
    }
}

void qsort_helper(std::vector<Employee> &arr, int l, int r) {
    if (l>=r) return;

    int index = partition(arr, l, r);

    qsort_helper(arr, l, index);
    qsort_helper(arr, index+1, r);
}

void quick_sort(std::vector<Employee> &arr) {
    if (!arr.empty()) {
        qsort_helper(arr, 0, arr.size() -1);
    }
}


int main() {
    std::ifstream inputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_input.txt");
    //std::ifstream inputFile("C:\\Users\\Max\\CLionProjects\\laboratory\\term_2_lab3\\first_file_input.txt");
    std::ofstream outputFile("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab3/first_file_output.txt");
    //std::ofstream outputFile("C:\\Users\\Max\\CLionProjects\\laboratory\\term_2_lab3\\first_file_output.txt");

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

    quick_sort(employees);

    if (!outputFile.is_open()) {
        std::cerr << "Error when creating output.txt!" << '\n';
        return 1;
    }


    outputFile << std::left << std::setw(15) << "Surname"
               << std::setw(15) << "Position"
               << std::setw(15) << "Data"
               << std::setw(15) << "Experience"
               << std::setw(15) << "Salary" << '\n';
    outputFile << std::string(65, '-') << '\n';

    for (const auto& e : employees) {
        std::string date = (e.day < 10 ? "0" : "") + std::to_string(e.day) + "." +
                      (e.month < 10 ? "0" : "") + std::to_string(e.month) + "." +
                      std::to_string(e.year);

        outputFile << std::left << std::setw(15) << e.surname
                   << std::setw(15) << e.position
                   << std::setw(15) << date
                   << std::setw(15) << e.experience
                   << std::fixed << std::setprecision(2) << e.salary << '\n';
    }

    return 0;
}




