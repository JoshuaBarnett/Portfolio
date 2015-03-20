/**
*
*   Ronald Hyatt & Josh Barnett
*   Systems Software
*   Assignment 3 Lexi
*   3-20-14
*
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXIDENTLEN = 11
#define MAXNUMLEN = 5

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym,
lessym, leqsym, gtrsym, geqsym, lparentsym,
rparentsym, commasym, semicolonsym, periodsym, becomessym,
beginsym, endsym, ifsym, thensym, whilesym,
dosym, callsym, constsym, intsym, procsym,
writesym, readsym , elsesym } token_type;
//Structure to hold the lexmeme List
typedef struct LexemeList{
	char ident[11];
	token_type tokenval;
	struct LexemeList* prev;
	struct LexemeList* next;
}LexTok;

int getFile();
int findFileLen();
int checkForReserved(char tempChar[], int j);
int printProgram(char sourceProgram[], int charCounter);
void fillCharArray(char sourceProgram[], int charCounter);
void initializeArray(char sourceProgram[], int charCounter);
void doWork(char sourceProgram[], int charCounter);
void addToLexi(char *ident, int value);
void printList();
void grabError(int errorNumber);

FILE *ifp, *mopf;
LexTok *lexiList = NULL;
int printOut = 0;

LexTok* lexi(int printToScreen, FILE *mainOutput){
    int boolCheck, charCounter = 0, i;

    //Grab the file that we need
    boolCheck = getFile();
    printOut = printToScreen;
    mopf = mainOutput;

    if(boolCheck == 0){
        printf("I'm sorry, that is not a valid file.\n");
        printf("Please try running program again with valid file.\n");
        return NULL;
    }

    //Find the size of char array we need and create enough space
    charCounter = findFileLen();
    rewind(ifp);
    char sourceProgram[charCounter + 1];
    initializeArray(sourceProgram, charCounter);

    fillCharArray(sourceProgram, charCounter + 1);

    charCounter = printProgram(sourceProgram, charCounter);

    //Print to the main output file
    fprintf(mopf, "%s\n", sourceProgram);

    //Print to the screen
    if (printOut == 1){
        printf("%s\n", sourceProgram);
    }

    doWork(sourceProgram, charCounter);

    fprintf(mopf, "\n");
    if (printOut == 1){
        printf("\n");
    }
    printList();

    fprintf(mopf, "\n");
    if (printOut == 1){
        printf("\n");
    }
    fclose(ifp);
    return lexiList;
}

void printList(){
    LexTok *temp = NULL;
    temp = lexiList;

    fprintf(mopf, "Lexeme List:\n");
    if (printOut == 1){
        printf("Lexeme List:\n");
    }

    while (temp != NULL){
        fprintf(mopf, "%d ", temp->tokenval);
        if (printOut == 1){
            printf("%d ", temp->tokenval);
        }
        if (temp->tokenval == 2 || temp->tokenval == 3){
            fprintf(mopf, "%s ", temp->ident);
            if (printOut == 1){
                printf("%s ", temp->ident);
            }
        }
        temp = temp->next;
    }


}

//Here is where we do the work and separate the symbols and what not
//Place into two arrays and send each to a print function using it's length and contents
void doWork(char sourceProgram[], int charCounter){
    int i, l, j, reserved;
    char tempChar[12];

    //Print out the header of the table
    fprintf(mopf, "\nLexeme Table:\n");
    fprintf(mopf, "Lexeme\t\tToken Type\n");
    if (printOut == 1){
            printf("\nLexeme Table:\n");
            printf("Lexeme\t\tToken Type\n");
    }

    //Read char by char to see what we have based on our stopping casses
    for (i = 0; i <= charCounter; i ++){
        initializeArray(tempChar, 12);
        reserved = 0;
        //Ignored cases -- Most used so right up at the top
        if (sourceProgram[i] == ' ' || sourceProgram[i] == '\n' || sourceProgram[i] == '\r' ||
            sourceProgram[i] == '\0' || sourceProgram[i] == '\t'){
            continue;
        }
        else if (sourceProgram[i] == '+'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], plussym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], plussym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, plussym);
        }
        else if (sourceProgram[i] == '-'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], minussym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], minussym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, minussym);
        }
        else if (sourceProgram[i] == '*'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], multsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], multsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, multsym);
        }
        else if (sourceProgram[i] == '/'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], slashsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], slashsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, slashsym);
        }
        else if (sourceProgram[i] == '='){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], eqsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], eqsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, eqsym);
        }
        else if (sourceProgram[i] == '<'){
            if (sourceProgram[i+1] == '>'){
                fprintf(mopf, "%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], neqsym);
                if (printOut == 1){
                    printf("%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], neqsym);
                }
                tempChar[0] = sourceProgram[i];
                tempChar[1] = sourceProgram[i+1];
                tempChar[2] = '\0';
                addToLexi(tempChar, neqsym);
                i = i + 1;
             }
            else if (sourceProgram[i + 1] == '='){
                fprintf(mopf, "%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], leqsym);
                if (printOut == 1){
                    printf("%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], leqsym);
                }
                tempChar[0] = sourceProgram[i];
                tempChar[1] = sourceProgram[i+1];
                tempChar[2] = '\0';
                addToLexi(tempChar, leqsym);
                i = i + 1;
            }
            else {
                fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], lessym);
                if (printOut == 1){
                    printf("%c\t\t%d\n", sourceProgram[i], lessym);
                }
                tempChar[0] = sourceProgram[i];
                tempChar[1] = '\0';
                addToLexi(tempChar, lessym);
            }
        }
        else if (sourceProgram[i] == '>'){
            if (sourceProgram[i + 1] == '='){
                fprintf(mopf, "%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], geqsym);
                if (printOut == 1){
                    printf("%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], geqsym);
                }
                tempChar[0] = sourceProgram[i];
                tempChar[1] = sourceProgram[i+1];
                tempChar[2] = '\0';
                addToLexi(tempChar, geqsym);
                i = i + 1;
            }
            else {
                fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], gtrsym);
                if (printOut == 1){
                    printf("%c\t\t%d\n", sourceProgram[i], gtrsym);
                }
                tempChar[0] = sourceProgram[i];
                tempChar[1] = '\0';
                addToLexi(tempChar, gtrsym);
            }
        }
        else if (sourceProgram[i] == ';'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], semicolonsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], semicolonsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, semicolonsym);
        }
        else if (sourceProgram[i] == '.'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], periodsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], periodsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, periodsym);
        }
        else if (sourceProgram[i] == '('){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], lparentsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], lparentsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, lparentsym);
        }
        else if (sourceProgram[i] == ')'){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], rparentsym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], rparentsym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, rparentsym);
        }
        else if (sourceProgram[i] == ','){
            fprintf(mopf, "%c\t\t%d\n", sourceProgram[i], commasym);
            if (printOut == 1){
                printf("%c\t\t%d\n", sourceProgram[i], commasym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = '\0';
            addToLexi(tempChar, commasym);
        }
        else if (sourceProgram[i] == ':' && sourceProgram[i + 1] == '='){
            fprintf(mopf, "%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], becomessym);
            if (printOut == 1){
                printf("%c%c\t\t%d\n", sourceProgram[i], sourceProgram[i + 1], becomessym);
            }
            tempChar[0] = sourceProgram[i];
            tempChar[1] = sourceProgram[i+1];
            tempChar[2] = '\0';
            addToLexi(tempChar, becomessym);
            i = i + 1;
        }
        else if (isdigit(sourceProgram[i])){
            tempChar[0] = sourceProgram[i];
            j = 1;
            while (isdigit(sourceProgram[i + j])){
                if (j >= 5){
                    grabError(2);
                    return;
                }
                tempChar[j] = sourceProgram[i + j];
                j = j + 1;
            }
            if (sourceProgram[i + j] != ';'){
                if (sourceProgram[i + j] != ','){
                    if (sourceProgram[i + j] != ' '){
                        if (sourceProgram[i + j] != '*'){
                            if (sourceProgram[i + j] != '/'){
                                if (sourceProgram[i + j] != '+'){
                                    if (sourceProgram[i + j] != '-'){
                                        if (sourceProgram[i + j] != '('){
                                            if (sourceProgram[i + j] != ')'){
                                                if (sourceProgram[i + j] != '\r'){
                                                    if (sourceProgram[i + j] != '\n'){
                                                        grabError(1);
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for (l = 0; l <= j; l++){
                fprintf(mopf, "%c", tempChar[l]);
                if (printOut == 1){
                    printf("%c", tempChar[l]);
                }
            }
            fprintf(mopf, "\t\t%d\n", numbersym);
            if (printOut == 1){
                printf("\t\t%d\n", numbersym);
            }
            tempChar[j] = '\0';
            addToLexi(tempChar, numbersym);
            i = i + j - 1;
        }
        else if (isalpha(sourceProgram[i])){
            tempChar[0] = sourceProgram[i];
            j = 1;
            while (isalnum(sourceProgram[i + j])){
                if (j >= 11){
                    grabError(3);
                    return;
                }
                tempChar[j] = sourceProgram[i+j];
                j = j + 1;
            }
            tempChar[j] = '\0';

            for (l = 0; l < j; l ++){
                fprintf(mopf, "%c", tempChar[l]);
                if (printOut == 1){
                    printf("%c", tempChar[l]);
                }
            }
            //Check if the variable is a reserved word and act appropriatly
            reserved = checkForReserved(tempChar, j);
            if (reserved != 1){
                fprintf(mopf, "\t\t%d\n", identsym);
                if (printOut == 1){
                    printf("\t\t%d\n", identsym);
                }
                addToLexi(tempChar, identsym);
            }
            i = i + j - 1;
        }
        else {
            grabError(4);
            return;
        }
    }
}

int checkForReserved(char tempChar[], int j){
    int reserved = 0;

    if (tempChar[0] == 'c' && tempChar[1] == 'o' && tempChar[2] == 'n' &&
        tempChar[3] == 's' && tempChar[4] == 't' && tempChar[5] == '\0'){
        fprintf(mopf, "\t\t%d\n", constsym);
        if (printOut == 1){
            printf("\t\t%d\n", constsym);
        }
        addToLexi(tempChar, constsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'i' && tempChar[1] == 'n' && tempChar[2] == 't' &&
        tempChar[3] == '\0'){
        fprintf(mopf, "\t\t%d\n", intsym);
        if (printOut == 1){
            printf("\t\t%d\n", intsym);
        }
        addToLexi(tempChar, intsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'p' && tempChar[1] == 'r' && tempChar[2] == 'o' &&
        tempChar[3] == 'c' && tempChar[4] == 'e' && tempChar[5] == 'd' &&
        tempChar[6] == 'u' && tempChar[7] == 'r' && tempChar[8] == 'e'&&
        tempChar[9] == '\0'){
        fprintf(mopf, "\t%d\n", procsym);
        if (printOut == 1){
            printf("\t%d\n", procsym);
        }
        addToLexi(tempChar, procsym);
        reserved = 1;
    }
    //Uncomment for call symbol
    else if (tempChar[0] == 'c' && tempChar[1] == 'a' && tempChar[2] == 'l' &&
        tempChar[3] == 'l' && tempChar[4] == '\0'){
        fprintf(mopf, "\t\t%d\n", callsym);
        if (printOut == 1){
            printf("\t\t%d\n", callsym);
        }
        addToLexi(tempChar, callsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'b' && tempChar[1] == 'e' && tempChar[2] == 'g' &&
        tempChar[3] == 'i' && tempChar[4] == 'n' && tempChar[5] == '\0'){
        fprintf(mopf, "\t\t%d\n", beginsym);
        if (printOut == 1){
            printf("\t\t%d\n", beginsym);
        }
        addToLexi(tempChar, beginsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'e' && tempChar[1] == 'n' && tempChar[2] == 'd' &&
        tempChar[3] == '\0'){
        fprintf(mopf, "\t\t%d\n", endsym);
        if (printOut == 1){
            printf("\t\t%d\n", endsym);
        }
        addToLexi(tempChar, endsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'i' && tempChar[1] == 'f' && tempChar[2] == '\0'){
        fprintf(mopf, "\t\t%d\n", ifsym);
        if (printOut == 1){
            printf("\t\t%d\n", ifsym);
        }
        addToLexi(tempChar, ifsym);
        reserved = 1;
    }
    else if (tempChar[0] == 't' && tempChar[1] == 'h' && tempChar[2] == 'e' &&
        tempChar[3] == 'n' && tempChar[4] == '\0'){
        fprintf(mopf, "\t\t%d\n", thensym);
        if (printOut == 1){
            printf("\t\t%d\n", thensym);
        }
        addToLexi(tempChar, thensym);
        reserved = 1;
    }
    else if (tempChar[0] == 'e' && tempChar[1] == 'l' && tempChar[2] == 's' &&
        tempChar[3] == 'e' && tempChar[4] == '\0'){
        fprintf(mopf, "\t\t%d\n", elsesym);
        if (printOut == 1){
            printf("\t\t%d\n", elsesym);
        }
        addToLexi(tempChar, elsesym);
        reserved = 1;
    }
    else if (tempChar[0] == 'w' && tempChar[1] == 'h' && tempChar[2] == 'i' &&
        tempChar[3] == 'l' && tempChar[4] == 'e' && tempChar[5] == '\0'){
        fprintf(mopf, "\t\t%d\n", whilesym);
        if (printOut == 1){
            printf("\t\t%d\n", whilesym);
        }
        addToLexi(tempChar, whilesym);
        reserved = 1;
    }
    else if (tempChar[0] == 'd' && tempChar[1] == 'o' && tempChar[2] == '\0'){
        fprintf(mopf, "\t\t%d\n", dosym);
        if (printOut == 1){
            printf("\t\t%d\n", dosym);
        }
        addToLexi(tempChar, dosym);
        reserved = 1;
    }
    else if (tempChar[0] == 'r' && tempChar[1] == 'e' && tempChar[2] == 'a' &&
        tempChar[3] == 'd' && tempChar[4] == '\0'){
        fprintf(mopf, "\t\t%d\n", readsym);
        if (printOut == 1){
            printf("\t\t%d\n", readsym);
        }
        addToLexi(tempChar, readsym);
        reserved = 1;
    }
    else if (tempChar[0] == 'w' && tempChar[1] == 'r' && tempChar[2] == 'i' &&
        tempChar[3] == 't' && tempChar[4] == 'e' && tempChar[5] == '\0'){
        fprintf(mopf, "\t\t%d\n", writesym);
        if (printOut == 1){
            printf("\t\t%d\n", writesym);
        }
        addToLexi(tempChar, writesym);
        reserved = 1;
    }
    else if (tempChar[0] == 'o' &&tempChar[1] == 'd' && tempChar[2] == 'd' && tempChar[3] == '\0'){
        fprintf(mopf, "\t\t%d\n", oddsym);
        if (printOut == 1){
            printf("\t\t%d\n", oddsym);
        }
        addToLexi(tempChar, oddsym);
        reserved = 1;
    }

    return reserved;
}

void grabError(int errorNumber){
    if (errorNumber == 1){
        printf("Error 26: Variable does not start with a letter.\n");
        exit(EXIT_FAILURE);
    }
    else if (errorNumber == 2){
        printf("Error 25: Variable number too long.\n");
        exit(EXIT_FAILURE);
    }
    else if (errorNumber == 3){
        printf("Error 27: Variable name too long.\n");
        exit(EXIT_FAILURE);
    }
    else if (errorNumber == 4){
        printf("Error 28: Invalid Symbols.\n");
        exit(EXIT_FAILURE);
    }
}

//Function to add a new node to a linked list of tokens
void addToLexi(char *ident, int value){

    LexTok *newNode = NULL;
    LexTok *pointer = NULL;

    newNode = (LexTok*)malloc(sizeof(LexTok));

    strcpy(newNode->ident, ident);
    newNode->tokenval = value;
    newNode->next = NULL;

    pointer = lexiList;

    if (pointer == NULL){
        lexiList = newNode;
        lexiList->next = NULL;
        lexiList->prev = NULL;
    }
    else {
        while (pointer->next != NULL){
            pointer = pointer->next;
        }
        pointer->next = newNode;
        newNode->prev = pointer;
    }
    return;
}

//Print the program, erase the comments, and save the new array to the old one
int printProgram(char sourceProgram[], int charCounter){
    int i, j, s = 0;
    char tempArray[charCounter];
    fprintf(mopf, "\nSource Program:\n");
    if (printOut == 1){
        printf("\nSource Program:\n");
    }
    for (i = 0; i < charCounter; i ++){
        tempArray[i] = sourceProgram[i];
        if (sourceProgram[i] == '/' && sourceProgram[i + 1] == '*'){
            i = i + 2;
            for (j = 0; j < charCounter -  i; j ++){
                if (sourceProgram [i + j - 1] == '*' && sourceProgram [i + j] == '/'){
                    i = i + j;
                    if (sourceProgram[i + j + 1] == '\n' || sourceProgram[i + j + 1] == '\r'){
                        i = i + 1;
                    }
                    break;
                }
            }
        }
        else {
            tempArray[s] = sourceProgram[i];
            s = s + 1;
        }
    }
    tempArray[s] = '\0';
    strcpy(sourceProgram, tempArray);

    return s;
}

//Run through file and fill the char array
void fillCharArray(char sourceProgram[], int charCounter){
    char current;
    int i;

    //Loop through the file and grab everything that isn't an enter
    for (i = 0; i < charCounter; i ++){
        current = fgetc(ifp);
        sourceProgram[i] = current;
    }
    sourceProgram[charCounter] = '\0';
}

//Initialize the array
void initializeArray(char sourceProgram[], int charCounter){
    int i;

    for (i = 0; i < charCounter; i ++){
        sourceProgram[i] = ' ';
    }
}

int findFileLen(){
    int len = 0;

    while(fgetc(ifp) != EOF){
        len = len + 1;
    }
    return len;
}


//Function to grab the source file.
int getFile(){
    char inputFileName[25];
    int input;

    printf("What is the name of your input file that you would like to use?\n");
    printf("File must be in the same directory in which this program is running.\n");
    gets(inputFileName);

    ifp = fopen(inputFileName, "r");

    while (ifp == NULL){
        printf("Unable to open input file \"%s\".\n", inputFileName);
        printf("Would you like to:\n");
        printf ("\t1) Retry your file name.\n");
        printf ("\t2) Exit the program.\n");
        scanf("%d", &input);

        if (input == 1){
            printf("\nWhat is the name of your input file that you would like to use?\n");
            printf("File must be in the same directory as this program.\n\n");
            gets(inputFileName);
            ifp = fopen(inputFileName, "r");
        }
        else if (input == 2){
                printf ("Now exiting\n");
                return 0;
        }
    }

    return 1;
}
