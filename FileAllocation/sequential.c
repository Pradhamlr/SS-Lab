#include <stdio.h>

int main() {
    int n;
    int startBlock;
    int length;
    int disk[100] = {0};

    printf("Enter number of files to be allocated: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("\nEnter the starting block for file %d: ", i);
        scanf("%d", &startBlock);
        printf("Enter the number of blocks required for file %d: ", i);
        scanf("%d", &length);

        int allocated = 1;

        for (int j = startBlock; j < startBlock + length; j++) {
            if (disk[j] == 1) {
                allocated = 0;
                break;
            }
        }

        if (allocated) {
            for (int j = startBlock; j < startBlock + length; j++) {
                disk[j] = 1;
            }
            printf("Successfully allocated File %d from Block %d to Block %d\n",
                   i, startBlock, startBlock + length - 1);
        } else {
            printf("Allocation failed for File %d — some blocks are already occupied.\n", i);
        }
    }

    return 0;
}
