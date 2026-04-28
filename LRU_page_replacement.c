#include <stdio.h>

#define FRAMES 3
#define PAGES 15

// Check if page is in frames
int isPageInFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return i;   // return index
    }
    return -1;
}

int main() {

    int refStr[PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
    int frames[FRAMES];
    int lastUsed[FRAMES];   // stores last used time

    int pageFaults = 0;

    // Initialize
    for (int i = 0; i < FRAMES; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("%-6s %-6s %-8s %-8s %-8s %-12s\n",
           "Step", "Page", "Frame1", "Frame2", "Frame3", "Result");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < PAGES; i++) {

        int page = refStr[i];
        int index = isPageInFrames(frames, FRAMES, page);

        if (index != -1) {
            // HIT
            lastUsed[index] = i;
        } else {
            // PAGE FAULT
            pageFaults++;

            int lruIndex = 0;

            for (int j = 1; j < FRAMES; j++) {
                if (lastUsed[j] < lastUsed[lruIndex])
                    lruIndex = j;
            }

            frames[lruIndex] = page;
            lastUsed[lruIndex] = i;
        }

        // Print
        printf("%-6d %-6d", i + 1, page);

        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == -1)
                printf(" %-8s", "-");
            else
                printf(" %-8d", frames[j]);
        }

        if (index != -1)
            printf(" HIT\n");
        else
            printf(" PAGE FAULT\n");
    }

    printf("-------------------------------------------------------------\n");
    printf("Total Page Faults : %d\n", pageFaults);
    printf("Total Page Hits   : %d\n", PAGES - pageFaults);

    return 0;
}