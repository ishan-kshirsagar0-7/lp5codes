#include<iostream>
#include<omp.h>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

void bubbleSort(vector<int>& arr){
    int n = arr.size();
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int>& arr){
    int n = arr.size();
    bool swapped;
    do{
        swapped = false;
        #pragma omp parallel for shared(arr, swapped)
        for (int i=0; i<n; i+=2){
            if(arr[i-1]>arr[i]){
                swap(arr[i-1], arr[i]);
                swapped = true;
            }
        }

        #pragma omp parallel for shared(arr, swapped)
        for (int i=0; i<n-1; i+=2){
            if(arr[i]>arr[i+1]){
                swap(arr[i], arr[i+1]);
                swapped = true;
            }
        }
    } while (swapped);
    
}

vector<int> generateRandomArray(int size){
    vector<int> v(size);
    for (int i=0; i<size; i++){
        v[i] = rand() % 100;
    }
    return v;
}

int main(){
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr = generateRandomArray(n);
    vector<int> arr2 = arr;

    clock_t start, end;
    double duration;

    // Sequential Bubble Sort
    start = clock();
    bubbleSort(arr);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for Sequential Bubble Sort: "<< duration <<" seconds"<< endl;

    // Parallel Bubble Sort
    start = clock();
    parallelBubbleSort(arr2);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for Parallel Bubble Sort: "<< duration <<" seconds"<< endl;

    return 0;
}

// How to execute :
// 1. RUN THIS => g++ -Fopenmp bubblesort.cpp -o bbsort
// 2. THEN THIS => ./bbsort

// Here's a sample input : 10000