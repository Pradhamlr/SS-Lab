#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

int frames[MAX_SIZE], counter[MAX_SIZE], counts[MAX_SIZE], age[MAX_SIZE];

void initialize(int nf) {
    for(int i = 0; i < nf; i++) {
        frames[i] = -1;
        counter[i] = 0;
        counts[i] = 0;
        age[i] = 0;
    }
}

void fifo(int pages[], int n, int nf) {
    int page_faults = 0, page_hits = 0, index = 0;
    initialize(nf);

    for(int i = 0; i < n; i++) {
        int page = pages[i], flag = 0;

        for(int j = 0; j < nf; j++) {
            if(frames[j] == page) {
                page_hits++;
                flag = 1;
                break;
            }
        }

        if(!flag) {
            frames[index] = page;
            index = (index + 1) % nf;
            page_faults++;
        }
    }

    printf("FIFO Page Scheduling\nNumber Of Page Hits: %d\nNumber Of Page Faults: %d\n", page_hits, page_faults);
}

int findLru(int nf) {
    int max = INT_MIN, lruIndex = 0;

    for(int i = 0; i < nf; i++) {
        if(counter[i] > max) {
            max = counter[i];
            lruIndex = i;
        }
    }

    return lruIndex;
}

void lru(int pages[], int n, int nf) {
    int page_hits = 0, page_faults = 0;
    initialize(nf);

    for(int i = 0; i < n; i++) {
        int page = pages[i], flag = 0;

        for(int j = 0; j < nf; j++) {
            if(frames[j] == page) {
                page_hits++;
                counter[j] = 0;
                flag = 1;
                break;
            }
        }

        if(!flag) {
            int emptyIndex = -1;
            for(int j = 0; j < nf; j++) {
                if(frames[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if(emptyIndex != -1) {
                frames[emptyIndex] = page;
                counter[emptyIndex] = 0;
            }
            else {
                int lruIndex = findLru(nf);
                frames[lruIndex] = page;
                counter[lruIndex] = 0;
            }
            page_faults++;
        }

        for(int j = 0; j < nf; j++) {
            if(frames[j] != -1) {
                counter[j]++;
            }
        }
    }

    printf("LRU Page Scheduling\nNumber of Page Hits: %d\nNumber Of Page Faults: %d\n", page_hits, page_faults);
}

int findLfu(int nf) {
    int min = INT_MAX, oldest = INT_MAX, lfuIndex = 0;
    for(int i = 0; i < nf; i++) {
        if(counts[i] < min || (counts[i] == min && age[i] < oldest)) {
            lfuIndex = i;
            oldest = age[i];
            min = counts[i];
        }
    }

    return lfuIndex;
}

void lfu(int pages[], int n, int nf) {
    int page_hits = 0, page_faults = 0;
    int time = 0;
    initialize(nf);

    for(int i = 0; i < n; i++) {
        int page = pages[i], flag = 0;
        time++;

        for(int j = 0; j < nf; j++) {
            if(frames[j] == page) {
                page_hits++;
                counts[j]++;
                flag = 1;
                break;
            }
        }

        if(!flag) {
            int emptyIndex = -1;
            for(int j = 0; j < nf; j++) {
                if(frames[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if(emptyIndex != -1) {
                frames[emptyIndex] = page;
                counts[emptyIndex] = 1;
                age[emptyIndex] = time;
            }
            else {
                int lfuIndex = findLfu(nf);
                frames[lfuIndex] = page;
                age[lfuIndex] = time;
                counts[lfuIndex] = 1;
            }
            page_faults++;
        }
    }

    printf("LFU Page Scheduling\nNumber Of Page Hits: %d\nNumber of Page Faults: %d\n", page_hits, page_faults);
}



void main() {
    int n, nf;
    int pages[MAX_SIZE];

    printf("Enter Number Of Pages:\t");
    scanf("%d", &n);

    printf("Enter Number of Frames:\t");
    scanf("%d", &nf);

    printf("Enter Page Requests\n");
    for(int i = 0; i < n; i++) {
        printf("Enter Request %d:\t", i+1);
        scanf("%d", &pages[i]);
    }

    fifo(pages, n, nf);
    lru(pages, n, nf);
    lfu(pages, n, nf);
}
