#include <stdio.h>
#include <stdlib.h>

#define MAX 15

// Comparator for sorting
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

    // Sort requests
    qsort(req, n, sizeof(int), compare);

    // Find split point
    int split = 0;
    while (split < n && req[split] < head)
        split++;

    printf("\nC-LOOK Disk Scheduling\n");
    printf("Step\tFrom\tTo\tSeek\tAction\n");

    int step = 1;

    // 🔸 Move RIGHT first
    for (int i = split; i < n; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n", step++, prev, req[i], dist);

        prev = req[i];
    }

    // 🔸 Jump to first request (circular move)
    if (split > 0) {
        dist = abs(prev - req[0]);
        total += dist;

        printf("%d\t%d\t%d\t%d\tJump\n", step++, prev, req[0], dist);

        prev = req[0];
    }

    // 🔸 Continue servicing on left side
    for (int i = 0; i < split; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n", step++, prev, req[i], dist);

        prev = req[i];
    }

    printf("\nTotal Seek Movement = %d\n", total);
    printf("Average Seek Time = %.2f\n", (float)total / n);

    return 0;
}