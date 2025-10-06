#include <stdio.h>

struct process {
    int id;
    int bt;  // Burst Time
    int at;  // Arrival Time
    int priority; // Priority (Lower value = Higher priority)
    int wt;  // Waiting Time
    int ta;  // Turnaround Time
    int completed; // Flag to check if process is completed
};

// Function to swap processes
void swap(struct process p[], int i, int j) {
    struct process temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

// Sorting by Arrival Time
void sortByArrival(struct process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                swap(p, j, j + 1);
            }
        }
    }
}

// Find Waiting and Turnaround Time for Priority Scheduling (Non-Preemptive)
void findTimes(struct process p[], int n) {
    int currentTime = 0, completedProcesses = 0;

    for (int i = 0; i < n; i++) {
        p[i].completed = 0; // Mark all processes as not completed
    }

    printf("Gantt Chart\n");

    while (completedProcesses < n) {
        int highestPriority = 1e9, index = -1;
        
        // Find the process with the highest priority (lowest priority number)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].completed && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                index = i;
            }
        }

        // If no process is available, move time forward
        if (index == -1) {
            currentTime++;
            continue;
        }

        printf("|%d\t|P[%d]|\t%d\t|", currentTime, p[index].id, currentTime + p[index].bt);

        // Process execution
        p[index].wt = currentTime - p[index].at;
        p[index].ta = p[index].wt + p[index].bt;
        currentTime += p[index].bt;
        p[index].completed = 1; // Mark process as completed
        completedProcesses++;
    }
}

// Print Process Table
void printr(struct process p[], int n) {
    printf("\nPriority Scheduling (Non-Preemptive)\n");
    printf("PID\tAT\tBT\tPriority\tWT\tTA\n");
    float totalwt = 0.0, totalta = 0.0;

    for (int i = 0; i < n; i++) {
        totalwt += p[i].wt;
        totalta += p[i].ta;
        printf("%d  \t%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].ta);
    }

    printf("Avg WT: %.2f\n", totalwt / n);
    printf("Avg TA: %.2f\n", totalta / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter process arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter process burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter process priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
    }

    sortByArrival(p, n);
    findTimes(p, n);
    printr(p, n);

    return 0;
}
