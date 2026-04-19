#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void analyze_stock_windows(int arr[], int size, int window_size);

int main() {
    int num_days = 10;
    int window_size = 3;

    // Allocate memory dynamically
    int *stocks = (int *)malloc(num_days * sizeof(int));
    
    // Seed the random number generator
    srand(time(NULL));

    // Generate random stock values between 10 and 100
    printf("Original random stock prices for %d days:\n", num_days);
    for (int i = 0; i < num_days; i++) {
        stocks[i] = (rand() % 91) + 10; 
        printf("%d ", stocks[i]);
    }
    printf("\n\n");

    // Brute force step 1: Sort the array using Quick Sort
    quickSort(stocks, 0, num_days - 1);

    printf("Sorted stock prices:\n");
    for (int i = 0; i < num_days; i++) {
        printf("%d ", stocks[i]);
    }
    printf("\n\n");

    // Brute force step 2: Apply the sliding window technique
    analyze_stock_windows(stocks, num_days, window_size);

    // Free the allocated memory
    free(stocks);

    return 0;
}

// Quick Sort partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as the pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and the pivot (arr[high])
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

// Quick Sort recursive function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Sliding window function
void analyze_stock_windows(int arr[], int size, int window_size) {
    if (size < window_size) {
        printf("Error: Array size is smaller than the window size.\n");
        return;
    }

    printf("--- Sliding Window Analysis (Window Size: %d) ---\n", window_size);
    
    // Slide the window across the array
    for (int i = 0; i <= size - window_size; i++) {
        int min_val = arr[i];
        int max_val = arr[i + window_size - 1];
        int variation = max_val - min_val;

        printf("Window %d [ ", i + 1);
        for (int j = i; j < i + window_size; j++) {
            printf("%d ", arr[j]);
        }
        printf("] -> Min: %d | Max: %d | Variation: %d\n", min_val, max_val, variation);
    }
}