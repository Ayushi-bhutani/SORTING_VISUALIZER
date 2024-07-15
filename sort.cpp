

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void saveSteps(const vector<vector<int>>& steps, const string& filename) {
    ofstream file(filename);
    for (const auto& step : steps) {
        for (size_t i = 0; i < step.size(); ++i) {
            file << step[i];
            if (i != step.size() - 1) file << ",";
        }
        file << endl;
    }
    file.close();
}

void bubbleSort(vector<int>& arr, vector<vector<int>>& steps) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                steps.push_back(arr);
            }
        }
    }
}

void selectionSort(vector<int>& arr, vector<vector<int>>& steps) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[minIdx], arr[i]);
        steps.push_back(arr);
    }
}

void insertionSort(vector<int>& arr, vector<vector<int>>& steps) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        steps.push_back(arr);
    }
}

void merge(vector<int>& arr, int left, int mid, int right, vector<vector<int>>& steps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        steps.push_back(arr);
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        steps.push_back(arr);
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        steps.push_back(arr);
    }
}

void mergeSort(vector<int>& arr, int left, int right, vector<vector<int>>& steps) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, steps);
    mergeSort(arr, mid + 1, right, steps);
    merge(arr, left, mid, right, steps);
}

int partition(vector<int>& arr, int low, int high, vector<vector<int>>& steps) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            steps.push_back(arr);
        }
    }
    swap(arr[i + 1], arr[high]);
    steps.push_back(arr);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high, vector<vector<int>>& steps) {
    if (low < high) {
        int pi = partition(arr, low, high, steps);
        quickSort(arr, low, pi - 1, steps);
        quickSort(arr, pi + 1, high, steps);
    }
}

int main(int argc, char* argv[]) {
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    vector<vector<int>> steps;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <algorithm>" << endl;
        return 1;
    }

    string algorithm = argv[1];

    if (algorithm == "bubbleSort") {
        bubbleSort(arr, steps);
        saveSteps(steps, "bubble_steps.txt");
    } else if (algorithm == "selectionSort") {
        selectionSort(arr, steps);
        saveSteps(steps, "selection_steps.txt");
    } else if (algorithm == "insertionSort") {
        insertionSort(arr, steps);
        saveSteps(steps, "insertion_steps.txt");
    } else if (algorithm == "mergeSort") {
        mergeSort(arr, 0, arr.size() - 1, steps);
        saveSteps(steps, "merge_steps.txt");
    } else if (algorithm == "quickSort") {
        quickSort(arr, 0, arr.size() - 1, steps);
        saveSteps(steps, "quick_steps.txt");
    } else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        return 1;
    }

    return 0;
}
