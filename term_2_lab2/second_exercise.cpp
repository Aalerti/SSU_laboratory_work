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
    bool is_first_digit_found = false;
    int first_digit = 0;

    std::unordered_map<std::string, int> ans;

    while (file >> input) {
        if (is_integer(input)) {
            if (!is_first_digit_found) {
                first_digit = std::stoi(input);
                is_first_digit_found = true;
            }
        }

        else {
            ans[input] += 1;
        }
    }

    if (!is_first_digit_found) {
        std::cerr << "You didn't enter a first digit";
        return 1;
    }

    if (ans.empty()) {
        std::cerr << "You didn't enter a word, only digit";
        return 1;
    }

    std::cout << "First digit: " << first_digit << '\n';
    
    for (const auto &pair : ans) {
        if (pair.second == first_digit) {
            std::cout << pair.first << '\n';
        }
    }
    
    return 0;
}