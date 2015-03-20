The files in this folder were done as a collaboration with Ronald Hyatt for the Systems Software class at UCF. 

This is a parser, lexical analyzer, and Virtual Machine for the "P-Machine" running the "PL/0" programming language 
(with minor variations on the official PL/0 language made specifically for the class).
Driver.C is the main file used to run, which integrates the three key parts of this project:
Lexi.C, which Lexically Analyzes and tokenizes a raw text file with PL/0 source code.
Parser.C, which parses these tokens into machine code for a P-Machine.
PM.C, which acts as a virtual machine for the P-Machine and outputs both the system status and register values at each step in the programs execution.


The README documentation that was turned in along with the assignment is as follows:

Ronald Hyatt & Josh Barnett
Systems Software
Assignment 3 PMachine
3-20-14


Compilation Instructions:
	1) Open your command prompt.
	2) Navigate to the directory of the downloaded program.
	3) Type in the command 'make'.

Running Instructions:
	1) Open your command prompt.
	2) Navigate to the directory of the downloaded program.
	3) Type in the command './Driver' followed by any arguments of your choice.
		a) The only arguments this program supports is '-v', '-a', and '-l'.
	4) The program will then prompt you for a name for the main output file.
	5) The program will ask for the souce file that you would like to run.
		a) This should be stored in the same directory as the program.

Read in file:

	const m = 7, n = 8;
	int  i,x,y,z,q,r,a,f,b;
	/*This is a comment
	that spans two lines*/
	  begin
		 a := 3;  b := 18; z := 0;
		 while b > 4 do
		 begin
			if odd x then z := z+a;
			   a := 2*a;
			   b := b/2;
			   /*This is an additional comment
			   it spans more lines*/
		 end
	  end.



Output to screen:
	What would you like the output file to be named?what
	What is the name of your input file that you would like to use?
	File must be in the same directory in which this program is running.
	input2.txt

	Source Program:
	const m = 7, n = 8;
	int  i,x,y,z,q,r,a,f,b;
	  begin
		 a := 3;  b := 18; z := 0;
		 while b > 4 do
		 begin
			if odd x then z := z+a;
			   a := 2*a;
			   b := b/2;

		 end
	  end.


	Lexeme Table:
	Lexeme          Token Type
	const           28
	m               2
	=               9
	7               3
	,               17
	n               2
	=               9
	8               3
	;               18
	int             29
	i               2
	,               17
	x               2
	,               17
	y               2
	,               17
	z               2
	,               17
	q               2
	,               17
	r               2
	,               17
	a               2
	,               17
	f               2
	,               17
	b               2
	;               18
	begin           21
	a               2
	:=              20
	3               3
	;               18
	b               2
	:=              20
	18              3
	;               18
	z               2
	:=              20
	0               3
	;               18
	while           25
	b               2
	>               13
	4               3
	do              26
	begin           21
	if              23
	odd             8
	x               2
	then            24
	z               2
	:=              20
	z               2
	+               4
	a               2
	;               18
	a               2
	:=              20
	2               3
	*               6
	a               2
	;               18
	b               2
	:=              20
	b               2
	/               7
	2               3
	;               18
	end             22
	end             22
	.               19

	Lexeme List:
	28 2 m 9 3 7 17 2 n 9 3 8 18 29 2 i 17 2 x 17 2 y 17 2 z 17 2 q 17 2 r 17 2 a 17 2 f 17 2 b

	Code generated from parser:
	6 0 0 4
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	6 0 0 1
	1 0 0 3
	4 0 0 10
	1 0 0 18
	4 0 0 12
	1 0 0 0
	4 0 0 7
	3 0 0 12
	1 1 0 4
	22 0 0 1
	8 0 0 36
	3 3 0 0
	16 3 0 0
	3 3 0 5
	3 4 0 7
	3 5 0 10
	12 4 4 5
	4 4 0 7
	1 0 0 2
	3 1 0 10
	14 0 0 1
	4 0 0 10
	3 0 0 12
	1 1 0 2
	15 0 0 1
	4 0 0 12
	7 0 0 16
	Line    OP      R       L       M       pc      bp      sp
	Initial Values                          0       1       0       0 0 0 0 0 0
	0       inc     0       0       4       1       1       4       0 0 0 0
	1       inc     0       0       1       2       1       5       0 0 0 0 0
	2       inc     0       0       1       3       1       6       0 0 0 0 0 0
	3       inc     0       0       1       4       1       7       0 0 0 0 0 0 0
	4       inc     0       0       1       5       1       8       0 0 0 0 0 0 0 0
	5       inc     0       0       1       6       1       9       0 0 0 0 0 0 0 0 0
	6       inc     0       0       1       7       1       10      0 0 0 0 0 0 0 0 0 0
	7       inc     0       0       1       8       1       11      0 0 0 0 0 0 0 0 0 0 0
	8       inc     0       0       1       9       1       12      0 0 0 0 0 0 0 0 0 0 0 0
	9       inc     0       0       1       10      1       13      0 0 0 0 0 0 0 0 0 0 0 0 0
	10      lit     0       0       3       11      1       13      0 0 0 0 0 0 0 0 0 0 0 0 0
	11      sto     0       0       10      12      1       13      0 0 0 0 0 0 0 0 0 0 3 0 0
	12      lit     0       0       18      13      1       13      0 0 0 0 0 0 0 0 0 0 3 0 0
	13      sto     0       0       12      14      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	14      lit     0       0       0       15      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	15      sto     0       0       7       16      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	16      lod     0       0       12      17      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	17      lit     1       0       4       18      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	18      gtr     0       0       1       19      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	19      jpc     0       0       36      20      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	20      lod     3       0       0       21      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	21      odd     3       0       0       22      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	22      lod     3       0       5       23      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	23      lod     4       0       7       24      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	24      lod     5       0       10      25      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	25      add     4       4       5       26      1       13      0 0 0 0 0 0 0 0 0 0 3 0 18
	26      sto     4       0       7       27      1       13      0 0 0 0 0 0 0 3 0 0 3 0 18
	27      lit     0       0       2       28      1       13      0 0 0 0 0 0 0 3 0 0 3 0 18
	28      lod     1       0       10      29      1       13      0 0 0 0 0 0 0 3 0 0 3 0 18
	29      mul     0       0       1       30      1       13      0 0 0 0 0 0 0 3 0 0 3 0 18
	30      sto     0       0       10      31      1       13      0 0 0 0 0 0 0 3 0 0 6 0 18
	31      lod     0       0       12      32      1       13      0 0 0 0 0 0 0 3 0 0 6 0 18
	32      lit     1       0       2       33      1       13      0 0 0 0 0 0 0 3 0 0 6 0 18
	33      div     0       0       1       34      1       13      0 0 0 0 0 0 0 3 0 0 6 0 18
	34      sto     0       0       12      35      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	35      jmp     0       0       16      16      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	16      lod     0       0       12      17      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	17      lit     1       0       4       18      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	18      gtr     0       0       1       19      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	19      jpc     0       0       36      20      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	20      lod     3       0       0       21      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	21      odd     3       0       0       22      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	22      lod     3       0       5       23      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	23      lod     4       0       7       24      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	24      lod     5       0       10      25      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	25      add     4       4       5       26      1       13      0 0 0 0 0 0 0 3 0 0 6 0 9
	26      sto     4       0       7       27      1       13      0 0 0 0 0 0 0 9 0 0 6 0 9
	27      lit     0       0       2       28      1       13      0 0 0 0 0 0 0 9 0 0 6 0 9
	28      lod     1       0       10      29      1       13      0 0 0 0 0 0 0 9 0 0 6 0 9
	29      mul     0       0       1       30      1       13      0 0 0 0 0 0 0 9 0 0 6 0 9
	30      sto     0       0       10      31      1       13      0 0 0 0 0 0 0 9 0 0 12 0 9
	31      lod     0       0       12      32      1       13      0 0 0 0 0 0 0 9 0 0 12 0 9
	32      lit     1       0       2       33      1       13      0 0 0 0 0 0 0 9 0 0 12 0 9
	33      div     0       0       1       34      1       13      0 0 0 0 0 0 0 9 0 0 12 0 9
	34      sto     0       0       12      35      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	35      jmp     0       0       16      16      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	16      lod     0       0       12      17      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	17      lit     1       0       4       18      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	18      gtr     0       0       1       19      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	19      jpc     0       0       36      36      1       13      0 0 0 0 0 0 0 9 0 0 12 0 4
	
	
	
