#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
    int done; // 0 = false, 1 = true
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
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    int time = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;

    // Gantt chart arrays
    char ganttProc[100][10];
    int ganttTime[100];
    int gIndex = 0;

    ganttTime[gIndex++] = 0;

    while (completed < n) {
        int idx = -1;
        int minAT = INT_MAX;

        // 🔥 FCFS selection → earliest arrival time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].at < minAT) {
                minAT = p[i].at;
                idx = i;
            }
        }

        if (idx == -1) {
            // CPU Idle
            time++;
            if (gIndex == 1 || strcmp(ganttProc[gIndex - 2], "IDLE") != 0) {
                sprintf(ganttProc[gIndex - 1], "IDLE");
                ganttTime[gIndex++] = time;
            } else {
                ganttTime[gIndex - 1] = time;
            }
        } else {
            // Execute process
            sprintf(ganttProc[gIndex - 1], "P%d", p[idx].pid);

            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;

            p[idx].done = 1;
            completed++;

            ganttTime[gIndex++] = time;
        }
    }

    // Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2lf\n", totalWT / n);
    printf("Average Turnaround Time = %.2lf\n", totalTAT / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gIndex - 1; i++) {
        printf("| %s ", ganttProc[i]);
    }
    printf("|\n");

    for (int i = 0; i < gIndex; i++) {
        printf("%d\t", ganttTime[i]);
    }

    return 0;
}