#include <stdio.h>

int main() {
    int n, i, time = 0, remain, tq;
    int at[20], bt[20], rt[20];
    int wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    printf("Enter Arrival Time and Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while(remain != 0) {
        int done = 1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0) {
                done = 0;

                if(rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;

                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];

                    avg_wt += wt[i];
                    avg_tat += tat[i];

                    remain--;
                }
                else {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }

        if(done)
            time++;
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}