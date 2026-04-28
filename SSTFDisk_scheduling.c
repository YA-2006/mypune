#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int main() {
    int n, head;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[MAX], visited[MAX] = {0};

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    int total = 0, prev = head, dist;

    printf("\nSSTF Disk Scheduling\n");
    printf("Step\tFrom\tTo\tSeek\n");

    for (int i = 0; i < n; i++) {

        int minDist = 1e9, index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int d = abs(req[j] - prev);
                if (d < minDist) {
                    minDist = d;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += minDist;

        printf("%d\t%d\t%d\t%d\n", i + 1, prev, req[index], minDist);

        prev = req[index];
    }

    printf("\nTotal Seek Movement = %d\n", total);
    printf("Average Seek Time = %.2f\n", (float)total / n);

    return 0;
}
