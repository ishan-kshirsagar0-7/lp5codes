#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

void min(int *arr, int n)
{
    double min_val = 10000;
    int i;
    cout << endl;
#pragma omp parallel for reduction(min : min_val)
    for (i = 0; i < n; i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    cout << "\n\nmin_val = " << min_val << endl;
}

void max(int *arr, int n)
{
    double max_val = 0.0;
    int i;

#pragma omp parallel for reduction(max : max_val)
    for (i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    cout << "\n\nmax_val = " << max_val << endl;
}

void avg(int *arr, int n)
{
    int i;
    float avg = 0, sum = 0;
#pragma omp parallel reduction(+ : sum)
    {
        // int id = omp_get_thread_num();
#pragma omp for
        for (i = 0; i < n; i++)
        {
            sum = sum + arr[i];
        }
    }
    cout << "\n\nSum = " << sum << endl;
    avg = sum / n;
    cout << "\nAverage = " << avg << endl;
}

int main()
{
    int n, i;
    n = 6; // change the number of elements directly
    int arr[6];  // change the number of elements directly

    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    cout << "\nArray elements are: ";
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << ",";
    }

    min(arr, n);
    max(arr, n);
    avg(arr, n);
    return 0;
}