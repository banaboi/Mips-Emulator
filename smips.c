// COMP1521 Assignment 2, smips.c 
// Author: Luke Banicevic, z5209974
// This program is a mips emulator.

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <math.h>


/* Instruction Struct */
typedef struct instruction {
    int operationMSB;
    int s;
    int t;
    int d;
    uint16_t I;
    int operationLSB;
} Instruction;


/* Function Definitions */
void mips_add(int d, int s, int t);
void mips_sub(int d, int s, int t);
void mips_and(int d, int s, int t);
void mips_or(int d, int s, int t);
void mips_slt(int d, int s, int t);
void mips_mul(int d, int s, int t);
void mips_beq(int s, int t, uint16_t I);
void mips_bne(int s, int t, uint16_t I); 
void mips_addi(int t, int s, uint16_t I);
void mips_slti(int t, int s, uint16_t I);
void mips_andi(int t, int s, uint16_t I);
void mips_ori(int t, int s, uint16_t I);
void mips_lui(int t, uint16_t I);
void mips_syscall();

int main(int argc, char *argv[]) {


    // open and read file from command line arguments
    FILE *file = fopen(argv[1], "rb");
    // to count lines of instruction
    int line = 0;

    int c; 
    // loop through the file until EOF
    while (fscanf(file, "%x", &c) == 1) {
        Instruction instruction = getInstructionComponents(c);
        if (instruction.operationMSB == 28) {
            mips_mul(instruction);
        } else if (instruction.operationMSB == 4) {
            mips_beq(instruction);
        } else if (instruction.operationMSB == 5) {
            mips_bne(instruction);
        } else if (instruction.operationMSB == 8) {
            mips_add(instruction);
        } else if (instruction.operationMSB == 10) {
            mips_slti(instruction);
        } else if (instrution.operationMSB == 12) {
            mips_andi(instruction);
        } else if (instruction.operationMSB == 13) {
            mips_ori(instruction);
        } else if (instruction.operationMSB == 15) {
            mips_lui(instruction);
        } else if (instruction.operationMSB == 0 && instruction.I == 12) {
            mips_syscall();
        } else if (instruction.operationLSB == 2 && instruction.operationMSB == 28) {
            mips_mul(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 42) {
            mips_slt(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 37) {
            mips_or(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 40) {
            mips_and(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operaationLSB == 34) {
            mips_sub(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 32) {
            mips_add(instruction);
        } else {
            // invalid instruction code
            printf("%s:%d: invalid instruction code: %d\n",argv[1],line, c);

        }
    }

    fclose(file);

    return 0;
}

// create a struct to store all the components of an instruction
Instruction getInstructionComponents(int c) {
    Instruction instruction;

    // code

    return instruction;
}


void mips_add(int d, int s, int t) {

}
void mips_sub(int d, int s, int t) {
    
}
void mips_and(int d, int s, int t) {
    
}
void mips_or(int d, int s, int t) {
    
}
void mips_slt(int d, int s, int t) {
    
}
void mips_mul(int d, int s, int t) {
    
}
void mips_beq(int s, int t, uint16_t I) {
    printf("beq $%d, $%d, %u\n", s, t, I);
    
}
void mips_bne(int s, int t, uint16_t I) {
    printf("bne $%d, $%d, %u\n", s, t, I);
    
}
void mips_addi(int t, int s, uint16_t I) {
    printf("addi $%d, $%d, %u\n", s, t, I);

}
void mips_slti(int t, int s, uint16_t I) {
    printf("slti $%d, $%d, %u\n", s, t, I);
    
}
void mips_andi(int t, int s, uint16_t I) {
    printf("andi $%d, $%d, %u\n", s, t, I);

}
void mips_ori(int t, int s, uint16_t I) {
    printf("ori $%d, $%d, %u\n", s, t, I);
}
void mips_lui(int t, uint16_t I) {
    
}
void mips_syscall() {
    printf("syscall\n");
}

