#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char opcode[10], operand[10], label[10], mnemonic[10], code[10];
    FILE *input, *optab, *symbol, *output;
    int locctr, start, length;
    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    output = fopen("output.txt", "w");
    symbol = fopen("symbol.txt", "w");
    
    fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    if(strcmp(opcode, "START") == 0){
        start = atoi(operand);
        locctr = start;
        fprintf(output, "\t%s\t%s\t%X\n", label, opcode, locctr + 3096);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    else locctr = 0;
    while(strcmp(opcode, "END") != 0){
        fprintf(output, "%X\t", locctr + 3096);
        if(strcmp(label, "-") != 0) fprintf(symbol, "%s\t%X\n", label, locctr + 3096);
        fseek(optab, SEEK_SET, 0);
        fscanf(optab, "%s\t%s", code, mnemonic);
        while(strcmp(code, "END") != 0){
            if(strcmp(opcode, code) == 0){
                locctr += 3;
                break;
            }
            fscanf(optab, "%s\t%s", code, mnemonic);
        }
        if(strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if(strcmp(opcode, "RESW") == 0)
            locctr += 3*(atoi(operand));
        else if(strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);
        else if(strcmp(opcode, "BYTE") == 0){
            char ch = operand[0];
            if(strcmp(&ch, "X") == 0)
                locctr += 1;
            else
                locctr += strlen(operand) - 3;
        }
        fprintf(output, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(output, "\t%s\t%s\t%s\n", label, opcode, operand);
    length = locctr - start;
    printf("Code length = %x\n", length);
    fclose(input);
    fclose(output);
    fclose(optab);
    fclose(symbol);
}



