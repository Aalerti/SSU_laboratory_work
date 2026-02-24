#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>

bool is_integer(const std::string& s) {
    if (s.empty()) return false;
    size_t start = 0;

    if (s[0] == '-' || s[0] == '+') {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < s.length(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main() {
    std::ifstream file("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Error when opening a input.txt" << std::endl;
        return 1;
    }

    std::string input;
    bool is_first_number_found = false;
    int first_number = 0;

    std::unordered_map<std::string, int> ans;

    while (file >> input) {
        if (is_integer(input)) {
            if (!is_first_number_found) {
                first_number = std::stoi(input);
                is_first_number_found = true;
            }
        }

        else {
            ans[input] += 1;
        }
    }

    if (!is_first_number_found) {
        std::cerr << "You didn't enter a first number";
        return 1;
    }

    if (first_number <= 0) {
        std::cout << "First number is " << first_number << ". A word cannot appear this many times.\n";
        return 0;
    }

    if (ans.empty()) {
        std::cerr << "You didn't enter a word, only number";
        return 1;
    }


    std::cout << "First number: " << first_number << '\n';
    
    for (const auto &pair : ans) {
        if (pair.second == first_number) {
            std::cout << pair.first << '\n';
        }
    }
    
    return 0;
}