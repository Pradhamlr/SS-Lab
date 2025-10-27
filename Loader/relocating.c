#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hex_to_binary(char hex[], char bin[]);

int main()
{
    char line[100];
    int actual_start;
    FILE *fp = fopen("object_code.txt", "r");
    
    if(fp == NULL)
    {
        printf("File Open Failed");
        return 1;
    }
    
    printf("Enter the actual starting address: ");
    scanf("%x", &actual_start);
    
    while(fgets(line, sizeof(line), fp))
    {
        if(line[0] == 'H')
        {
            char prog[20], start[20], length[20];
            sscanf(line, "H^%[^^]^%[^^]^%s", prog, start, length);
            printf("Program name:%s ,Starting address:%s ,Length of Program:%s\n", prog, start, length);
        }
        else if(line[0] == 'T')
        {
            char start[10], length[20], bitmask[10], obj[100], binmask[40];
            sscanf(line, "T^%[^^]^%[^^]^%[^^]^%[^\n]", start, length, bitmask, obj);
            
            int text_addr = (int)strtol(start, NULL, 16) + actual_start;
            hex_to_binary(bitmask, binmask);
            
            printf("\nBitmask: %s -> Binary: %s\n", bitmask, binmask);
            printf("Address\t\tObject Code\n");
            
            int i = 0, bit_index = 0;
            int len = strlen(obj);
            
            while(i < len && obj[i] != '$')
            {
                if(obj[i] != '^')
                {
                    char instruction[7] = {0};
                    strncpy(instruction, &obj[i], 6);
                    
                    int opcode, addr;
                    sscanf(instruction, "%2x%4x", &opcode, &addr);
                    
                    if(binmask[bit_index] == '1')
                        addr += actual_start;
                    
                    printf("%04X\t\t%02X%04X\n", text_addr, opcode, addr);
                    
                    text_addr += 3;
                    bit_index++;
                    i += 6;
                }
                else
                {
                    i++;
                }
            }
        }
        else
        {
            printf("End of program\n");
        }
    }
    
    fclose(fp);
    return 0;
}

void hex_to_binary(char hex[], char bin[])
{
    int i;
    strcpy(bin, "");
    
    for(i = 0; i < strlen(hex); i++)
    {
        switch(hex[i])
        {
            case '0': strcat(bin, "0000"); break;
            case '1': strcat(bin, "0001"); break;
            case '2': strcat(bin, "0010"); break;
            case '3': strcat(bin, "0011"); break;
            case '4': strcat(bin, "0100"); break;
            case '5': strcat(bin, "0101"); break;
            case '6': strcat(bin, "0110"); break;
            case '7': strcat(bin, "0111"); break;
            case '8': strcat(bin, "1000"); break;
            case '9': strcat(bin, "1001"); break;
            case 'A': case 'a': strcat(bin, "1010"); break;
            case 'B': case 'b': strcat(bin, "1011"); break;
            case 'C': case 'c': strcat(bin, "1100"); break;
            case 'D': case 'd': strcat(bin, "1101"); break;
            case 'E': case 'e': strcat(bin, "1110"); break;
            case 'F': case 'f': strcat(bin, "1111"); break;
        }
    }
}
