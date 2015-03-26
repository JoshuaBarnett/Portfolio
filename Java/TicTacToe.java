// Josh Barnett
//11/28/12

import java.io.*;
import java.util.*;

public class TicTacToe {

  
  public enum SquareType { X, O, EMPTY };

  
  //array for the playing field
  private SquareType[][] board;
  //whose turn it is (should only be X or O)
  private SquareType turntracker;
  //how many moves have happened  
  int movecounter;

  // Begin Constructor
  public TicTacToe() {


    //Initialize the board and other important variables
    board = new SquareType[3][3];

    for (int i=0;i < 3; i++)
      for (int j=0; j < 3; j++)
        board[i][j] = SquareType.EMPTY;

    turntracker = SquareType.X;
    movecounter = 0;
  } //End Constructor

  //Checks if the inputed row and column are in the valid range
    public int validSquare(int r, int c) {

    if (((r > 0) && (r < 2)) && ((c > 0) && (c <2)))
      return 1;
    else
	return 0;
  }

  // Makes a move and returns 1, or it returns 0 if the space is occupied
  public int Move(int r, int c) {

    // Make the necessary changes here.
    if ((board[r][c] == SquareType.EMPTY) && validSquare(r,c)) {
      board[r][c] = turntracker;
      movecounter++;
      return 1;
    }
    else
      return 0;
  }


  // Returns the current player's name.
  public String getCurrentString() {
    if (turntracker == SquareType.X)
      return "Player X";
    else
      return "Player O";
  }

  // Switch the turn tracker (at the end of each turn)
  public void endTurn() {

    if (turntracker == SquareType.X) 
      turntracker = SquareType.O;
    else
      turntracker = SquareType.X;
  }

  // Added method to return a character corresponding to a SquareType.
  public char squareTypeToChar(SquareType square) {
    if (square == SquareType.X)
       return 'X';
    else if (square == SquareType.O)
       return 'O';
    else
       return ' ';
  }

  // Print the current board
  public void printGrid() {

    for (int i=0; i<23; i++)
	 System.out.print("-"); //print the top of the grid
    System.out.println();

    for (int j=0; j<3; j++) 
      {
      System.out.println("|       |       |       |");
      
      for (int k=0; k<3; k++)
        System.out.print("|   " + 
		squareTypeToChar(board[i][j])+"   |");
      
      System.out.println();
      System.out.println("|       |       |       |");

	 for (int l=0; l<23; l++)
	 	System.out.print("-"); //print divider/bottom of grid
    System.out.println();
    }

  }


  // Returns the winner.
  public SquareType winner() {

    for (int i=0; i<3; i++) //check the columns
      if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        return board[i][0];

    for (int i=0; i<3; i++) //check the rows
      if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
         return board[0][i];

    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) //check one diagonal
         return board[0][0];

    if ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2])) //check other diagonal
         return board[2][0];

    // if all squares filled
    if (movecounter == 9)
      return SquareType.EMPTY
  }

  
  // check to see if x won (to be called after a winner is determined), if not return 0
  public String getWinner(SquareType status) {
    if (s == SquareType.X) return "Player X";
    return "Player O";
  }

  public static void main(String[] args) throws IOException {

    Scanner newscanner = new Scanner(System.in);

    // Create the board/game
    TicTacToe currentgame = new TicTacToe();

    while (movecounter < 9) {


      boolean done = false;
      int r,c;

      while (!done) {
	
        currentgame.printGrid();

	System.out.println(currentgame.getCurrentString() + "s turn.");
        System.out.print(currentgame.getCurrentString());            
        System.out.println(": Enter row ( 0, 1 or 2 ):");
      	r = newscanner.nextInt();

        System.out.print(currentgame.getCurrentString());            
        System.out.println(": Enter column ( 0, 1 or 2 ):");
      	c = newscanner.nextInt();	

        if (currentgame.validSquare(r,c) == 1) 
        {
          if (currentgame.Move(r,c) == 0)
            System.out.println("Sorry, that square is filled.");
          else
            done = true;
       }  
	  else
          System.out.println("Sorry, those are invalid entries.");
        
      }
	
      currentgame.endTurn();
    }

	//game is over
    currentgame.printGrid();
    SquareType win = currentgame.winner();
    if (win == SquareType.EMPTY)
      System.out.println("CAT'S GAME!");
    else
      System.out.println(currentgame.getWinner(win) + " won.");    

  }
}
