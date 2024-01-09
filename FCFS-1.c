#include <stdio.h>
#include <stdlib.h>

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort(int n, int bt[], int at[], int pid[]) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (at[j] > at[j + 1]) {
                swap(at, j, j + 1);
                swap(bt, j, j + 1);
                swap(pid, j, j + 1);
            }
}

void sortPids(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (pid[j] > pid[j + 1]) {
                swap(at, j, j + 1);
                swap(bt, j, j + 1);
                swap(pid, j, j + 1);
                swap(ct, j, j + 1);
                swap(tat, j, j + 1);
                swap(wt, j, j + 1);
            }
}

int main() {
    int n, *pid, *bt, *at, *ct, *wt, *tat, avgWt = 0, avgTAT = 0, i;
    float avg_Wt, avg_TAT;
    
    printf("Enter no of processes:\n");
    scanf("%d", &n);

    // Dynamic memory allocation
    pid = (int*)malloc(n * sizeof(int));
    bt = (int*)malloc(n * sizeof(int));
    at = (int*)malloc(n * sizeof(int));
    ct = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    tat = (int*)malloc(n * sizeof(int));

    printf("Enter burst time and arrival time of each process:\n");
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        scanf("%d%d", &bt[i], &at[i]);
    }

    // sorting pid, at, and bt with respect to at
    sort(n, bt, at, pid);

    // Calculation of completion time
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        if (at[i] <= ct[i - 1]) {
            ct[i] = ct[i - 1] + bt[i];
        } else {
            ct[i] = at[i] + bt[i];
        }
    }

    // Calculation of waiting time and tat
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgWt += wt[i];
        avgTAT += tat[i];
    }

    avg_Wt = avgWt / (float)n;
    avg_TAT = avgTAT / (float)n;

    sortPids(n, pid, at, bt, ct, tat, wt);

    // Printing the table
    printf("Process id\tArrival time\tBurst time\tCompletion time\tTAT\tWaiting time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT is %f and average WT is %f\n", avg_TAT, avg_Wt);

    // Free allocated memory
    free(pid);
    free(bt);
    free(at);
    free(ct);
    free(wt);
    free(tat);

    return 0;
}
/*
Input and output:
Enter no of processes:
6
Enter burst time and arrival time of each process:
2 3
4 9
5 12
3 2
6 15
1 3
Process id      Arrival time    Burst time      Completion time TAT     Waiting time
1               3               2               7               4               2
2               9               4               13              4               0
3               12              5               18              6               1
4               2               3               5               3               0
5               15              6               24              9               3
6               3               1               8               5               4

Average TAT is 5.166667 and average WT is 1.666667
*/

