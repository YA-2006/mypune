#include <stdio.h>

struct Process {
    int pid, at, bt;
    int rt, ct, tat, wt;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;

    int ganttPID[1000], ganttTime[1000];
    int gIndex = 0;

    ganttTime[0] = 0;

    while (completed < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                found = 1;

                if (gIndex == 0 || ganttPID[gIndex - 1] != p[i].pid)
                    ganttPID[gIndex++] = p[i].pid;

                int exec = (p[i].rt > tq) ? tq : p[i].rt;

                p[i].rt -= exec;
                time += exec;
                ganttTime[gIndex] = time;

                if (p[i].rt == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    totalWT += p[i].wt;
                    totalTAT += p[i].tat;
                    completed++;
                }
            }
        }

        if (!found) {
            if (gIndex == 0 || ganttPID[gIndex - 1] != 0)
                ganttPID[gIndex++] = 0;

            time++;
            ganttTime[gIndex] = time;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage WT = %.2lf\n", totalWT / n);
    printf("Average TAT = %.2lf\n", totalTAT / n);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < gIndex; i++) {
        if (ganttPID[i] == 0)
            printf("| IDLE ");
        else
            printf("| P%d ", ganttPID[i]);
    }
    printf("|\n");

    for (int i = 0; i <= gIndex; i++)
        printf("%d ", ganttTime[i]);

    printf("\n");

    return 0;
}