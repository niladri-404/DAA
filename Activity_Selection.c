#include <stdio.h>
#include <stdlib.h>


struct Activity {
    int start;
    int finish;
};


int compare(const void *a, const void *b) {
    struct Activity *act1 = (struct Activity *)a;
    struct Activity *act2 = (struct Activity *)b;
    return (act1->finish - act2->finish);
}

int main() {
    int n;

    printf("Enter the number of activities: ");
    scanf("%d", &n);

    struct Activity arr[n];

    printf("Enter start and finish times for each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d (start finish): ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].finish);
    }


    qsort(arr, n, sizeof(struct Activity), compare);

    printf("\nFollowing activities are selected:\n");


    int i = 0;
    printf("Activity %d: (%d, %d)\n", i + 1, arr[i].start, arr[i].finish);


    for (int j = 1; j < n; j++) {

        if (arr[j].start >= arr[i].finish) {
            printf("Activity %d: (%d, %d)\n", j + 1, arr[j].start, arr[j].finish);
            i = j;
        }
    }

    return 0;
}