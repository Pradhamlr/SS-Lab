#include <stdio.h>
#include <stdlib.h>

struct process
{
    int id;
    int at;
    int bt;
    int wt;
    int ta;
    int completed;
};

void swap(struct process p[],int i,int j)
{
    struct process temp=p[i];
    p[i]=p[j];
    p[j]=temp;
}

void sortByArrival(struct process p[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].at>p[j+1].at)
            {
                swap(p,j,j+1);
            }
        }
    }
}

// SJF
void findTimes_sjf(struct process p[],int n)
{
    int currentTime=0;
    int completedno=0;
    for(int i=0;i<n;i++)
    {
        p[i].completed=0;
    }
    printf("GAANT CHART\n");
    while(completedno<n)
    {
        int minbt=14567;
        int index=-1;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=currentTime && !p[i].completed && p[i].bt<minbt)
            {
                index=i;
                minbt=p[i].bt;
            }
        }
        if(index==-1)
        {
            currentTime++;
            continue;
        }
        printf("|%d\t|P[%d]|\t%d|\t",currentTime,p[index].id,currentTime+p[index].bt);
        p[index].wt=currentTime-p[index].at;
        p[index].ta=p[index].wt+p[index].bt;
        currentTime+=p[index].bt;
        p[index].completed=1;
        completedno++;
    }
    printf("\n");
}

void print_sjf(struct process p[],int n)
{
    float totalwt=0.0;
    float totalta=0.0;
    printf("SJF SCHEDULING\n");
    printf("PID\tAT\tBT\tWT\tTA\n");
    for(int i=0;i<n;i++)
    {
        totalwt+=p[i].wt;
        totalta+=p[i].ta;
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].wt,p[i].ta);
    }
    printf("Average waiting time: %.2f\n",totalwt/n);
    printf("Average turnaround time: %.2f\n",totalta/n);
}

void run_sjf()
{
    int n;
    printf("Enter no: of processes: ");
    if(scanf("%d",&n)!=1) return;
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].id=i+1;
        printf("Enter arrival time for PID %d: ",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time for PID %d: ",i+1);
        scanf("%d",&p[i].bt);
    }
    sortByArrival(p,n);
    findTimes_sjf(p,n);
    print_sjf(p,n);
}

// FCFS
void findTimes_fcfs(struct process p[],int n)
{
    int currentTime=0;
    printf("GAANT CHART\n");
    for(int i=0;i<n;i++)
    {
        if(currentTime<p[i].at)
        {
            currentTime=p[i].at;
        }
        printf("|%d\t|P[%d]|\t%d|\t",currentTime,p[i].id,currentTime+p[i].bt);
        p[i].wt=currentTime-p[i].at;
        p[i].ta=p[i].wt+p[i].bt;
        currentTime+=p[i].bt;
    }
}

void print_fcfs(struct process p[],int n)
{
    printf("\nFCFS Scheduling\n");
    printf("Process\tAT\tBT\tWT\tTA\n");
    float totalwt=0.0;
    float totalta=0.0;
    for(int i=0;i<n;i++)
    {
        totalwt+=p[i].wt;
        totalta+=p[i].ta;
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].wt,p[i].ta);
    }

    printf("\nAverage Waiting Time : %.2f",totalwt/n);
    printf("\nAverage Turnaround Time : %.2f\n",totalta/n);
}

void run_fcfs()
{
    int n;
    printf("Enter no of process: ");
    if(scanf("%d",&n)!=1) return;
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].id=i+1;
        printf("Enter process arrival time: ");
        scanf("%d",&p[i].at);
        printf("Enter process burst time: ");
        scanf("%d",&p[i].bt);
    }
    sortByArrival(p,n);
    findTimes_fcfs(p,n);
    print_fcfs(p,n);
}

int main(void)
{
    int choice=0;
    do
    {
        printf("\n--- Menu ---\n");
        printf("1. SJF\n");
        printf("2. FCFS\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        if(scanf("%d",&choice)!=1) break;
        switch(choice)
        {
            case 1:
                run_sjf();
                break;
            case 2:
                run_fcfs();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice!=3);
    return 0;
}
