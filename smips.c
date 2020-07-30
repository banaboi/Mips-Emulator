// COMP1521 Assignment 2, smips.c 
// Author: Luke Banicevic, z5209974
// This program is a mips emulator.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>



#include "smips.h"

int main(int argc, char *argv[]) {

    // print file instructions
    printInstructions(0, 0, argv[1]);

    // fill registers
    fillRegisters(0, argv[1]);


    // exit program
    return 0;
}


// print non zero registers after execution
void printRegisters(int *registers) {

    printf("Registers After Execution\n");
    for (int i = 1; i < 33; i++) {
        if (registers[i] != 0) {
            if (i < 10) {
                printf("$%d  = %d\n", i, registers[i]);
            } else {
                printf("$%d = %d\n", i, registers[i]);
            }
            
        }
    }
}


void fillRegisters(int c, char *filename) {

    // define state of program
    int state = CONTINUE_PROGRAM;
    
    // open file for reading
    FILE *file = fopen(filename, "rb");

    // create register array
    int registers[33] = {0};

    // to store instructions
    int instructions[1000] = {0};

    printf("Output\n");
    // read the file 32 bits at a time in hexadecimal format
    // and store instructions into array
    int k = 0;
    int length = 0;
    while (fscanf(file, "%x", &c) == 1) {
        instructions[k++] = c;
        length++;
    }

    // loop through array of instructions to print output
    int i = 0;
    while (i < length && state == CONTINUE_PROGRAM){

        // split the instruction into components
        Instruction instruction = getInstructionComponents(instructions[i]);
        
        // analyse each component to identify opcode
        if (instruction.operationMSB == 28) {
            mips_mul(instruction, registers);
        } else if (instruction.operationMSB == 4) {
            if (registers[instruction.s] == registers[instruction.t]) i += instruction.I - 1;
        } else if (instruction.operationMSB == 5) {
            if (registers[instruction.s] != registers[instruction.t]) i += instruction.I - 1;
        } else if (instruction.operationMSB == 8) {
            mips_addi(instruction, registers);
        } else if (instruction.operationMSB == 10) {
            mips_slti(instruction, registers);
        } else if (instruction.operationMSB == 12) {
            mips_andi(instruction, registers);
        } else if (instruction.operationMSB == 13) {
            mips_ori(instruction, registers);
        } else if (instruction.operationMSB == 15) {
            mips_lui(instruction, registers);
        } else if (instruction.operationMSB == 0 && instruction.I == 12) {
            state = mips_syscall(registers);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 42) {
            mips_slt(instruction, registers);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 37) {
            mips_or(instruction, registers);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 36) {
            mips_and(instruction, registers);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 34) {
            mips_sub(instruction, registers);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 32) {
            mips_add(instruction, registers);
        }
        // changes to register $0 are ignored, remains equal to 0
        if (registers[0] != 0) registers[0] = 0;
        i++;
    }

    // file is read, close
    fclose(file);

    // print registers after execution
    printRegisters(registers);

}

// print the instructions from a given file
void printInstructions(int c, int line, char *filename) {
    
    // open file for reading
    FILE *file = fopen(filename, "rb");

    printf("Program\n");
    // read the file 32 bits at a time in hexadecimal format
    while (fscanf(file, "%x", &c) == 1) {

        // split the instruction into components
        Instruction instruction = getInstructionComponents(c);
        if (line < 10) {
            printf("  %d:", line);
        } else {
            printf(" %d:", line);
        }
        
        // analyse each component to identify opcode
        if (instruction.operationMSB == 28) {
            printMipsCode("mul", instruction.d, instruction.s, instruction.t);
        } else if (instruction.operationMSB == 4) {
            printMipsCode("beq", instruction.s, instruction.t, instruction.I);
        } else if (instruction.operationMSB == 5) {
            printMipsCode("bne", instruction.s, instruction.t, instruction.I);
        } else if (instruction.operationMSB == 8) {
            printMipsCode("addi", instruction.t, instruction.s, instruction.I);
        } else if (instruction.operationMSB == 10) {
            printMipsCode("slti", instruction.t, instruction.s, instruction.I);
        } else if (instruction.operationMSB == 12) {
            printMipsCode("andi", instruction.t, instruction.s, instruction.I);
        } else if (instruction.operationMSB == 13) {
            printMipsCode("ori", instruction.t, instruction.s, instruction.I);
        } else if (instruction.operationMSB == 15) {
            printMipsCode("lui", instruction.t, instruction.I, 0);
        } else if (instruction.operationMSB == 0 && instruction.I == 12) {
            printMipsCode("syscall",0,0,0);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 42) {
            printMipsCode("slt", instruction.d, instruction.s, instruction.t);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 37) {
            printMipsCode("or", instruction.d, instruction.s, instruction.t);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 36) {
            printMipsCode("and", instruction.d, instruction.s, instruction.t);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 34) {
            printMipsCode("sub", instruction.d, instruction.s, instruction.t);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 32) {
            printMipsCode("add", instruction.d, instruction.s, instruction.t);
        } else {

            // invalid instruction code
            printf(" %s:%d: invalid instruction code: %d\n",filename,line, c);

        }

        line++;
    }

    // file is read, close
    fclose(file);
    
}

// create a struct to store all the components of an instruction
Instruction getInstructionComponents(int c) {
    Instruction instruction;

    instruction.operationMSB = (c >> 26) & 0b111111;
    instruction.s = (c >> 21) & 0b11111;
    instruction.t = (c >> 16) & 0b11111;
    instruction.d = (c >> 11) & 0b11111;
    instruction.I = c & 0xFFFF;
    instruction.operationLSB = c & 0b11111111111;

    return instruction;
}


void printMipsCode(char *command, int num1, int num2, int num3) {
    if (strcmp("syscall",command) == 0) {
        printf(" syscall\n");
    } else if (strcmp("lui",command) == 0) {
        printf(" %s  $%d, %d\n", command, num1, num2);
    } else if ( strcmp("add", command) == 0 || strcmp("sub", command) == 0 || 
                strcmp("and", command) == 0 || strcmp("or", command) == 0 || 
                strcmp("slt", command) == 0 || strcmp("mul", command) == 0) {
        printf(" %s  $%d, $%d, $%d\n", command, num1, num2, num3);
    } else if (strcmp("addi", command) == 0) {
        printf(" %s $%d, $%d, %d\n", command, num1, num2, num3);
    } else {
        printf(" %s  $%d, $%d, %d\n", command, num1, num2, num3);
    }
    
}

////////////////////////////////////////////////////////////////////////////////

void mips_add(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] + registers[instruction.t];
}
void mips_sub(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] - registers[instruction.t];
}
void mips_and(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] & registers[instruction.t];
}
void mips_or(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] | registers[instruction.t];
}
void mips_slt(Instruction instruction, int *registers) {
    registers[instruction.d] = (registers[instruction.s] < registers[instruction.t]) ? 1 : 0;
}
void mips_mul(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] * registers[instruction.t];
}
void mips_addi(Instruction instruction, int *registers) {
    registers[instruction.t] = registers[instruction.s] + instruction.I;
}
void mips_slti(Instruction instruction, int *registers) {
    registers[instruction.t] = (registers[instruction.s] < instruction.I) ? 1 : 0;
}
void mips_andi(Instruction instruction, int *registers) {
    registers[instruction.t] = registers[instruction.s] & instruction.I;
}

void mips_lui(Instruction instruction, int *registers) {
    registers[instruction.t] = instruction.I << 16;
}

void mips_ori(Instruction instruction, int *registers) {
    registers[instruction.t] = registers[instruction.s] | instruction.I;
}

int mips_syscall(int *registers) {

    if (registers[2] == 11) {
        printf("%c", (char)registers[4]);
    } else if (registers[2] == 10) {
        return END_PROGRAM;
    } else if (registers[2] == 1) {
        printf("%d", registers[4]);
    } else {
        printf("Unknown system call: %d\n", registers[2]);
        return END_PROGRAM;
    }

    return CONTINUE_PROGRAM;

}

