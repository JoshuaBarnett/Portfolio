/**
*
*   Ronald Hyatt & Josh Barnett
*   Systems Software
*   Assignment 3 Parser
*   3-20-14
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOL_TABLE_SIZE 500
#define NOERRORS 0
#define ERRORS 1
/*
TODO:
Symbol Table
Code Generation
Output Code
Printing Lexemes Correctly in Command Prompt
Write codeout to file and screen in main function
*/

int validProg = NOERRORS;
///Changed
typedef struct machineInstruct{
    int opcode;
    int r;
    int l;
    int m;
}mI;

///Added
enum OP{LIT = 1, RTN, LOD, STO, CAL, INC, JMP, JPC, SIOP, SIOR, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS ,LEQ, GTR, GEQ};


typedef struct symbol
    {
	int kind; 		// const = 1, var = 2, proc = 3
	char name[10];	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
}smb;

struct symbol symbolTable[MAX_SYMBOL_TABLE_SIZE];
int numSymbols = 0;
int addrCounter[3];

int tempNum = 0, pastProc = 0;

typedef struct registerList{
    int val;            //value stored in the register
    char ident[11];     //name of variable using register (or the last value to use it)
}rL;



void getToken();
void PROGRAM();
void BLOCK();
void CONDITION();
void EXPRESSION();
void STATEMENT();
void TERM();
void FACTOR();
void ERROR(int errornum);
void newSymbol(int kind,char* name,int val, int level, int addr);
void emit(int op, int r, int l, int m);
void addSymbol(char* name, int kind, int val, int level, int addr);
int searchSymbolTable(char name[10]);
int RELATION(token_type x);


struct machineInstruct codeOut[MAX_CODE_LENGTH]; //where the outputted p-machine code will be generated/stored
struct registerList regList[16]; //registers


FILE *ofp, *mopf;
struct LexemeList *token = NULL;
int printOutParser = 0;
int cx;
int temp[100];
int tempCount;
///All around zero for assignment 3
int l = 0;

///Added
int rp = 0;

FILE* parser(int printToScreen, FILE *mainOutput, struct LexemeList *lexiIn){

addrCounter[0] = 4;

addrCounter[1] = 4;

addrCounter[2] = 4;
      mopf = mainOutput;
      printOutParser = printToScreen;
      int numTokens, numIdent;
      token = lexiIn;
      int i;
      for (i = 0;i<16;i++){
        regList[i].val = 0;
      }
      PROGRAM();

      if (printOutParser)
            printf("\nCode generated from parser:\n");
      ofp = fopen("ParserOutput.txt","w");
      fprintf(ofp,"%d\n",cx); ///adds a first line to ParserOutput.txt (renamed from 'ParserOutput') that lists the number of lines

      fprintf(mopf,"\nCode generated from parser:\n");
      for (i=0;i<cx;i++)
      {
            fprintf(ofp,"%d %d %d %d\n",codeOut[i].opcode,codeOut[i].r,codeOut[i].l,codeOut[i].m);
            fprintf(mopf,"%d %d %d %d\n",codeOut[i].opcode,codeOut[i].r,codeOut[i].l,codeOut[i].m);
            if (printOutParser)
                printf("%d %d %d %d\n",codeOut[i].opcode,codeOut[i].r,codeOut[i].l,codeOut[i].m);
      }
      fprintf(mopf,"\n");
      fclose(ofp);
      return ofp;
}

void PROGRAM(){
    emit(INC,0,0,4); ///add initial AR
    BLOCK();
    if (token->tokenval != periodsym){
        ERROR(9);
    }
printf("Block has returned for program!!!\n");

}

void BLOCK(){
    char tempname[10];
    if (l > 3)
        ERROR(27);
    if (token->tokenval == constsym){
        do{
            getToken();
            if (token->tokenval != identsym){
                ERROR(4);
              }
              strcpy(tempname,token->ident);
              getToken();

              if (token->tokenval == becomessym){
                ERROR(1);
              }
              if (token->tokenval != eqsym){
                ERROR(3);
              }
              getToken();
              if (token->tokenval != numbersym){
                ERROR(2);
              }
              addSymbol(tempname,1,atoi(token->ident),l,-1);
              getToken();
        } while(token->tokenval == commasym);
        if (token->tokenval != semicolonsym){
            ERROR(5);
        }
        getToken();
    }
    if (token->tokenval == intsym){
        do{
            getToken();
            if (token->tokenval != identsym){
                ERROR(4);
            }
            strcpy(tempname,token->ident);
            addSymbol(tempname,2,0,l,addrCounter[l]);
            addrCounter[l]++;
            emit(INC,0,l,1); //add stack room
            printf("Adding var:%s\n",tempname);
            getToken();
        }while (token->tokenval == commasym);
        if (token->tokenval != semicolonsym){
            ERROR(5);
        }
        getToken();
    }
    while (token->tokenval == procsym){
        getToken();
        if (token->tokenval != identsym){
            ERROR(4);
        }

        strcpy(tempname, token->ident);
        addSymbol(tempname, 3, -107, l, cx);
        l++;
        pastProc = cx;
        emit(JMP, 0,0,0);
printf("Emited dummy jump for procedure: %s\n", tempname);

        getToken();
        if (token->tokenval != semicolonsym){
            ERROR(6);
        }
        getToken();
        BLOCK();

        codeOut[pastProc].m = cx+1;
        emit(RTN,0,0,0);
        l--;
printf("Returned from procedure: %s\n", tempname);

        if (token->tokenval != semicolonsym){
            ERROR(5);
        }
        getToken();
    }
    STATEMENT();
}

void STATEMENT(){
    if (token->tokenval == identsym){
        //Grab symbol from table
        temp[tempCount] = searchSymbolTable(token->ident);
        if (temp[tempCount] == -1){
            ERROR(11);
        }
        if ((symbolTable[temp[tempCount]].kind == 1) || (symbolTable[temp[tempCount]].kind == 3))//const or proc
            ERROR(12);
        int here = rp;
        getToken();
        if (token->tokenval != becomessym){
            ERROR(13);
        }
        getToken();
        tempCount++;
        EXPRESSION();
        tempCount--;
        //Generate a store command at the register that we loaded the symbol into
        emit(STO, here, l-symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].addr); ///cannot add +1/-1 to addr
        //Reset the rp
        rp = here;
    }
    else if (token->tokenval == callsym){
        getToken();
        if (token->tokenval != identsym){
            ERROR(35);
        }
        tempNum = cx;
//        emit(INC, 0, 0, 4);
        emit(CAL, 0, l-symbolTable[searchSymbolTable(token->ident)].level, symbolTable[searchSymbolTable(token->ident)].addr+1); ///has to be +1
printf("After the emit in the call\n");

        getToken();
        ///while (token->tokenval == identsym)
        ///{
        ///emit(inc,0,0,1);
        ///
    }
    else if (token->tokenval == beginsym){
        getToken();
        STATEMENT();
        while (token->tokenval == semicolonsym){
            getToken();
            STATEMENT();
        }
        if (token->tokenval != endsym){
            ERROR(10);
        }
      getToken();
    }
    else if (token->tokenval == ifsym){
        getToken();
        CONDITION();
        if (token->tokenval != thensym){
            ERROR(16);
        }
        getToken();
        int tmp = cx;
        emit (JPC, 0,0,0);
        STATEMENT();

        if (token->tokenval == elsesym){
            int toJmp = cx;
            emit(JMP,0,0,0);
            codeOut[tmp].m = cx;
            getToken();
            STATEMENT();
            codeOut[toJmp].m = cx;
        }
        else{
            codeOut[tmp].m = cx;
        }

    }
    else if (token->tokenval == whilesym){
        int cx1 = cx;
        int cx2;
        getToken();
        CONDITION();
        cx2 = cx;
        emit(JPC, 0, 0, 0);
        if (token->tokenval != dosym){
            ERROR(18);
        }
        getToken();
        STATEMENT();
        emit(JMP, 0, 0, cx1);
        codeOut[cx2].m = cx;
    }
    //Not sure what these are supposed to do...
    else if (token->tokenval == readsym){
        //Load into temp token
        temp[tempCount] = searchSymbolTable(token->ident);
        emit(LOD, rp, l-symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].addr);
        //Write to screen
        emit(SIOR, rp, 0, 1);
        //Reset RP
        rp--;
    }
    else if (token->tokenval == writesym){
        //Load into temp token
        temp[tempCount] = searchSymbolTable(token->ident);
        emit(LOD, rp, l-symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].addr);
        //Write to screen
        emit(SIOP, rp, 0, 2);
        //Reset RP
        rp--;

    }
}

void CONDITION(){
    if (token->tokenval == oddsym){
        //Create a temp symbol
        temp[tempCount] = searchSymbolTable(token->ident);
        //load it into a register
        if (symbolTable[temp[tempCount]].kind == 1) //const
            emit(LIT, rp, symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].val);
        else //int
            emit(LOD, rp, l-symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].addr);
        //emit odd command
        emit(ODD, rp, 0, 0);
        //Don't increment rp as we don't need to store the previous value

        getToken();
        tempCount++;
        EXPRESSION();
        tempCount--;
    }
    else{
        EXPRESSION();
        int relCode = RELATION(token->tokenval);
        if (relCode < 18 || relCode > 23){
            ERROR(20);
        }
        getToken();
        EXPRESSION();
        emit(relCode, rp - 2, rp - 2, rp - 1);
        rp--;
    }
}

void EXPRESSION(){
    int addop;
    if (token->tokenval == plussym || token->tokenval == minussym){
        addop = token->tokenval;
        int here = rp;
        getToken();
        TERM();
        if (addop == minussym){
            emit(NEG, here, l, atoi(token->ident));
        }
        rp = here;
    }
    TERM();
    while (token->tokenval == plussym || token->tokenval == minussym){
      addop = token->tokenval;
      getToken();
      TERM();

      if (addop == plussym){
        emit(ADD, rp-2, rp-2, rp-1);
        rp--;
      }
      else {
        emit(SUB, rp-2, rp-2, rp-1);
        rp--;
      }
    }
}

void TERM(){
    int mulop;
    FACTOR();
    while (token->tokenval == multsym || token->tokenval == slashsym){
      mulop = token->tokenval;
      getToken();
      FACTOR();
      if (mulop == multsym){
        emit(MUL, rp-2, rp-2, rp-1);
      }
      else {
        emit(DIV, rp-2, rp-2, rp-1);
      }
      rp--;
    }
}

void FACTOR() {
    if (token->tokenval == identsym){
        temp[tempCount] = searchSymbolTable(token->ident);
        if (temp[tempCount] == -1){
            ERROR(11);
        }
        if (symbolTable[temp[tempCount]].kind == 1) //const
            emit(LIT, rp, symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].val);
        else //int
            emit(LOD, rp, l-symbolTable[temp[tempCount]].level, symbolTable[temp[tempCount]].addr); ///trying +1
        rp++;
        getToken();
    }
    else if (token->tokenval == numbersym){
        emit(LIT, rp, l, atoi(token->ident));
        rp++;
        getToken();

    }
    else if (token->tokenval == lparentsym){
        getToken();

        EXPRESSION();
        if (token->tokenval != rparentsym){
            ERROR(22);
        }
        getToken();
    }
    else ERROR(24);
}


void ERROR(int errornum){
    int x = errornum;
    validProg = ERRORS;
    switch (x){
    case 1:{
        printf("Error %d on line %d: Use = instead of :=.\n",x,cx);
        exit(EXIT_FAILURE);
        break;}
    case 2:
        printf("Error %d on line %d: = must be followed by a number.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 3:
        printf("Error %d on line %d: Identifier must be followed by =.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 4:
        printf("Error %d on line %d: const, int, procedure must be followed by identifier.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 5:
        printf("Error %d on line %d: Semicolon or comma missing.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 6:
        printf("Error %d on line %d: Incorrect symbol after procedure declaration.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 7:
        printf("Error %d on line %d: Statement expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 8:
        printf("Error %d on line %d: Incorrect symbol after statement part in block.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 9:
        printf("Error %d on line %d: Period expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 10:
        printf("Error %d on line %d: Semicolon between statements missing.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 11:
        printf("Error %d on line %d: Undeclared identifier.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 12:
        printf("Error %d on line %d: Assignment to constant or procedure is not allowed.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 13:
        printf("Error %d on line %d: Assignment operator expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 14:
        printf("Error %d on line %d: call must be followed by an identifier.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 15:
        printf("Error %d on line %d: Call of a constant or variable is meaningless.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 16:
        printf("Error %d on line %d: then	 expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 17:
        printf("Error %d on line %d: Semicolon or } expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 18:
        printf("Error %d on line %d: do expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 19:
        printf("Error %d on line %d: Incorrect symbol following statement.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 20:
        printf("Error %d on line %d: Relational operator expected.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 21:
        printf("Error %d on line %d: Expression must not contain a procedure identifier.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 22:
        printf("Error %d on line %d: Right parenthesis missing.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 23:
        printf("Error %d on line %d: The preceding factor cannot begin with this symbol.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 24:
        printf("Error %d on line %d: An expression cannot begin with this symbol.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 25:
        printf("Error %d on line %d: This number is too large.\n",x,cx);
        exit(EXIT_FAILURE);
        break;
    case 26:
        printf("Error %d on line %d: Code too long\n", x, cx);
        exit(EXIT_FAILURE);
        break;
    case 27:
        printf("Error %d on line %d: Lexigraphical level cannot exceed 3\n", x, cx);
        exit(EXIT_FAILURE);
        break;

    case 35:
        printf("Error Not Set yet... Please set soon\n");
        exit(EXIT_FAILURE);
        break;
    }

}

//Function to create the code for the parser
void emit(int op, int r, int l, int m){

    if (cx > MAX_CODE_LENGTH){
        ERROR(26);
    }
    else{
        codeOut[cx].opcode = op;
        codeOut[cx].r = r;
        codeOut[cx].l = l;
        codeOut[cx].m = m;
        cx++;
    }

    return;
}


void addSymbol(char* name, int kind, int val, int level, int addr){

//    printf("Added: %s\n", name);
    strcpy(symbolTable[numSymbols].name,name);
    symbolTable[numSymbols].kind = kind;
    symbolTable[numSymbols].val = val;
    symbolTable[numSymbols].level = level;
    symbolTable[numSymbols].addr = addr;
    numSymbols++;
}

//returns index of a symbol (if found) based on name search, else returns -1
int searchSymbolTable(char name[10]){
    int i, j;
    for (j=l;j>=0;j--)
    {
    for (i = numSymbols; i >= 0; i--){
        if ((strcmp(symbolTable[i].name,name) == 0) && (symbolTable[i].level == j)) ///added l check
            return i;
        }
    }
    return -1;

}

int searchSymbolTableLevel(char name[10],int level)
{
    int i;
    for (i=numSymbols;i>=0;i--)
    {
        if ((strcmp(symbolTable[i].name,name) == 0) && (symbolTable[i].level == level)) ///added l check
            return i;
    }
    return -1;
}

int RELATION(token_type x){

    if (x == eqsym)
        return 18;
    if (x == neqsym)
        return 19;
    if (x == lessym)
        return 20;
    if (x == leqsym)
        return 21;
    if (x == gtrsym)
        return 22;
    if (x == geqsym)
        return 23;

    return 0;

}

//adds a symbol's name and value to a register, increments RP
void addSymRL(smb val)
{
    regList[rp].val = val.val; //lol @ this line
    if (val.name != NULL)
        strcpy(regList[rp].ident,val.name);
    rp++;
}

//searches in regList for a symbol by name
int searchSymRL(char* name)
{
    int k;
    for (k=0;k<16;k++)
        if (strcmp(regList[k].ident,name) == 0)
            return k; //return the index in regList
    return -1; //not found in regList
}

void getToken(){
    if (token->next != NULL){
        token = token->next;
    }
    else{

    }

}
