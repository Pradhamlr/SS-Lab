#include <stdio.h>

struct process
{
    int id;
    int bt;
    int at;
    int wt;
    int ta;
    int start;
    int end;
};

void swap(struct process p[], int i, int j)
{
    struct process temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

void sortByArrival(struct process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                swap(p, j, j + 1);
            }
        }
    }
}

void findTimes(struct process p[], int n)
{
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].at)
        {
            currentTime = p[i].at;
        }
        p[i].start = currentTime;
        p[i].wt = currentTime - p[i].at;
        p[i].ta = p[i].wt + p[i].bt;
        currentTime += p[i].bt;
        p[i].end = currentTime;
    }
}

void printr(struct process p[], int n)
{
    printf("\nFCFS Scheduling\n");
    printf("Process\tAT\tBT\tWT\tTA\n");
    float totalwt = 0.0, totalta = 0.0;

    for (int i = 0; i < n; i++)
    {
        totalwt += p[i].wt;
        totalta += p[i].ta;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].ta);
    }

    printf("\nAverage Waiting Time : %.2f", totalwt / n);
    printf("\nAverage Turnaround Time : %.2f\n", totalta / n);

 
    printf("\nGantt Chart:\n");

    // Upper bar
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].bt; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

  
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].bt - 1; j++)
            printf(" ");
        printf("P%d", p[i].id);
        for (int j = 0; j < p[i].bt - 1; j++)
            printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].bt; j++)
            printf("--");
        printf(" ");
    }

  
    printf("\n");

    printf("%d", p[0].start);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].bt; j++)
            printf("  ");
        if (p[i].end > 9)
            printf("\b"); 
        printf("%d", p[i].end);
    }
    printf("\n");
}

void main()
{
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    sortByArrival(p, n);
    findTimes(p, n);
    printr(p, n);
}
