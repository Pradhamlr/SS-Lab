#include <stdio.h>
#include <stdlib.h>
struct Node {
    int block;
    struct Node* next;
};

int main() {
    int disk[100] = {0};
    int n, numBlocks;

    scanf("%d", &n);

    for (int f = 1; f <= n; f++) {
        scanf("%d", &numBlocks);

        struct Node* head = NULL;
        struct Node* tail = NULL;
        int allocated = 1;

        for (int i = 0; i < numBlocks; i++) {
            int block;
            scanf("%d", &block);

            if (disk[block] == 0) {
                disk[block] = 1;

                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->block = block;
                newNode->next = NULL;

                if (head == NULL)
                    head = tail = newNode;
                else {
                    tail->next = newNode;
                    tail = newNode;
                }
            } else {
                allocated = 0;
                break;
            }
        }

        if (allocated) {
            struct Node* temp = head;
            while (temp) {
                printf("%d", temp->block);
                if (temp->next) printf(" -> ");
                temp = temp->next;
            }
            printf("\n");
        } else {
            printf("Allocation failed\n");
        }
    }

    return 0;
}

