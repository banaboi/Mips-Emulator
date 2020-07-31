
/* Struct Definition */
typedef struct instruction {
    uint32_t operationMSB;
    uint32_t s;
    uint32_t t;
    uint32_t d;
    int16_t I;
    uint32_t operationLSB;
} Instruction;


#define END_PROGRAM -1
#define CONTINUE_PROGRAM -2

/* Function Definitions */
Instruction getInstructionComponents(int c);
void printInstructions(int c, int line, char *filename);
void executeProgram(int c,char *filename);
void printRegisters(int *registers);
void printMipsCode(char *command, int num1, int num2, int num3);
void fillInstructions(int c, int *length, int *instructions, char *filename);

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
int mips_syscall(int *registers);
