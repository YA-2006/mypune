#include <stdio.h>
#include <stdlib.h>

#define MAX 15
#define DISK_MAX 199
#define DISK_MIN 0

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

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

    qsort(req, n, sizeof(int), compare);

    int split = 0;
    while (split < n && req[split] < head)
        split++;

    printf("\nSCAN Disk Scheduling\n");
    printf("Step\tFrom\tTo\tSeek\tAction\n");

    int step = 1;

    // Right side
    for (int i = split; i < n; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n", step++, prev, req[i], dist);

        prev = req[i];
    }

    // Go to end
    dist = abs(DISK_MAX - prev);
    total += dist;

    printf("%d\t%d\t%d\t%d\tGo End\n", step++, prev, DISK_MAX, dist);

    prev = DISK_MAX;

    // Left side
    for (int i = split - 1; i >= 0; i--) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n", step++, prev, req[i], dist);

        prev = req[i];
    }

    printf("\nTotal Seek Movement = %d\n", total);
    printf("Average Seek Time = %.2f\n", (float)total / n);

    return 0;
}