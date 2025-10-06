#include <stdio.h>
#include <stdlib.h>


#define MAX_REQUESTS 100
#define DISK_SIZE 200


void sort(int requests[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
}


int fcfs(int requests[], int n, int head) {
    int totalSeek = 0, current = head;
    for(int i = 0; i < n; i++) {
        totalSeek += abs(current - requests[i]);
        current = requests[i];
    }


    return totalSeek;
}




int scan(int requests[], int n, int head) {
    int totalSeek = 0, current = head;
    sort(requests, n);


    for(int i = 0; i < n; i++) {
        if(requests[i] >= head) {
            totalSeek += abs(current - requests[i]);
            current = requests[i];
        }
    }


    totalSeek += abs(current - (DISK_SIZE - 1));
    current = DISK_SIZE - 1;


    for(int i = n-1; i >= 0; i--) {
        if(requests[i] < head) {
            totalSeek += abs(current - requests[i]);
            current = requests[i];
        }
    }


    return totalSeek;
}


int cScan(int requests[], int n, int head) {
    int totalSeek = 0, current = head;
    sort(requests, n);


    for(int i = 0; i < n; i++) {
        if(requests[i] >= head) {
            totalSeek += abs(current - requests[i]);
            current = requests[i];
        }
    }


    totalSeek += abs(current - (DISK_SIZE - 1));
    totalSeek += DISK_SIZE - 1;
    current = 0;


    for(int i = 0; i < n; i++) {
        if(requests[i] < head) {
            totalSeek += abs(current - requests[i]);
            current = requests[i];
        }
    }


    return totalSeek;
}


void main() {
    int requests[MAX_REQUESTS], n, head;
    printf("Enter Number Of Disk Requests:\t");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("Enter Request %d:\t", i+1);
        scanf("%d", &requests[i]);
    }
    printf("Enter Starting Head Position:\t");
    scanf("%d", &head);


    printf("Total Seek Time For FCFS: %d\n", fcfs(requests, n, head));
    printf("Total Seek Time For SCAN: %d\n", scan(requests, n, head));
    printf("Total Seek Time For CSCAN: %d\n", cScan(requests, n, head));
}
