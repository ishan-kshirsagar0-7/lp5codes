#include<iostream>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void min(int *arr, int n){
    int min_val = 10000;
    int i;
    cout << endl;
    #pragma omp parallel for reduction(min: min_val)
    for(i=0; i<n; i++){
        if(arr[i] < min_val){
            min_val = arr[i];
        }
    }
    cout<< "\n\nMINIMUM VALUE = "<<min_val;
}

void max(int *arr, int n){
    int max_val = 0.0;
    int i;
    cout << endl;
    #pragma omp parallel for reduction(max: max_val)
    for(i=0; i<n; i++){
        if(arr[i]>max_val){
            max_val = arr[i];
        }
    }
    cout<<"\n\nMAXIMUM VALUE = "<<max_val<<endl;
}

void avg(int *arr, int n){
    int i;
    float avg=0, sum=0;
    #pragma omp parallel reduction(+ : sum)
    {
        #pragma omp for
        for(i=0; i<n; i++){
            sum = sum + arr[i];
        }
    }
    cout<<"\n\nSUM = "<<sum<<endl;
    avg = sum / n;
    cout<<"\n\nAVERAGE = "<<avg<<endl;
    cout<<endl;
}

int main(){
    int n, i;
    n = 6;           // Change this to any size you want
    int arr[6];      // Change this to any size you want 

    srand(time(0));
    for(int i=0; i<n; ++i){
        arr[i] = rand() % 100;
    }

    cout<<"\nArray Elements are: ";
    for(i=0; i<n; i++){
        cout<<arr[i]<<", ";
    }

    min(arr, n);
    max(arr, n);
    avg(arr, n);

    return 0;
}

// How to execute :
// 1. RUN THIS => g++ -Fopenmp parallel_reduction.cpp -o pr
// 2. THEN THIS => ./pr