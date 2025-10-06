#include <stdio.h>
struct process 
{
    int at;
    int bt;
    int wt;
    int ta;
    int id;
    int completed;
    int remaining_bt;
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
void findTimes(struct process p[],int n,int tq)
{
    int currentTime=0;
    int completedno=0;
    for(int i=0;i<n;i++)
    {
        p[i].completed=0;
        p[i].remaining_bt=p[i].bt;
    }
    printf("GAANT CHART\n");
    while(completedno<n)
    {
        int done=1;
        for(int i=0;i<n;i++)
        {
            if(!p[i].completed&&p[i].at<=currentTime)
            {
                done=0;
                printf("|%d\t|P[%d]\t", currentTime, p[i].id);
                if(p[i].remaining_bt>tq)
                {
                    currentTime+=tq;
                    p[i].remaining_bt-=tq;
                }
                else
                {
                    currentTime+=p[i].remaining_bt;
                    p[i].ta=currentTime-p[i].at;
                    p[i].wt=p[i].ta-p[i].bt;
                    p[i].remaining_bt=0;
                    p[i].completed=1;
                    completedno++;
                    
                }
                printf("%d|\t", currentTime);
            }
            
        }
        if(done)
        {
            currentTime++;
        }
    }
}
void printr(struct process p[],int n)
{
    float totalwt=0.0;
    float totalta=0.0;
    printf("Round Robin\n");
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
    int tq;
    printf("Enter no: of processes: ");
    scanf("%d",&n);
    printf("Enter time quantum: ");
    scanf("%d",&tq);
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
    findTimes(p,n,tq);
    printr(p,n);
}
