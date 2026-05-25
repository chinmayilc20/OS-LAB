#include <stdio.h>

#define MAX 10

typedef struct {
    int id, C, T, D;
    int rem, next, deadline;
} Task;

void init(Task t[], int n) {
    for (int i = 0; i < n; i++) {
        t[i].rem = 0;
        t[i].next = 0;
    }
}

/* -------- COMPRESSED GANTT PRINT -------- */
void printCompressed(int sched[], int time) {
    int i = 0;

    printf("\n");

    // Print blocks
    while (i < time) {
        if (sched[i] == -1)
            printf("Idle | ");
        else
            printf("T%d | ", sched[i] + 1);

        int j = i + 1;
        while (j < time && sched[j] == sched[i])
            j++;

        i = j;
    }

    printf("\n0 ");

    // Print time markers
    i = 0;
    while (i < time) {
        int j = i + 1;
        while (j < time && sched[j] == sched[i])
            j++;

        printf(" %d ", j);
        i = j;
    }

    printf("\n");
}

/* -------- RMS -------- */
void RMS(Task t[], int n, int time) {
    int sched[50];

    for (int tt = 0; tt < time; tt++) {
        for (int i = 0; i < n; i++)
            if (tt == t[i].next) {
                t[i].rem = t[i].C;
                t[i].next += t[i].T;
            }

        int sel = -1;
        for (int i = 0; i < n; i++)
            if (t[i].rem > 0 &&
               (sel == -1 || t[i].T < t[sel].T))
                sel = i;

        sched[tt] = sel;

        if (sel != -1)
            t[sel].rem--;
    }

    printf("\n--- RMS ---");
    printCompressed(sched, time);
}

/* -------- EDF -------- */
void EDF(Task t[], int n, int time) {
    int sched[50];

    for (int tt = 0; tt < time; tt++) {
        for (int i = 0; i < n; i++)
            if (tt == t[i].next) {
                t[i].rem = t[i].C;
                t[i].deadline = tt + t[i].D;
                t[i].next += t[i].T;
            }

        int sel = -1;
        for (int i = 0; i < n; i++)
            if (t[i].rem > 0 &&
               (sel == -1 || t[i].deadline < t[sel].deadline))
                sel = i;

        sched[tt] = sel;

        if (sel != -1)
            t[sel].rem--;
    }

    printf("\n--- EDF ---");
    printCompressed(sched, time);
}

/* -------- PROPORTIONAL -------- */
void PS(Task t[], int n, int time) {
    int sched[50];

    for (int tt = 0; tt < time; tt++) {
        float max = -1;
        int sel = -1;

        for (int i = 0; i < n; i++) {
            float share = (float)t[i].C / t[i].T;
            if (share > max) {
                max = share;
                sel = i;
            }
        }

        sched[tt] = sel;
    }

    printf("\n--- Proportional ---");
    printCompressed(sched, time);
}

/* -------- MAIN -------- */
int main() {
    int n, time;
    Task t[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);
        t[i].id = i + 1;

        printf("Execution Time: ");
        scanf("%d", &t[i].C);

        printf("Period: ");
        scanf("%d", &t[i].T);

        printf("Deadline: ");
        scanf("%d", &t[i].D);
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &time);

    init(t, n);
    RMS(t, n, time);

    init(t, n);
    EDF(t, n, time);

    PS(t, n, time);

    return 0;
}