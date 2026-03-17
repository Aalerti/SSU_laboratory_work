#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int RUN = 16;

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int el = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > el) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = el;
    }
}


void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> l_p(mid - left + 1);
    for (int i = 0; i < mid - left + 1; i++)
        l_p[i] = arr[left + i];

    vector<int> r_p(right - mid);
    for (int i = 0; i < right - mid; i++)
        r_p[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < l_p.size() && j < r_p.size()) {
        if (l_p[i] <= r_p[j]) {
            arr[k++] = l_p[i++];
        } else {
            arr[k++] = r_p[j++];
        }
    }
    while (i < l_p.size()) {
        arr[k++] = l_p[i++];
    }
    while (j < r_p.size()) {
        arr[k++] = r_p[j++];
    }
}


void timSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, min(i + RUN - 1, n - 1));
    }


    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    timSort(arr);

    cout << "sorted elements: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}