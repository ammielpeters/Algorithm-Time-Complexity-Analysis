#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// O(n) Linear Search
void linear_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return;
    }
}

// O(n^2) Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// O(log n) Binary Search (array must be sorted)
int binary_search(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high)/2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Measure execution time
double measure_time(void (*func)(int*, int, int), int arr[], int n, int key) {
    clock_t start = clock();
    func(arr, n, key);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Wrapper for bubble sort (since it doesn’t take key)
void bubble_wrapper(int arr[], int n, int key) {
    bubble_sort(arr, n);
}

int main() {
    int sizes[] = {10, 100, 1000, 5000};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);

    printf("Algorithm Performance (time in seconds)\n");
    printf("InputSize\tLinear(O(n))\tBubble(O(n^2))\tBinary(O(log n))\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));

        // Fill array
        for (int j = 0; j < n; j++) arr[j] = j;

        int key = n - 1; // last element to ensure worst case

        // Measure algorithms
        double t_linear = measure_time(linear_search, arr, n, key);
        double t_bubble = measure_time(bubble_wrapper, arr, n, key);
        double t_binary = measure_time(binary_search, arr, n, key);

        printf("%d\t\t%f\t%f\t%f\n", n, t_linear, t_bubble, t_binary);

        free(arr);
    }

    return 0;
}
