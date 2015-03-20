/**
*
*   Ronald Hyatt & Josh Barnett
*   Systems Software
*   Assignment 3 PMachine
*   3-20-14
*
**/

#include <stdio.h>
#include <stdlib.h>

//Given Struct
typedef struct instruction{
    int op; //Opcode
    int r;  //Register
    int l;  //Lexi Level
    int m;  //M
}instructionStruct;

//Constant Variables
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

void initVariables();
int base(int l, int base);
char* findOPCode(int op);
void fetchCycle(instructionStruct codeStructs[MAX_CODE_LENGTH], int commandCount);
void executeCycle(int op, int r, int l, int m);

//Define Globals
FILE *ifp, *opf, *mainOutput;
int printToScreen = 0;
int stack[MAX_STACK_HEIGHT];
int activationRecord[MAX_STACK_HEIGHT];
int regFile[16];
int SP;
int BP;
int PC;
int IR;
int lineCount; ///new variable!
FILE* pmachine (int v, FILE *mopf){
    int boolCheck, commandCounter = 0;
    printToScreen = v;
    mainOutput = mopf;
    instructionStruct codeStructs[MAX_CODE_LENGTH];

    initVariables();

    ifp = fopen("ParserOutput.txt", "r");
    int i;
    for (i=0;i<MAX_STACK_HEIGHT;i++)
        activationRecord[i] = 0;
    fscanf(ifp,"%d", &lineCount); ///reads in first int from file (number of lines)
    //Setup initial headings

    fprintf(mopf,"Pmachine Trace:\nLine \tOP \tR \tL \tM");
    if (printToScreen)
        printf("Line \tOP \tR \tL \tM");
    for (i=0;i<lineCount;i++){ ///changed from while !feof to a for loop thru lineCount
        fscanf(ifp, "%d", &codeStructs[commandCounter].op);
        fscanf(ifp, "%d", &codeStructs[commandCounter].r);
        fscanf(ifp, "%d", &codeStructs[commandCounter].l);
        fscanf(ifp, "%d", &codeStructs[commandCounter].m);
        /*
        printf("%d\t", commandCounter);
        printf("%s\t", findOPCode(codeStructs[commandCounter].op));
        printf("%d\t", codeStructs[commandCounter].r);
        printf("%d\t", codeStructs[commandCounter].l);
        printf("%d\n", codeStructs[commandCounter].m);*/

        commandCounter++;
    }

    fclose(ifp);
    remove("ParserOutput.txt");

    fetchCycle(codeStructs, commandCounter);
    for (i=0;i<MAX_STACK_HEIGHT;i++)
        printf("%d",stack[i]);
    return mainOutput;
}

//Function to setup variables
void initVariables(){
    int i;

    SP = 0;
    BP = 1;
    PC = 0;
    IR = 0;

    //Set every position to 0
    for (i = 0; i < MAX_STACK_HEIGHT; i ++){
        stack[i] = 0;
    }

    //Set every position in the regFile to 0
    for (i = 0; i < 16; i ++){
        regFile[i] = 0;
    }

}

//Function to execute the program
void fetchCycle(instructionStruct codeStructs[MAX_CODE_LENGTH], int commandCount){
    int i;
    if (printToScreen){
        printf("\tpc \tbp \tsp\n");
        printf("Initial Values\t\t\t\t%d\t%d\t%d\t%d %d %d %d %d %d\n", PC, BP, SP, stack[0], stack[1], stack[2], stack[3], stack[4], stack[5]);
    }
    fprintf(mainOutput,"\n\n\t\t\t\t\tpc \tbp \tsp\n");
    fprintf(mainOutput,"Initial Values\t\t\t\t%d\t%d\t%d\t%d %d %d %d %d %d\n", PC, BP, SP, stack[0], stack[1], stack[2], stack[3], stack[4], stack[5]);
    while (BP != 0){

    printf("\n\n");
    for (i=0;i<16;i++)
        printf("%d ",regFile[i]);
        if (PC >= lineCount) ///Before executing instruction, make sure it is a valid instruction! If not, stop executing (geq b/c index starts at 0, so =lineCount is out of bounds)
            return;
        //Print the command, the PC, BP, SP, and stack
        if (printToScreen)
            printf("%d\t%s\t%d\t%d\t%d\t", PC, findOPCode(codeStructs[PC].op), codeStructs[PC].r ,codeStructs[PC].l, codeStructs[PC].m);
        fprintf(mainOutput,"%d\t%s\t%d\t%d\t%d\t", PC, findOPCode(codeStructs[PC].op), codeStructs[PC].r ,codeStructs[PC].l, codeStructs[PC].m);
        if (codeStructs[PC].op == 5)
            activationRecord[SP+1] = 1; ///Mark the area right after the stack pointer as an activation record
        //Call execute
        executeCycle(codeStructs[PC].op, codeStructs[PC].r ,codeStructs[PC].l ,codeStructs[PC].m);
        if (printToScreen)
            printf("%d\t%d\t%d\t", PC, BP, SP);
        fprintf(mainOutput,"%d\t%d\t%d\t", PC, BP, SP);
        for (i = 1; i <= SP; i ++){
                if (activationRecord[i] == 1)
                    fprintf(mainOutput,"|");
            fprintf(mainOutput,"%d ", stack[i]);
            if (printToScreen){
                if (activationRecord[i] == 1)
                    printf("|");
                printf("%d ", stack[i]);
            }
        }
        fprintf(mainOutput,"\n");
        if (printToScreen)
            printf("\n");
    }
}

void executeCycle(int op, int r, int l, int m){
PC ++;
    switch (op){
        case 1:
            regFile[r] = m;
            break;
        case 2:
            SP = BP - 1;
            BP = stack[SP + 3];
            PC = stack[SP + 4];
            break;
        case 3:
            regFile[r] = stack[base(l,BP) + m];
            printf("Register %d has value %d\n",r,regFile[r]);
            break;
        case 4:
            stack[base(l,BP) + m] = regFile[r];
            break;
        case 5:
            stack[SP + 1] = 0;
            stack[SP + 2] = base(l, BP);
            stack[SP + 3] = BP;
            stack[SP + 4] = PC;
            BP = SP + 1;
            PC = m;
            SP = SP + 4;
            break;
        case 6:
            SP = SP + m;
            break;
        case 7:
            PC = m;
            break;
        case 8:
            if (regFile[r] == 0){
                PC = m;
            }
            break;
        case 9:
            //printf("Printing: The %d register file contains: %d\n", r, regFile[r]);
            break;
        case 10:
            //printf("Please enter an integer to place in register %d\n", r);
            //scanf("%d", &regFile[r]);
            break;
        case 11:
            regFile[r] = -regFile[l];
            break;
        case 12:
            regFile[r] = regFile[l] + regFile[m];
            break;
        case 13:
            regFile[r] = regFile[l] - regFile[m];
            break;
        case 14:
            regFile[r] = regFile[l] * regFile[m];
            break;
        case 15:
            regFile[r] = regFile[l] / regFile[m];
            break;
        case 16:
            regFile[r] = regFile[r] % 2;
            break;
        case 17:
            regFile[r] = regFile[l] % regFile[m];
            break;
        case 18:
            if (regFile[l] == regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
        case 19:
            if (regFile[l] != regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
        case 20:
            if (regFile[l] < regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
        case 21:
            if (regFile[l] <= regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
        case 22:
            if (regFile[l] > regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
        case 23:
            if (regFile[l] >= regFile[m]){
                regFile[r] = 1;
            }
            else {
                regFile[r] = 0;
            }
            break;
    }
    return;
}

//Function to grab the op code based on number
char* findOPCode(int op){
    switch (op){
        case 1: return "lit";
        case 2: return "rtn";
        case 3: return "lod";
        case 4: return "sto";
        case 5: return "cal";
        case 6: return "inc";
        case 7: return "jmp";
        case 8: return "jpc";
        case 9: return "sio";
        case 10: return "sio";
        case 11: return "neg";
        case 12: return "add";
        case 13: return "sub";
        case 14: return "mul";
        case 15: return "div";
        case 16: return "odd";
        case 17: return "mod";
        case 18: return "eql";
        case 19: return "neq";
        case 20: return "lss";
        case 21: return "leq";
        case 22: return "gtr";
        case 23: return "geq";
        default: return "error";
    }
}

int base(int l, int base) // l stand for L in the instruction format
{
  int b1; //find base L levels down
  b1 = base;
  while (l > 0)
  {
    b1 = stack[b1 + 1];
    l--;
  }
  return b1;
}
