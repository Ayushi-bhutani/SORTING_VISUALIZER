#include <iostream>
#include <vector>
#include <fstream>

void printStep(const std::vector<int>& arr, std::ofstream& outfile) {
    for (size_t i = 0; i < arr.size(); ++i) {
        outfile << arr[i];
        if (i < arr.size() - 1) outfile << ",";
    }
    outfile << std::endl;
}

void bubbleSort(std::vector<int>& arr, std::ofstream& outfile) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                printStep(arr, outfile);
            }
        }
    }
}

void selectionSort(std::vector<int>& arr, std::ofstream& outfile) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
            printStep(arr, outfile);
        }
    }
}

void insertionSort(std::vector<int>& arr, std::ofstream& outfile) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            printStep(arr, outfile);
        }
        arr[j + 1] = key;
        printStep(arr, outfile);
    }
}

int main() {
    std::vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    std::string algorithm;
    std::cin >> algorithm;

    std::ofstream outfile("steps.txt");

    if (algorithm == "bubbleSort") {
        bubbleSort(arr, outfile);
    } else if (algorithm == "selectionSort") {
        selectionSort(arr, outfile);
    } else if (algorithm == "insertionSort") {
        insertionSort(arr, outfile);
    }

    outfile.close();
    return 0;
}
