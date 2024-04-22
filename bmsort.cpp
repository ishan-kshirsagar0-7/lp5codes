#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

// Function to perform bubble sort
void bubbleSort(vector<int>& arr) {
    bool swapped;
    int n = arr.size();
    do {
        swapped = false;
        #pragma omp parallel for
        for (int i = 1; i < n; i += 2) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        #pragma omp parallel for
        for (int i = 2; i < n; i += 2) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

// Function to merge two halves of the array
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        temp[k++] = arr[i++];
    }

    while (j <= r) {
        temp[k++] = arr[j++];
    }

    for (i = l, k = 0; i <= r; i++, k++) {
        arr[i] = temp[k];
    }
}

// Function to perform merge sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    srand(time(0)); // Seed for random number generation

    cout << "Original array:\n";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
        cout << arr[i] << " ";
    }
    cout << "\n";

    // Parallel Bubble Sort
    cout << "Sorting array with Parallel Bubble Sort...\n";
    double start_time = omp_get_wtime();
    bubbleSort(arr);
    double time_taken = omp_get_wtime() - start_time;
    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\nTime taken: " << time_taken << " seconds\n";

    // Reinitialize the array for Merge Sort
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers again
    }

    // Parallel Merge Sort
    cout << "Sorting array with Parallel Merge Sort...\n";
    start_time = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    time_taken = omp_get_wtime() - start_time;
    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\nTime taken: " << time_taken << " seconds\n";

    return 0;
}

// Command to compile : g++ -fopenmp -o bmsort bmsort.cpp
// Command to execute : ./bmsort
// Sample input : 10