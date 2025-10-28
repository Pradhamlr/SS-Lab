#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *inter, *optab, *symtab, *object, *len;
    char label[30], opcode[15], operand[15];
    char opt_opcode[15], opt_value[15];
    char sym_label[30];
    int sym_addr, locctr, start_addr = 0, program_length = 0, length;

    // Open files
    inter = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symbol.txt", "r");
    object = fopen("objectcode.txt", "w");
    len = fopen("length.txt", "r");

    if (!inter || !optab || !symtab || !object) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(len, "%X", &length);

    // Read first line
    fscanf(inter, "%x %s %s %s", &locctr, label, opcode, operand);

    // START directive → Header record
    if (strcmp(opcode, "START") == 0) {
        start_addr = (int)strtol(operand, NULL, 16);
        fprintf(object, "H^%-6s^%06X^%06X", label, start_addr, length);
        fscanf(inter, "%x %s %s %s", &locctr, label, opcode, operand);
    }

    fprintf(object, "\nT^%06X^", locctr); // Start Text record

    // Process all lines until END
    while (strcmp(opcode, "END") != 0) {
        int found = 0;

        // Search opcode in OPTAB
        rewind(optab);
        while (fscanf(optab, "%s %s", opt_opcode, opt_value) == 2) {
            if (strcmp(opcode, opt_opcode) == 0) {
                // Get operand address from SYMTAB
                rewind(symtab);
                int sym_found = 0;
                while (fscanf(symtab, "%s %x", sym_label, &sym_addr) == 2) {
                    if (strcmp(sym_label, operand) == 0) {
                        fprintf(object, "%s%04X^", opt_value, sym_addr);
                        sym_found = 1;
                        break;
                    }
                }
                if (!sym_found) {
                    fprintf(object, "%s0000^", opt_value); // undefined symbol
                }
                found = 1;
                break;
            }
        }

        // Handle assembler directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                fprintf(object, "%06X^", atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') { // C'EOF'
                    for (int i = 2; i < strlen(operand) - 1; i++)
                        fprintf(object, "%02X", operand[i]);
                    fprintf(object, "^");
                } else if (operand[0] == 'X') { // X'F1'
                    fprintf(object, "%02X^", (int)strtol(&operand[2], NULL, 16));
                }
            }
            // RESW/RESB → skip object code (no output)
        }

        // Read next line
        fscanf(inter, "%x %s %s %s", &locctr, label, opcode, operand);
    }

    // END record
    fprintf(object, "\nE^%06X\n", start_addr);

    printf(" PASS 2 completed! Object code written to objectcode.txt\n");

    fclose(inter);
    fclose(optab);
    fclose(symtab);
    fclose(object);

    return 0;
}