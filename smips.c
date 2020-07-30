// COMP1521 Assignment 2, smips.c 
// Author: Luke Banicevic, z5209974
// This program is a mips emulator.

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>


/* Instruction Struct */
typedef struct instruction {
    uint32_t operationMSB;
    uint32_t s;
    uint32_t t;
    uint32_t d;
    int16_t I;
    uint32_t operationLSB;
} Instruction;


/* Function Definitions */
Instruction getInstructionComponents(int c);
void printInstructions(int c, int line, char *filename);
void fillRegisters(int c,char *filename);
void printRegisters(int *registers);
void print_mips_add(Instruction instruction);
void print_mips_sub(Instruction instruction);
void print_mips_and(Instruction instruction);
void print_mips_or(Instruction instruction);
void print_mips_slt(Instruction instruction);
void print_mips_mul(Instruction instruction);
void print_mips_beq(Instruction instruction);
void print_mips_bne(Instruction instruction); 
void print_mips_addi(Instruction instruction);
void print_mips_slti(Instruction instruction);
void print_mips_andi(Instruction instruction);
void print_mips_ori(Instruction instruction);
void print_mips_lui(Instruction instruction);
void print_mips_syscall();

void mips_add(Instruction instruction, int *registers);
void mips_sub(Instruction instruction,int *registers);
void mips_and(Instruction instruction, int *registers);
void mips_or(Instruction instruction, int *registers);
void mips_slt(Instruction instruction, int *registers);
void mips_mul(Instruction instruction, int *registers);
void mips_beq(Instruction instruction, int *registers);
void mips_bne(Instruction instruction, int *registers); 
void mips_addi(Instruction instruction, int *registers);
void mips_slti(Instruction instruction, int *registers);
void mips_andi(Instruction instruction, int *registers);
void mips_ori(Instruction instruction, int *registers);
void mips_lui(Instruction instruction, int *registers);
//int syscall();

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
    for (int i = 0; i < 32; i++) {
        if (registers[i] != 0) {
            printf("$%d  = %d\n", i, registers[i]);
        }
    }
}


void fillRegisters(int c, char *filename) {
    
    // open file for reading
    FILE *file = fopen(filename, "rb");
    // create register array
    int registers[32] = {0};
    // read the file 32 bits at a time in hexadecimal format
    while (fscanf(file, "%x", &c) == 1) {
        // split the instruction into components
        Instruction instruction = getInstructionComponents(c);
        
        // analyse each component to identify opcode
        if (instruction.operationMSB == 28) {
            mips_mul(instruction, registers);
        } else if (instruction.operationMSB == 4) {
            mips_beq(instruction, registers);
        } else if (instruction.operationMSB == 5) {
            mips_bne(instruction, registers);
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
            //mips_syscall();
        } else if (instruction.operationLSB == 2 && instruction.operationMSB == 28) {
            mips_mul(instruction, registers);
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
        } else {

            // invalid instruction code
        }
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
            //mips_mul(instruction, registers);
            print_mips_mul(instruction);
        } else if (instruction.operationMSB == 4) {
            //mips_beq(instruction, registers);
            print_mips_beq(instruction);
        } else if (instruction.operationMSB == 5) {
            //mips_bne(instruction, registers);
            print_mips_bne(instruction);
        } else if (instruction.operationMSB == 8) {
            //mips_addi(instruction, registers);
            print_mips_addi(instruction);
        } else if (instruction.operationMSB == 10) {
            //mips_slti(instruction, registers);
            print_mips_slti(instruction);
        } else if (instruction.operationMSB == 12) {
            //mips_andi(instruction, registers);
            print_mips_andi(instruction);
        } else if (instruction.operationMSB == 13) {
            //mips_ori(instruction, registers);
            print_mips_ori(instruction);
        } else if (instruction.operationMSB == 15) {
            //mips_lui(instruction, registers);
            print_mips_lui(instruction);
        } else if (instruction.operationMSB == 0 && instruction.I == 12) {
            print_mips_syscall();
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 42) {
            //mips_slt(instruction, registers);
            print_mips_slt(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 37) {
            //mips_or(instruction, registers);
            print_mips_or(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 36) {
            //mips_and(instruction, registers);
            print_mips_and(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 34) {
            //mips_sub(instruction, registers);
            print_mips_sub(instruction);
        } else if (instruction.operationMSB == 0 && instruction.operationLSB == 32) {
            //mips_add(instruction, registers);
            print_mips_add(instruction);
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


///////////////////////////////////////////////////////////////////////////////

void print_mips_add(Instruction instruction) {
    printf(" add  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_sub(Instruction instruction) {
    printf(" sub  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_and(Instruction instruction) {
    printf(" and  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_or(Instruction instruction) {
    printf(" or  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_slt(Instruction instruction) {
    printf(" slt  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_mul(Instruction instruction) {
    printf(" mul  $%d, $%d, $%d\n", instruction.d, instruction.s, instruction.t);
}
void print_mips_beq(Instruction instruction) {
    printf(" beq  $%d, $%d, %d\n", instruction.s, instruction.t, instruction.I);
    
}
void print_mips_bne(Instruction instruction) {
    printf(" bne  $%d, $%d, %d\n", instruction.s, instruction.t, instruction.I);
    
}
void print_mips_addi(Instruction instruction) {
    printf(" addi $%d, $%d, %d\n", instruction.t, instruction.s, instruction.I);

}
void print_mips_slti(Instruction instruction) {
    printf(" slti  $%d, $%d, %d\n", instruction.t, instruction.s, instruction.I);
    
}
void print_mips_andi(Instruction instruction) {
    printf(" andi  $%d, $%d, %d\n", instruction.t, instruction.s, instruction.I);

}
void print_mips_ori(Instruction instruction) {
    printf(" ori  $%d, $%d, %d\n", instruction.t, instruction.s, instruction.I);
}
void print_mips_lui(Instruction instruction) {
    printf(" lui  $%d, %d\n", instruction.t, instruction.I);
}
void print_mips_syscall() {
    printf(" syscall\n");
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
    registers[instruction.d] = registers[instruction.s] + registers[instruction.t];
}
void mips_beq(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] * registers[instruction.t];
    
}
void mips_bne(Instruction instruction, int *registers) {
    registers[instruction.d] = registers[instruction.s] + registers[instruction.t];
    
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
    registers[instruction.t] = instruction.I << registers[instruction.t];
}

void mips_ori(Instruction instruction, int *registers) {
    registers[instruction.t] = registers[instruction.s] | instruction.I;
}
