//Josh Barnett


import java.io.*;
import java.util.*;

public class SudokuSolver{
	
	
public static void main(String[] args) {
	File textFile = new File("input.txt");
	Scanner fileScanner = new Scanner(textFile);
	int numLoops;
	int tempIn;
	int i, j, k;
	
	numLoops = fileScanner.nextInt();
	
	for (i=1;i<=numLoops;i++)
	{
		SudokuBoard testCase = new SudokuBoard();
		
		System.out.println("Test Case #:" + i + "\n");//extra escape sequence intentional for blank line
		
		for (j=0;j<9;j++)
			for (k=0;k<9;k++)
			{
				tempIn = fileScanner.nextInt();
				if (tempIn != 0)
					testCase.setSquare(j,k,tempIn);
			}
	
		if (testCase.solveSudoku() == true)
			testCase.printSolution();
		else
			System.out.println("There is no possible solution.\n");
	
	}
}

class SudokuBoard{
	
	public boolean solvable; //false by default, true if a solution is found
	private int squaresFilled; //0-81, how many squares have a concrete value 
	
	public void SudokuBoard{
		
		//initialize the game board out of a 9x9 grid of squares
		SudokuSquare[][] gameBoard = new SudokuSquare[9][9];
		for (int i = 0;i<9;i++)
			for (int j = 0; j<9;j++)
				gameBoard[i][j] = new SudokuSquare();
	}
	
	//Recursive algorithm to solve
	public boolean solveSudoku()
	{
		if (squaresFilled == 81)
			return true; //if every square has a value, return true (sudoku is solvable, program done)
			
		int i, j;
		for (i=0;i<9;i++)
			for (j=0;j<9;j++) //loop thru whole grid
			{
				if ((gameBoard[i][j].getVal != 0) && (gameBoard[i][j].getNumPossibilities() ==  1))//there's only one possible and it's not filled in
				{
					setSquare(i,j,gameBoard[i][j].onlyOnePossible()); //fill in the only possible value
					return solveSudoku(); //recursively call function on updated board
				}
				else if ((gameBoard[i][j].getVal != 0) && (gameBoard[i][j].getNumPossibilities() ==  2)) //the square can be one of two
				{ //backtrack and try both options
					return solveSudoku(i,j,gameBoard[i][j].getLowestPossible(),gameBoard[i][j].getHighestPossible());
				}
				else if ((gameBoard[i][j].getVal == 0) && (gameBoard[i][j].getNumPossibilities() ==  0))
					return false; //an unfilled square is found impossible to fill
			}
			
		//if it gets through the whole grid without being able to fill one in (all squares unfilled have 3 or more possibilities
		return false;
	}
	
	public boolean solveSudoku(int r, int c, int val1, int val2) //with row, column, and 2 values to insert/backtrack
	{
		setSquare(r,c,val1);
		if (solveSudoku() = true)
			return true;
		unsetSquare(r,c,val1);
		setSquare(r,c,val2);
		return solveSudoku();
	}
	
	public void setRow(int row, int val)
	{
		//mark val as impossible in all items of a given row, except for the one that has value val already
		int i;
		for (i=0;i<9;i++)
		{
			if (gameBoard[row][i].getVal() != val) //if it's not the square that just got set
				gameBoard[row][i].setImpossible(val);
		}
		
	}
	
	public void setCol(int col, int val)
	{
		//mark val as impossible in all items of a given column, except for the one that has value val already
		int i;
		for (i=0;i<9;i++)
		{
			if (gameBoard[i][col].getVal() != val) //if it's not the square that just got set
				gameBoard[i][col].setImpossible(val);
		}
		
	}
	
	public void setBox(int row, int col, int val)
	{
		//mark val as impossible in all items of a given box, except for the one that has value val already
		
		int i, j, k, l;
		if (row < 3)
			i = 0;
		else if (row < 6)
			i = 3;
		else
			i = 6;
		//adjust the loop position based on the section it is in
		if (col < 3)
			j = 0;
		else if (col < 6)
			j = 3;
		else
			j = 6;
		
		for (k=i;k<i+3;k++)
			for (l=j;l<j+3;l++)
			{
				if (gameBoard[k][l].getVal() != val)
					gameBoard[k][l].setImpossible(val);
			} //loop through the box it's in, set the value to impossible to all except the one that just got changed
		
	}
	
	public void setSquare(int row, int col, int val)
	{
		//Insert a value into a square, update impossibilities in row column and box. increment counter of squares filled
		gameBoard[row][col].setVal(val);
		setBox(row,col,val);
		setCol(col, val);
		setRow(row,val);
		squaresFilled++;
		
	}
	
	public void unsetRow(int row, int val)
	{
		//reverse of setRow
		int i;
		for (i=0;i<9;i++)
		{
			if (gameBoard[row][i].getVal() != val) //if it's not the square that just got set
				gameBoard[row][i].setPossible(val);
		}
		
	}
	
	public void unsetCol(int col, int val)
	{
		//reverse of setCol
		int i;
		for (i=0;i<9;i++)
		{
			if (gameBoard[i][col].getVal() != val) //if it's not the square that just got set
				gameBoard[i][col].setPossible(val);
		}
		
	}
	
	public void unsetBox(int row, int col, int val)
	{
		//reverse of setBox
		int i, j, k, l;
		if (row < 3)
			i = 0;
		else if (row < 6)
			i = 3;
		else
			i = 6;
		//adjust the loop position based on the section it is in
		if (col < 3)
			j = 0;
		else if (col < 6)
			j = 3;
		else
			j = 6;
		
		for (k=i;k<i+3;k++)
			for (l=j;l<j+3;l++)
			{
				if (gameBoard[k][l].getVal() != val)
					gameBoard[k][l].setPossible(val);
			} //loop through the box it's in, set the value to impossible to all except the one that just got changed
		
	}
	
	public void unsetSquare(int row, int col, int val)
	{
		//reverse of setSquare
		unsetBox(row,col,val);
		unsetCol(col, val);
		unsetRow(row,val);
		gameBoard[row][col].setVal(0);
		squaresFilled--;
		
	}
	
	public void printSolution()
	{
		int i, j;
		for (i=0;i<9;i++)
		{
			for (j=0;j<9;j++)
			{
				System.out.print(gameBoard[i][j].getVal() + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
	
}

class SudokuSquare{
	
	private int value;
	private int impossible[9]; // each value for 0-8 (corresponding to 1-9) is 0 by default, 
							 // and it is 1 if that is not a possible value for this square
							 
	public void SudokuSquare()
	{
		value = 0; //0 indicates undecided value
		for (int i = 0; i<9; i++) //initialize array of possibilities
			impossible[i] = 0;
	}
	
	public int getVal(){
		return value;
	}
	
	public void setVal(int val){
		value = val;
	}
	
	public int getImpossible(int val)
	{
		if ((val < 0) || (val > 8))
			return 0;
		else
			return impossible[val];
	}
	
	public void setImpossible(int val)
	{
		if !((val < 0) || (val > 8))
			impossible[val]++;
	}
	
	public void setPossible(int val)
	{
		if !((val < 0) || (val > 8))
			impossible[val]--;
	}
	
	public int getLowestPossible(){
		
		int i;
		for (i = 0; i < 9; i++)
		{
			if (impossible[i] == 0)
				return i;
		}
		return -1;
		
	}
	
	public int getHighestPossible(){
		
		int i;
		for (i = 8; i >= 0; i--)
		{
			if (impossible[i] == 0)
				return i;
		}
		return -1;
		
	}
	
	public int onlyOnePossible(){
		
		if (self.getHighestPossible() == self.getLowestPossible())
			return self.getHighestPossible();
		else
			return -2; //returns that there is more than one possible (didn't use -1 for debugging purposes)
		
	}
	
	public int getNumPossibilities(){
		
		int i, j;
		for (i=0;i<9;i++)
			if (impossible[i] == 0)
				j++;
		return j;
	}
	
	public boolean isNumPossible(int val)
	{
		if !((val < 0) || (val > 8))
			if impossible[val] = 0
				return true;
			else
				return false;
		else
			return false;

	}
	
}
