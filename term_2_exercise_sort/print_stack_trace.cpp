#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void printState(const vector<int>& arr, int i, int j) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << " i = " << i << " j = " << j << "\n";
}


void selectionSort(vector<int> arr) {
    cout << "--- Сортировка выбором ---" << "\n";
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            printState(arr, i, j); 
            
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
    
    cout << "Результат: ";
    for (int num : arr) cout << num << " ";
    cout << "\n\n";
}

// Сортировка вставками
void insertionSort(vector<int> arr) {
    cout << "--- Сортировка вставками ---" << "\n";
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0) {

            
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                printState(arr, i, j);
                j--;
            } else {
                printState(arr, i, j);
                break;
            }
        }
    }
    
    cout << "Результат: ";
    for (int num : arr) cout << num << " ";
    cout << "\n\n";
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<int> arr1 = {5, 1, 8, 2, 9, 7, 3, 4, 6};
    selectionSort(arr1);

    vector<int> arr2 = {5, 1, 8, 2, 9, 7, 3, 4, 6};
    insertionSort(arr2);

    return 0;
}