#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


void countingSortRow(std::vector<int>& row) {
    if (row.empty()) return;

    int min_val = *std::min_element(row.begin(), row.end());
    int max_val = *std::max_element(row.begin(), row.end());
    int range = max_val - min_val + 1;

    std::vector<int> count(range, 0);
    for (int num : row) {
        count[num - min_val]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            row[index] = i + min_val;
            index++;
            count[i]--;
        }
    }
}

int main() {
    std::ifstream input("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab4/input.txt");
    std::ofstream output("/home/alerti/Projects/CLionProjects/SSU_laboratory_work/term_2_lab4/output.txt");

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error when opening file" << '\n';
        return 1;
    }

    int n;
    if (!(input >> n)) {
        std::cerr << "File is empty or have a wrong form" << '\n';
        return 1;
    }

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        countingSortRow(matrix[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << matrix[i][j] << " ";
        }
        output << '\n';
    }

    input.close();
    output.close();

    return 0;
}