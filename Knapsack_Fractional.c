#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int profit;
    float ratio;
} Item;

int compareRatio(const void *a, const void *b) {
    Item *i1 = (Item *)a;
    Item *i2 = (Item *)b;

    if (i1->ratio < i2->ratio)
        return 1;
    else if (i1->ratio > i2->ratio)
        return -1;
    else 
        return 0;
}

int compareWeight(const void *a, const void *b) {
    Item *i1 = (Item *)a;
    Item *i2 = (Item *)b;

    return i1->weight - i2->weight;
}

int compareProfit(const void *a, const void *b) {
    Item *i1 = (Item *)a;
    Item *i2 = (Item *)b;

    return i2->profit - i1->profit;
}

float knapsack(Item items[], int n, int capacity) {
    float totalValue = 0.0;
    int remainingCapacity = capacity;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= remainingCapacity) {
            totalValue += items[i].profit;
            remainingCapacity -= items[i].weight;
        } else {
            totalValue += items[i].ratio * remainingCapacity;
            break;
        }
    }
    return totalValue;
}

int main() {
    int n, capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int profit[n], weight[n];

    printf("Enter profits:\n");
    for (int i = 0; i < n; i++) 
        scanf("%d", &profit[i]);

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    Item items[n];

    for (int i = 0; i < n; i++) {
        items[i].profit = profit[i];
        items[i].weight = weight[i];
        items[i].ratio = (float)profit[i] / weight[i];
    }

    printf("\nProfit array: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", profit[i]);

    printf("\nWeight array: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", weight[i]);

    printf("\nProfit/Weight ratio array: ");
    for (int i = 0; i < n; i++) 
        printf("%.2f ", items[i].ratio);

    printf("\nEnter knapsack capacity: ");
    scanf("%d", &capacity);

   
    Item itemsRatio[n];
    for (int i = 0; i < n; i++) 
        itemsRatio[i] = items[i];

    qsort(itemsRatio, n, sizeof(Item), compareRatio);
    float resultRatio = knapsack(itemsRatio, n, capacity);

    printf("\n[Case 1: Profit/Weight Ratio] Max Profit = %.2f\n", resultRatio);

    Item itemsWeight[n];
    for (int i = 0; i < n; i++) itemsWeight[i] = items[i];

    qsort(itemsWeight, n, sizeof(Item), compareWeight);
    float resultWeight = knapsack(itemsWeight, n, capacity);

    printf("[Case 2: Min Weight Priority] Max Profit = %.2f\n", resultWeight);

    Item itemsProfit[n];
    for (int i = 0; i < n; i++) itemsProfit[i] = items[i];

    qsort(itemsProfit, n, sizeof(Item), compareProfit);
    float resultProfit = knapsack(itemsProfit, n, capacity);

    printf("[Case 3: Max Profit Priority] Max Profit = %.2f\n", resultProfit);

    return 0;
}