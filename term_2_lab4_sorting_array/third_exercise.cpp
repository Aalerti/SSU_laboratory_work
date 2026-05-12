#include <iostream>
#include <fstream>
#include <vector>

void bubbleSortDiagonal(std::vector<std::vector<int>>& matrix, int k, int start_row, int len) {
    if (len <= 1) return;

    for (int step = 0; step < len - 1; step++) {

        for (int i = 0; i < len - 1 - step; i++) {
            int r1 = start_row + i;
            int c1 = k - r1;

            int r2 = start_row + i + 1;
            int c2 = k - r2;
            if (matrix[r1][c1] > matrix[r2][c2]) {
                std::swap(matrix[r1][c1], matrix[r2][c2]);
            }
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

    for (int k =0; k < 2*n - 2; k++) {
        int start_row = std::max(0, k - n + 1);
        int end_row = std::min(k, n - 1);
        int len = end_row - start_row + 1;

        bubbleSortDiagonal(matrix, k, start_row, len);
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