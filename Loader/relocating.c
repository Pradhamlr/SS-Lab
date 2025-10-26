#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char line[100];
    FILE *fp = fopen("object_code.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file.\n");  
        return 1;
    }

    int prog_start, load_addr;
    printf("Enter new starting address for loading (hex): ");
    scanf("%x", &load_addr);

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'H') {
            char prog[20], start[10], length[10];  
            sscanf(line, "H^%[^^]^%[^^]^%s", prog, start, length);  
            prog_start = (int)strtol(start, NULL, 16);
            printf("Program: %s, Original Start: %s, Length: %s\n", prog, start, length);
            printf("Loading at: %04X\n", load_addr);
        }
        else if (line[0] == 'T') {
            char start[10], len[10], obj[100];
            sscanf(line, "T^%[^^]^%[^^]^%[^\n]", start, len, obj);  
            int addr = (int)strtol(start, NULL, 16);
            int relocation = load_addr - prog_start;
            addr += relocation;

            int i = 0;  
            int obj_len = strlen(obj);
            while (i < obj_len && obj[i] != '$') {
                if (obj[i] != '^') {
                    char byte[3] = { obj[i], obj[i+1], '\0' };
                    printf("Address 00%04X: %s\n", addr, byte);
                    addr++;
                    i += 2;
                } else {
                    i++;
                }
            }
        }
        else if (line[0] == 'E') {
            char exec[10];
            if (sscanf(line, "E^%s", exec) == 1) {
                int exec_addr = (int)strtol(exec, NULL, 16) + (load_addr - prog_start);
                printf("Execution starts at: %04X\n", exec_addr);
            } else {
                printf("Execution starts at program start: %04X\n", load_addr);
            }
        }
    }

    fclose(fp);
    return 0;
}
