#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int main() {
    int n, head;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[MAX];

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    int total = 0, prev = head, dist;

    printf("\nFCFS Disk Scheduling\n");
    printf("Step\tFrom\tTo\tSeek\n");

    for (int i = 0; i < n; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\n", i + 1, prev, req[i], dist);

        prev = req[i];
    }

    printf("\nTotal Seek Movement = %d\n", total);
    printf("Average Seek Time = %.2f\n", (float)total / n);

    return 0;
}