#include <stdio.h>

struct Process {
    int pid, at, bt, type;
    int ct, tat, wt;
};

int main() {
    int n, i, j, time = 0;
    struct Process p[20], temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (AT BT TYPE[0-System,1-User]): ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);
    }

    // Sort: System first, then by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if ((p[i].type > p[j].type) || 
               (p[i].type == p[j].type && p[i].at > p[j].at)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Execution
    for (i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Output
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].type,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}