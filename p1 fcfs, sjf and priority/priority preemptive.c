#include <stdio.h>

int main() {
    int n, bt[10], bt_copy[10], wt[10], tat[10], at[10], ct[10], p[10], pr[10], rt[10];
    int i, time = 0, completed = 0, highest, prev = -1;
    float avg_wt = 0, avg_tat = 0;
   
    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &pr[i]);
        bt_copy[i] = bt[i];
        rt[i] = bt[i]; // remaining time
    }
   
    printf("\nGantt Chart: ");
   
    while(completed < n) {
        highest = -1;
        int max_pr = 9999; // Lower number = higher priority
       
        // Find process with highest priority (lowest number)
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && pr[i] < max_pr) {
                max_pr = pr[i];
                highest = i;
            }
        }
       
        if(highest == -1) {
            time++;
            continue;
        }
       
        // Print process if changed
        if(prev != p[highest]) {
            printf("P%d ", p[highest]);
            prev = p[highest];
        }
       
        // Execute for 1 unit
        rt[highest]--;
        time++;
       
        // If process completed
        if(rt[highest] == 0) {
            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];
            completed++;
        }
    }
   
    printf("\n\nP\tAT\tBT\tPR\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt_copy[i], pr[i], ct[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
   
    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);
   
    return 0;
}