#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void findMaxMin(int arr[], int low, int high, int *max, int *min);
void analyze_stock_window_dc(int arr[], int size, int window_size);

int main()
{
    int num_days = 10;
    int window_size = 3;

    int *stocks = (int *)malloc(num_days * sizeof(int));

    srand(time(NULL));

    // Generate random stock value between 10 and 100
    printf("Original stock pricesfor %d days:\n", num_days);
    for (int i = 0; i < num_days; i++)
    {
        stocks[i] = (rand() % 91) + 10;
        printf("%d ", stocks[i]);
    }
    printf("\n\n");

    // No sorting is required for Divide and Conquer technique
    analyze_stock_window_dc(stocks, num_days, window_size);

    free(stocks);
    return 0;
}

// Divide and conquer method to find max and min
void findMaxMin(int arr[], int low, int high, int *max, int *min)
{
    int max1, min1, max2, min2;

    // case-1: if only one element if present
    if (low == high)
    {
        *min = arr[low];
        *max = arr[high];
        return;
    }

    // case-2: if exactly two elements are present
    if (high == low + 1)
    {
        if (arr[low] > arr[high])
        {
            *min = arr[high];
            *max = arr[low];
        }
        else
        {
            *min = arr[low];
            *max = arr[high];
        }
        return;
    }

    // Recursive case: Divide the array(or window) in to two halves
    int mid = low + (high - low) / 2;

    // Find min and max in the left half
    findMaxMin(arr, low, mid, &max1, &min1);

    // Find min and max in the right half
    findMaxMin(arr, mid + 1, high, &max2, &min2);

    // Conquer: compare the maximus and minimus of the two halves
    if (min1 < min2)
        *min = min1;
    else
        *min = min2;
    if (max1 > max2)
        *max = max1;
    else
        *max = max2;
}

void analyze_stock_window_dc(int arr[], int size, int window_size)
{
    if (size < window_size)
    {
        printf("Error array size is smaller than the window size.\n");
        return;
    }

    printf(".....Sliding window analusis(window size %d)....\n", window_size);

    // Slide the window accross the unsorted array
    for (int i = 0; i < size - window_size; i++)
    {
        int current_max, current_min;

        // pass the start(i) and end(i+window_size-1) of the current window into the divide and conquer function using pointers to extract the result
        findMaxMin(arr, i, i + window_size - 1, &current_max, &current_min);
        int variation = current_max - current_min;

        //print the result of the specific window
        printf("Window %d [",i+1);
        for (int j = i; j<i+window_size; j++)
        {
            printf("%d ",arr[j]);
        }
        printf("] -> Min: %d | Max: %d | Variation: %d\n", current_min, current_max, variation);
        
    }
}