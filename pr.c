#include<stdio.h>
#include<stdlib.h>

#define MAX 15
#define DISK_MAX 199
#define DISK_MIN 0

int compare(const void *a,const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    printf("Enter the no. of request : ");
    scanf("%d",&n);

    int req[MAX];

    printf("Enter the req seq : \n");
    for (int  i = 0; i < n; i++)
    {
        scanf("%d",&req[i]);
    }
    int head;
    printf("ENter the intial head position ");
    scanf("%d",&head);

    qsort(req,n,sizeof(int),compare);

    int split=0;
    while (split < n && req[split] < head)
    {
        split++;
    }

    printf("\nSCAN Disk Scheduling\n");
    printf("Step\tfrom\tto\tseek\tAction\n");

    int step=1;

    int prev=head;
    int total=0;
    int dist=0;

    for(int i=split;i<n;i++) {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n",step++,prev,req[i],dist);
        prev = req[i];
    }

    dist = (DISK_MAX - prev);
    total += dist;

    printf("%d\t%d\t%d\t%d\tGo End\n", step++, prev, DISK_MAX, dist);


    prev = DISK_MAX;


    for (int i = split-1; i >= 0; i--)
    {
        dist = abs(req[i] - prev);
        total += dist;

        printf("%d\t%d\t%d\t%d\tService\n", step++, prev, req[i], dist);

        prev = req[i];
    }

    printf("Total Seek Movment = %d",total);
    printf("Average Seek Time = %.2f\n", (float)total / n);
    
    

    
    
    return 0;
}