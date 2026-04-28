#include <stdio.h>

struct Process {
    int pid, at, bt;
    int rt, ct, tat, wt;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // remaining time
    }

    int time = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;

    // Gantt chart (clean version)
    int ganttPID[1000];   // 0 = IDLE
    int ganttTime[1000];
    int gIndex = 0;

    ganttTime[0] = 0;

    while (completed < n) {
        int idx = -1;
        int minRT = 999999;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            // CPU IDLE
            if (gIndex == 0 || ganttPID[gIndex - 1] != 0) {
                ganttPID[gIndex] = 0;
                gIndex++;
            }
            time++;
            ganttTime[gIndex] = time;
        }
        else {
            // Add new block if process changes
            if (gIndex == 0 || ganttPID[gIndex - 1] != p[idx].pid) {
                ganttPID[gIndex] = p[idx].pid;
                gIndex++;
            }

            // Execute for 1 unit
            p[idx].rt--;
            time++;
            ganttTime[gIndex] = time;

            // If completed
            if (p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
                completed++;
            }
        }
    }

    // Output table
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