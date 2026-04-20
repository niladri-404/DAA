#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id[10];
    int deadline;
    int profit;
} Job;

/* Sort by Maximum Profit (Descending) */
int compareProfit(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;

    return j2->profit - j1->profit;
}

int main() {
    int n;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];

    /* Input job details */
    for (int i = 0; i < n; i++) {
        printf("\nEnter Job ID, Deadline, Profit for Job %d: ", i + 1);
        scanf("%s %d %d", jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    /* Print input jobs */
    printf("\nJobs Entered:\n");
    printf("Job\tDeadline\tProfit\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);
    }

    /* Sort jobs by profit */
    qsort(jobs, n, sizeof(Job), compareProfit);

    printf("\nAfter Sorting by Profit:\n");
    printf("Job\tDeadline\tProfit\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);
    }

    /* Find maximum deadline */
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    /* Create slot array */
    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = -1;

    int totalProfit = 0;

    /* Job Sequencing Logic */
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    /* Print selected jobs */
    printf("\nSelected Jobs Sequence:\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%s ", jobs[slot[i]].id);
    }

    printf("\nMaximum Profit = %d\n", totalProfit);

    return 0;
}