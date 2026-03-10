#include <iostream>
#include <fstream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right, bool descending, std::vector<int>& temp) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        bool condition = descending ? (arr[i] > arr[j]) : (arr[i] < arr[j]);
        
        if (condition) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, bool descending, std::vector<int>& temp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, descending, temp);
        mergeSort(arr, mid + 1, right, descending, temp);

        merge(arr, left, mid, right, descending, temp);
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

    std::vector<int> temp(n);

    for (int i = 0; i < n; i++) {
        bool isThirdRow = ((i + 1) % 3 == 0);
        mergeSort(matrix[i], 0, n - 1, isThirdRow, temp);
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