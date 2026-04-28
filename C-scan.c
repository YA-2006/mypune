#include <stdio.h>
#include <stdlib.h>

#define MAX 15        // number of requests
#define DISK_MAX 199  // highest cylinder
#define DISK_MIN 0    // lowest cylinder

// 🔹 Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {

    int n, head;

    printf("Enter number of requests (<=15): ");
    scanf("%d", &n);

    int req[MAX];

    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    int total = 0, prev = head, dist;

    // 🔹 Sort requests
    qsort(req, n, sizeof(int), compare);

    // 🔹 Find split point
    int split = 0;
    while (split < n && req[split] < head)
        split++;

    printf("\nC-SCAN Disk Scheduling\n");
    printf("Step\tFrom\tTo\tSeek\tAction\n");

    int step = 1;

    // 🔹 Service requests to the right of head
    for (int i = split; i < n; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n",
               step++, prev, req[i], dist);

        prev = req[i];
    }

    // 🔹 Move to end of disk
    dist = abs(DISK_MAX - prev);
    total += dist;

    printf("%d\t%d\t%d\t%d\tGo End\n",
           step++, prev, DISK_MAX, dist);

    prev = DISK_MAX;

    // 🔹 Jump to beginning
    dist = abs(DISK_MIN - prev);
    total += dist;

    printf("%d\t%d\t%d\t%d\tJump\n",
           step++, prev, DISK_MIN, dist);

    prev = DISK_MIN;

    // 🔹 Service remaining requests
    for (int i = 0; i < split; i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n",
               step++, prev, req[i], dist);

        prev = req[i];
    }

    printf("\nTotal Seek Movement = %d\n", total);
    printf("Average Seek Time = %.2f\n", (float)total / n);

    return 0;
}