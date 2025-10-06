#include <stdio.h>
struct process 
{
    int at;
    int bt;
    int wt;
    int ta;
    int id;
    int completed;
};
void swap(struct process p[],int i,int j)
{
    struct process temp=p[i];
    p[i]=p[j];
    p[j]=temp;
}
void sortByArrival(struct  process p[],int n)
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
            if(p[i].at<=currentTime&&!p[i].completed&&p[i].bt<minbt)
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
void printr(struct process p[],int n)
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
void main()
{
    int n;
    printf("Enter no: of processes: ");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].id=i+1;
        printf("Enter arrival time for PID %d; ",i+1);
        scanf("%d",&p[i].at);
        printf("Enter burst time for PID %d; ",i+1);
        scanf("%d",&p[i].bt);
    }
    sortByArrival(p,n);
    findTimes(p,n);
    printr(p,n);
}
