#include<iostream>
#include<omp.h>
#include<ctime>
#include<vector>
#include<cstdlib>
using namespace std;

void merge(vector<int>& arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i=0; i<n1; i++){
        L[i] = arr[l + i];
    }
    for (int j=0; j<n2; j++){
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r){
    if(l < r){
        int m = l + (r - l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, l, m);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, m + 1, r);
            }
        }

        merge(arr, l, m, r);
    }
}

vector<int> generateRandomVector(int size){
    vector<int> v(size);
    for(int i=0; i<size; i++){
        v[i] = rand() % 100;
    }
    return v;
}

int main(){
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr = generateRandomVector(n);
    vector<int> arr2 = arr;

    clock_t start, end;
    double duration;

    // Sequential Merge Sort
    start = clock();
    mergeSort(arr, 0, arr.size()-1);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for Sequential Merge Sort: "<<duration<<" seconds."<<endl;

    // Parallel Merge Sort
    start = clock();
    parallelMergeSort(arr2, 0, arr2.size()-1);
    end = clock();
    duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for Parallel Merge Sort: "<<duration<<" seconds."<<endl;

    return 0;
}

// How to execute :
// 1. RUN THIS => g++ -Fopenmp bubblesort.cpp -o bbsort
// 2. THEN THIS => ./bbsort

// Here's a sample input : 1000000