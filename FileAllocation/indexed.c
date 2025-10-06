#include <stdio.h>

int main() {
    int n;
    int indexBlock;
    int length;
    int block;
    int disk[100] = {0};

    printf("Enter number of files to be allocated: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("\nEnter the index block for file %d: ", i);
        scanf("%d", &indexBlock);

        if (disk[indexBlock] == 1) {
            printf("Index block already allocated. Choose another block.\n");
            i--;
            continue;
        }

        printf("Enter the number of blocks required for file %d: ", i);
        scanf("%d", &length);

        int fileBlocks[100];
        int success = 1;

        printf("Enter the blocks to be allocated for this file:\n");

        for (int j = 0; j < length; j++) {
            scanf("%d", &block);

            if (disk[block] == 1 || block == indexBlock) {
                printf("Block %d already allocated! Try again.\n", block);
                success = 0;
                break;
            }

            fileBlocks[j] = block;
        }

        if (success) {
            disk[indexBlock] = 1;
            for (int j = 0; j < length; j++)
                disk[fileBlocks[j]] = 1;

            printf("File %d allocated successfully.\n", i);
            printf("Index Block: %d -> Blocks: ", indexBlock);
            for (int j = 0; j < length; j++)
                printf("%d ", fileBlocks[j]);
            printf("\n");
        } else {
            printf("Allocation failed for File %d.\n", i);
        }
    }

    return 0;
}
