/*
============================================================================
Name 	    : project3.cpp
Author 	    : Aaron Shehan
Version     : 1.0.0
Copyright   : 2018
Description : This program allows a user to play connect 4 with the computer.
============================================================================
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
using namespace std;

enum {SPACE = 1, RED = 2, BLUE = 3};		//Enumeration constant for position of players and open space.
enum Status {POSITION = 'O'};			//Enumeration constant for letter 'O' to be used when board is printed.
const int COLUMNS = 6;				//Constant number of columns



/*
============================================================================
Function    : Header
Parameters  : NA
Return	    : NA
Description : This functino prints the header.
============================================================================
*/
void Header()
{
	cout << "\t +----------------------------------------------+\n";
	cout << "\t |       Computer Science and Engineering       |\n";
	cout << "\t |        CSCE 1030 - Computer Science I        |\n";
	cout << "\t | Aaron Shehan ats0109 aaronshehan@my.unt.edu  |\n";
	cout << "\t +----------------------------------------------+\n"; 
}


/*
============================================================================
Function    : Description
Parameters  : NA
Return	    : NA
Description : This function prints description of the game to be played.
============================================================================
*/
void Description() 
{
	cout << endl;
	cout << "\t  W e l c o me   t o   1 0 3 0   C o n n e c t" << endl; cout << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "This program will set up a game board to play 1030 Connect using a board " << endl;
	cout << "where the rows are determined by the user to be between 4 and 6, inclus-" << endl;
	cout << "ively, but the number of columns is fixed at 6." << endl; cout << endl;
	cout << "Then, the user (RED) will play against the computer (BLUE) to attempt to" << endl;
	cout << "connect four discs in a row, either horizontal or vertical, on the board." << endl;
	cout << "The user (RED) will start the game." << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl;
}

/*
============================================================================
Function    : initialBoard
Parameters  : an int array representing the game board
	      an int representing the number of rows in game board
Return	    : NA
Description : This function initializes each position of array and prints game board.
============================================================================
*/
void initialBoard(int gameBoard[][COLUMNS], int numRows)
{
	cout << "Initializing game board..." << endl;
	cout << "    1 2 3 4 5 6" << endl;
	cout << "  +-------------+" << endl;

	char letter = 'A'; 	//For column of letters corresponding to each row of the board.
	
	for (int i = 0; i < numRows; ++i)	//initializes each position of board to zero, and outputs a hyphen at each position
	{
		cout << letter << " | ";
		letter += 1;
		for (int j = 0; j < COLUMNS; ++j)
		{
			gameBoard[i][j] = SPACE;
			cout << "- ";
		}
		cout << "|" <<  endl;
	}	
	cout << "  +-------------+" << endl;		
}

/*
============================================================================
Function    : board_in_play
Parameters  : an int array representing the game board
	      an int representing the number of rows in the game board
	      an int representing the column the red players disc is to go
	      an int representing the column the blue players disc is to go
	      an int representing which players turn it is
Return	    : a bool representing the the outcome of the game
Description : This function places the disc into the column the red 
	      player or blue player selects and checks for the winner.
============================================================================
*/
bool board_in_play(int gameBoard[][COLUMNS], int numRows, int playerChoice, int aiChoice, int playerTurn)
{
	bool gameOver = false; 		//Eventual return value for board_in_play function. When true game is over.
	
	for (int i = numRows - 1; i > -1; --i)	//inserts disc into game board
	{
		if (playerTurn == RED)
		{
			if (gameBoard[i][playerChoice - 1] == SPACE)
			{
				gameBoard[i][playerChoice - 1] = RED;
				break;			
			}
			if (gameBoard[i][playerChoice - 1] != SPACE && i == 0)
			{
				cout << "Invalid Move: Turn forfeited." << endl;
				break;
			}
		}
		if (playerTurn == BLUE)
		{	
			if (gameBoard[i][aiChoice - 1] == SPACE)
			{
				gameBoard[i][aiChoice - 1] = BLUE;
				break;			
			}
			if (gameBoard[i][aiChoice - 1] != SPACE && i == 0)
			{
				cout << "Invalid Move: Turn forfeited." << endl;
				break;
			}

		}

	}

	int redWin; 	//Counter for red player to determine winner
	int blueWin; 	//Counter for blue player to determine winner

	for (int i = 0; i < numRows; ++i)	//checks for four discs in a row horizontally
	{
		redWin = 0;
		blueWin = 0;
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (gameBoard[i][j] == RED)
			{
				redWin += 1;
				blueWin = 0;
			}
			else if (gameBoard[i][j] == BLUE)
			{
				blueWin += 1;
				redWin = 0;
			}
			else
			{
				blueWin = 0;
				redWin = 0;
			}
	
			if (redWin == 4 || blueWin == 4)
			{
				gameOver = true;
				break;
			}
		}
	}


	for (int i = 0; i < COLUMNS; ++i)	//checks for four discs in a row vertically
	{
		redWin = 0; 
		blueWin = 0;
		for (int j = 0; j < numRows; ++j)
		{
			if (gameBoard[j][i] == RED)
			{
				redWin += 1;
				blueWin = 0;
			}
			else if (gameBoard[j][i] == BLUE)
			{
				blueWin += 1;
				redWin = 0;
			}
			else 
			{
				blueWin = 0;
				redWin = 0;
			}	

			if (redWin == 4 || blueWin == 4)
			{
				gameOver = true;
				break;
			}
		}
	}

	return gameOver;
}	

/*
============================================================================
Function    : board_after_turn
Parameters  : an int array representing the game board
	      an int representing the number of rows in the game board
Return	    : NA
Description : This function prints the game board with the updated player 
	      positions.
============================================================================
*/
void board_after_turn(int gameBoard[][COLUMNS], int numRows)
{
	cout << "    1 2 3 4 5 6" << endl;
	cout << "  +-------------+" << endl;

	char letter = 'A'; 			//For column of letters corresponding to each row of the board.
	
	for (int i = 0; i < numRows; ++i) 	//Loop used to discplay updated board with disc positions
	{	
		cout << letter << " | ";
		letter += 1;

		for (int j = 0; j < COLUMNS; ++j)
		{
			if (gameBoard[i][j] == SPACE) 	 //Prints '-' when location in array is equal to 0.
			{
				cout << "- ";
			}
			else if (gameBoard[i][j] == RED) //If specific location in array is equal to 2, a red 'O' is printed.
			{
				Status red = POSITION;
				printf("\033[1;31m%c\033[0m ", static_cast<char>(red)); 
			}
			else 
			{
				Status blue = POSITION; 
				printf("\033[1;34m%c\033[0m ", static_cast<char>(blue)); 
			}
		}
		cout << "|" <<  endl;
	}
	cout << "  +-------------+" << endl;
}

/*
============================================================================
Function    : tie_game_check
Parameters  : an int array representing the game board
Return	    : a bool that returns true if the game is a tie, otherwise false
Description : This function checks to see if the game has ended in a tie.
============================================================================
*/
bool tie_game_check(int gameBoard[][COLUMNS])
{
	bool tieGame = false;
	int tieCheck = 0;
	
	for(int i = 0; i < COLUMNS; ++i)
	{
		if (gameBoard[0][i] != SPACE)
		{
			tieCheck += 1;
		}
	}

	if (tieCheck == COLUMNS)
	{
		tieGame = true;
		cout << "Sorry, but the game has resulted in a DRAW with no winner." << endl;
	}

	return tieGame;
}

int main()
{
	int numRows; 	//User defined number of rows
	Header(); 	//Function call for header
	Description();  //Function call for description of the game
	
	do		//loop in case user enters invalid number for rows
	{
		cout << "Enter the desired number of rows on the board: ";
		cin >> numRows;
		
		if (numRows < 4 || numRows > 6)
		{
			cout << "Invalid number of rows. Must be between 4 and 6." << endl;
		}
	}
	while (numRows < 4 || numRows > 6);

	int gameBoard[numRows][COLUMNS];	//array for game board initialized with user defined rows and constant columns
	initialBoard(gameBoard, numRows);	//function call prints initial game board
	bool gameWinner = false;		//Determines if loop will terminate. True when winner is found.
	int playerChoice;			//used to select which column disc will fall in for user
	int playerTurn;				//decides which players turn it is
	int aiChoice;				//used to select which column disc will fall in for computer

	do
	{
		do	//loop in case user enters invalid number for disc to be placed
		{
			cout << "RED MOVE: Enter column to place RED disc: ";
			cin >> playerChoice;
			
			if (playerChoice < 1 || playerChoice > COLUMNS)
			{
				cout << "Invalid choice. Please select again." << endl;
			}
		}
		while (playerChoice < 1 || playerChoice > COLUMNS);

		playerTurn = RED;	//Red players turn.
		
		gameWinner = board_in_play(gameBoard, numRows, playerChoice, aiChoice, playerTurn);

		board_after_turn(gameBoard, numRows);
		
		if (gameWinner == true)
		{
			cout << "Congratulations, RED won the game!" << endl;
		}

		if (gameWinner == false)
		{
			gameWinner = tie_game_check(gameBoard);	
		}

		if (gameWinner == false)
		{
			srand(time(NULL));
			aiChoice = (rand() % 6) + 1;	//Randomly selected column choice for Blue player.

			cout << "BLUE MOVIE: Enter column to place BLUE disc: " << aiChoice << endl;

			playerTurn = BLUE;	//Blue players turn.

			gameWinner = board_in_play(gameBoard, numRows, playerChoice, aiChoice, playerTurn);

			board_after_turn(gameBoard, numRows);
			
			if (gameWinner == true)
			{
				cout << "Congratulations, BLUE won the game!" << endl;
			}
			
			if (gameWinner == false)
			{
				gameWinner = tie_game_check(gameBoard);	
			}
		}
	}
	while (gameWinner == false); 		//Game is over when true
	
	return 0;
}