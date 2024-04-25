#include<iostream>
#include<bits/stdc++.h>
#include<iomanip>
#include<omp.h>
using namespace std;

void quicksort_serial(int arr[], int st, int end) {
    if (st < end) {
        int pivot = arr[end];
        int i = st - 1;
        int j = st;

        for (int var = j; var < end; var++) {
            if (arr[var] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[var];
                arr[var] = temp;
            }
        }

        // swap i+1 and end
        int temp = arr[i + 1];
        arr[i + 1] = arr[end];
        arr[end] = temp;

        i++;

        quicksort_serial(arr, st, i - 1);
        quicksort_serial(arr, i + 1, end);
    }
}

void quicksort_parallel(int arr[], int st, int end) {
    if (st < end) {
        int pivot = arr[end];
        int i = st - 1;
        int j = st;

        for (int var = j; var < end; var++) {
            if (arr[var] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[var];
                arr[var] = temp;
            }
        }

        // swap i+1 and end
        int temp = arr[i + 1];
        arr[i + 1] = arr[end];
        arr[end] = temp;

        i++;

#pragma omp parallel sections
        {
#pragma omp section
            quicksort_parallel(arr, st, i - 1);
#pragma omp section
            quicksort_parallel(arr, i + 1, end);
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n] = {0};

    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%32;
    }

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // Serial Execution
    clock_t start_serial = clock();
    quicksort_serial(arr, 0, n - 1);
    clock_t stop_serial = clock();
    cout << "Sorted Array (Serial): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout<<"Time required for serial execution: "<<(double)(stop_serial-start_serial)<<" ms"<<endl;

    // Reset array for parallel execution
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%32;
    }


    // Parallel Execution
    clock_t start_parallel = clock();
    quicksort_parallel(arr, 0, n - 1);
    clock_t stop_parallel = clock();
    cout << "Sorted Array (Parallel): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout<<"Time required for parallel execution: "<<(double)(stop_parallel-start_parallel)<<" ms"<<endl;

    return 0;
}
