#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int pid, at, bt, pr;
    int rt, ct, tat, wt;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
    }

    int time = 0, completed = 0, prev = -1;
    double totalWT = 0, totalTAT = 0;

    char gantt[1000][20];   // stores process names
    int times[1000];        // stores time points
    int gIndex = 0, tIndex = 0;

    while (completed < n) {
        int idx = -1;
        int bestPr = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].pr < bestPr) {
                bestPr = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            if (prev != -2) {
                strcpy(gantt[gIndex++], "IDLE");
                times[tIndex++] = time;
                prev = -2;
            }
            time++;
            continue;
        }

        if (prev != idx) {
            sprintf(gantt[gIndex++], "P%d", p[idx].pid);
            times[tIndex++] = time;
            prev = idx;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        }
    }

    times[tIndex++] = time;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2lf\n", totalWT / n);
    printf("Average Turnaround Time = %.2lf\n", totalTAT / n);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < gIndex; i++) {
        printf("| %s ", gantt[i]);
    }
    printf("|\n");

    for (int i = 0; i < tIndex; i++) {
        printf("%d\t", times[i]);
    }
    printf("\n");

    return 0;
}
/*
7
2 2 3
1 5 6
7 3 2
3 6 4 
6 4 5
2 2 1 
10 2 0
*/