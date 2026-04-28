#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int ct, tat, wt;
    int done; // 0 = not done, 1 = completed
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].done = 0;
        printf("Enter AT, BT, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }

    int time = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;

    // Gantt chart
    int ganttPID[100];   // 0 = IDLE
    int ganttTime[100];
    int gIndex = 0;

    ganttTime[0] = 0;

    while (completed < n) {
        int idx = -1;
        int bestPr = 999999;

        // Select highest priority process (lowest value)
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].pr < bestPr) {
                    bestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU is IDLE
            if (gIndex == 0 || ganttPID[gIndex - 1] != 0) {
                ganttPID[gIndex] = 0;
                gIndex++;
            }
            time++;
            ganttTime[gIndex] = time;
        } else {
            // Execute FULL process (non-preemptive)
            ganttPID[gIndex] = p[idx].pid;
            gIndex++;

            time += p[idx].bt;
            ganttTime[gIndex] = time;

            // Calculate values
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;

            p[idx].done = 1;
            completed++;
        }
    }

    // Output table
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2lf\n", totalWT / n);
    printf("Average Turnaround Time = %.2lf\n", totalTAT / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gIndex; i++) {
        if (ganttPID[i] == 0)
            printf("| IDLE ");
        else
            printf("|  P%d  ", ganttPID[i]);
    }
    printf("|\n");

    for (int i = 0; i <= gIndex; i++) {
        printf("%-7d", ganttTime[i]);
    }
    printf("\n");

    return 0;
}