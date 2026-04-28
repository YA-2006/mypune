#include <stdio.h>

#define FRAMES 3
#define PAGES 15

int isPageInFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int main() {

    int refStr[PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
    int frames[FRAMES];
    int pageFaults = 0;

    int front = 0;

    for (int i = 0; i < FRAMES; i++)
        frames[i] = -1;

    printf("%-6s %-6s %-8s %-8s %-8s %-12s\n",
           "Step", "Page", "Frame1", "Frame2", "Frame3", "Result");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < PAGES; i++) {

        int page = refStr[i];

        // store result BEFORE modification
        int hit = isPageInFrames(frames, FRAMES, page);

        if (!hit) {
            pageFaults++;
            frames[front] = page;
            front = (front + 1) % FRAMES;
        }

        printf("%-6d %-6d", i + 1, page);

        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == -1)
                printf(" %-8s", "-");
            else
                printf(" %-8d", frames[j]);
        }

        if (hit)
            printf(" HIT\n");
        else
            printf(" PAGE FAULT\n");
    }

    printf("-------------------------------------------------------------\n");
    printf("Total Page Faults : %d\n", pageFaults);
    printf("Total Page Hits   : %d\n", PAGES - pageFaults);
    printf("Page Fault Rate   : %.2f%%\n",
           ((float)pageFaults / PAGES) * 100);

    return 0;
}