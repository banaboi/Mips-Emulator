// COMP1521 Assignment 2, smips.c 
// Author: Luke Banicevic, z5209974
// This program is a mips emulator.

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <math.h>

typedef struct instruction {
    uint32_t operation;
    uint32_t s;
    uint32_t t;
    uint16_t I;
} Instruction;

/* Function Prototypes */ 
void resetBuffer(int buffer[4])
void resetBinaryInstruction(int binaryInstruction[32])
void createBinaryInstruction(int buffer[4], int binaryInstructions[32])
int get_nth_bit(int num, int n);
Instruction getInstructionComponents(int c);
void mips_add(Instruction instruction);
void mips_sub(Instruction instruction);
void mips_and(Instruction instruction);
void mips_or(Instruction instruction);
void mips_slt(Instruction instruction);
void mips_mul(Instruction instruction);
void mips_beq(Instruction instruction);
void mips_bne(Instruction instruction);
void mips_addi(Instruction instruction);
void mips_slti(Instruction instruction);
void mips_andi(Instruction instruction);
void mips_ori(Instruction instruction);
void mips_lui(Instruction instruction);
void mips_syscall();

int main(int argc, char *argv[]) {

    // create buffer array to store 4 bytes and deduce instruction
    int buffer[4] = {0};

    // create array to symbolise instruction in binary
    int binaryInstruction[32] = {0};

    // to count bytes
    int bytes = 0;

    // read file from command line arguments
    FILE *file = fopen(argv[1], "r");

    // read bytes from file presenting instructions
    int c = fgetc(file);
    
    // loop through the file until EOF
    while (c != EOF)
        // store the byte in buffer and increment bytes seen
        buffer[bytes] = c;
        bytes++;

        if (bytes == 4) {
            createBinaryInstruction(buffer, binaryInstruction);
            // split instruction into components using struct for identification
            Instruction instruction = getInstructionComponents(binaryInstruction);
            if (instruction.operation == 28) {
                mips_mul(instruction);
            } else if (instruction.operation == 4) {
                mips_beq(instruction);
            } else if (instruction.operation == 5) {
                mips_bne(instruction);
            } else if (instruction.operation == 8) {
                mips_add(instruction);
            } else if (instruction.operation == 10) {
                mips_slti(instruction);
            } else if (instrution.operation == 12) {
                mips_andi(instruction);
            } else if (instruction.operation == 13) {
                mips_ori(instruction);
            } else if (instruction.operation == 15) {
                mips_lui(instruction);
            } else if (instruction.operation == 0 && instruction.I == 12) {
                mips_syscall();
            }

            bytes = 0;
            resetBuffer(buffer);
            resetBinaryInstruction(binaryInstruction);
        }
    
        c = fgetc(file);
        
    }

    return 0;
}

// resets the buffer every four bytes
void resetBuffer( int buffer[4]) {
    for (int i = 0; i < 4; i++) {
        buffer[i] = 0;
    }
}

// resets the binary instruction array after every four bytes is read
void resetBinaryInstruction(int binaryInstruction[32]) {
    for (int i = 0; i < 31; i++) {
        binaryInstruction[i] = 0;
    }
}

// one byte at a time, extract each bit and place into array
void createBinaryInstruction(int buffer[4], int binaryInstructions[32]) {

    int k = 31;
    for (int i = 3; i >= 0; i--) {
        for (int n = 8; n >= 0; n--) {
            int bit = get_nth_bit(buffer[i], n);
            (bit == 1) ? binaryInstructions[k--] = 1 : binaryInstructions[k--] = 0;
        }
    }

}

// get the nth bit from a number
int get_nth_bit(int num, int n) {
    return (num >> n) & 1;
}

// create a struct to store all the components of an instruction
Instruction getInstructionComponents(int binaryInstructions[32]) {
    Instruction instruction;

    instruction.I = 0;
    int multiplier = 1;
    for (int k = 31; k >= 16; k--) {
        instruction.I += binaryInstructions[k] * multiplier;
        multiplier *= 2;
    }

    instruction.t = 0;
    multiplier = 1;
    for (int k = 15; k >= 11; k--) {
        instruction.t += binaryInstructions[k] * multiplier;
        multiplier *= 2;
    }

    instruction.s = 0;
    multiplier = 1;
    for (int k = 10; k >= 6; k--) {
        instruction.s += binaryInstructions[k] * multiplier;
        multiplier *= 2;
    }

    instruction.operation = 0;
    multiplier = 1;
    for (int k = 5; k >= 0; k--) {
        instruction.operation += binaryInstructions[k] * multiplier;
        multiplier *= 2;
    }

    return instruction;
}



void mips_add(Instruction instruction) {


}
void mips_sub(Instruction instruction) {


}

void mips_and(Instruction instruction) {


}
void mips_or(Instruction instruction) {


}
void mips_slt(Instruction instruction) {


}
void mips_mul(Instruction instruction) {


}
void mips_beq(Instruction instruction) {
    printf("beq $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_bne(Instruction instruction) {
    printf("bne $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_addi(Instruction instruction) {
    printf("addi $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_slti(Instruction instruction) {
    printf("slti $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_andi(Instruction instruction) {
    printf("andi $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_ori(Instruction instruction) {
    printf("ori $%d, $%d, %u\n", instruction.s, instruction.t, instruction.I);

}
void mips_lui(Instruction instruction) {
    // error if s part of bit pattern does not equal zero;
    if (instruction.s != 0) return;

}
void mips_syscall() {
    printf("syscall\n");
}
