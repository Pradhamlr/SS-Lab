#include <stdio.h>
struct process
{
    int id;
    int bt;
    int at;
    int wt;
    int ta;
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

void findTimes(struct process p[],int n)
{
    int currentTime=0;
    for(int i=0;i<n;i++)
    {
        if(currentTime<p[i].at)
        {
            currentTime=p[i].at;
        }
        p[i].wt=currentTime-p[i].at;
        p[i].ta=p[i].wt+p[i].bt;
        currentTime+=p[i].bt;
    }
}

void printr(struct process p[],int n)
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

   
    printf("\nGantt Chart:\n ");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].bt;j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].bt-1;j++)
            printf(" ");
        printf("P%d",p[i].id);
        for(int j=0;j<p[i].bt-1;j++)
            printf(" ");
        printf("|");
    }

    printf("\n ");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].bt;j++)
            printf("--");
        printf(" ");
    }

    // Time line
    printf("\n");
    int time=0;
    printf("%d",p[0].at>0?p[0].at:0);
    time=(p[0].at>0)?p[0].at:0;

    for(int i=0;i<n;i++)
    {
        if(time<p[i].at)
            time=p[i].at;
        time+=p[i].bt;
        printf("%*d",p[i].bt*2,time); 
    }
    printf("\n");
}

void main()
{
    int n;
    printf("Enter no of process: ");
    scanf("%d",&n);
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
    findTimes(p,n);
    printr(p,n);
}
