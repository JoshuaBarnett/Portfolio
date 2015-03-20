/**
*
*   Ronald Hyatt & Josh Barnett
*   Systems Software
*   Assignment 4 Compile Driver
*   3-20-14
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Lexi.c"
#include "PM.c"
#include "Parser.c"


#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

FILE *mopf;


int main(int argc, char *argv[]){

    int l = 0, a = 0, v = 0, check = 1, i;
    char mainOutputFile[25];
    char* command;

    LexTok *lexiReturn = NULL;

    for (i = 1; i < argc; i ++){
        command = argv[i];
//        printf("Argument #%d: %s\n", i, command);
        if ((strcmp(command, "-l")) == 0) {
            l = 1;
        }
        else if ((strcmp(command, "-a")) == 0){
            a = 1;
//            printf("A has turned to true\n");
        }
        else if ((strcmp(command, "-v")) == 0){
            v = 1;
//            printf("V has turned to true\n");
        }
    }

    printf("What would you like the output file to be named?");
    gets(mainOutputFile);
    mopf = fopen(mainOutputFile, "w");

//printf("Going to lexi!\n");
    lexiReturn = lexi(l, mopf);

//printf("Going to parser!\n");
    parser(a, mopf, lexiReturn);

//printf("Going to pmachine!\n");
    mopf = pmachine(v, mopf);

//printf("Done!\n");
    return 0;
}
