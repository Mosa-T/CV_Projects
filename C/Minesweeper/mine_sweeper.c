/****************************************************************************************************

		id: ********
		name: Mosa Thoukwho

		Minesweeper game, what else is there to it?, have fun!.

***************************************************************************************************/

/* Include files */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/* Definitions */
#define TRUE 1
#define FALSE 0

/* Function prototypes */
void display_welcome();
char  **build_2d_array(int columns, int rows);
void print_arr(char **arrayr, int rows, int columns);
void bomber_man(char **array, int columns, int rows, int num_of_mines);
bool check_near_mines(char **board, int pickrow, int pickcol, int ROWS, int COLS, int mine);
char **replica_array(char **array, int rows, int cols);
void picker(char **board, int ROWS, int COLS, int mines);
char bomb_count(char **board, int pickrow, int pickcol, int ROW, int COL, int mine);
bool first_click();
void board_rest(char **board, int rows, int cols);
void check_win(char **array, int rows, int cols, int mine);

/* Main function */
int main()
{
	int rows, columns, mines;
	char **board_arr;
	char **replica_arr;
	display_welcome();
	printf("Enter number of rows: ");
	scanf("%d", &rows);
	printf("Enter number of columns: ");
	scanf("%d", &columns);
	board_arr = build_2d_array(columns, rows);
	printf("Enter number of mines(no bigger than %d): ", (rows*columns));
	scanf("%d", &mines);
	printf("\n\nPlease note that if your first move lands you on a mine, it might take a few seconds for the game to refresh mine placements!\n\n");
	bomber_man(board_arr, columns, rows, mines);
	//print_arr(replica_arr , rows, columns);
	//printf("\n\nprint replica of the array now\n");
	printf("\n\n       (^U^)\n\n");
	print_arr(board_arr, rows, columns);
	picker(board_arr, rows, columns, mines);
	check_win(board_arr, rows, columns, mines);
	replica_arr = replica_array(board_arr, columns, rows);
	print_arr(replica_arr, rows, columns);
	free(replica_arr);
	free(board_arr);
	return 0;
}

/* Recursive function for checking for nearby mines, plus advancing through the tiles if there are no mines near the tile and reveal said tiles up untill the nearest tile with a mine in it's area. */
bool check_near_mines(char **board, int pickrow, int pickcol, int ROWS, int COLS, int mine)
{
	if (pickrow < 1 || pickrow >= ROWS) return 0;     /* skip off-board tiles */
	if (pickcol < 1 || pickcol >= COLS) return 0;
	if (bomb_count(board, pickrow, pickcol, ROWS, COLS, mine) != '0') return 0;
	else {
		if (board[pickrow][pickcol] == '0') {
			check_near_mines(board, pickrow - 1, pickcol, ROWS - 1, COLS, mine);				 // ^
			check_near_mines(board, pickrow, pickcol - 1, ROWS, COLS - 1, mine);				 // <
			check_near_mines(board, pickrow, pickcol + 1, ROWS, COLS, mine);					 // >
			check_near_mines(board, pickrow + 1, pickcol, ROWS, COLS, mine);					 // v
			check_near_mines(board, pickrow + 1, pickcol + 1, ROWS, COLS - 1, mine);			 // v>
			check_near_mines(board, pickrow + 1, pickcol - 1, ROWS, COLS - 1, mine);			 // v<
			check_near_mines(board, pickrow - 1, pickcol + 1, ROWS - 1, COLS, mine);			 // ^>
			check_near_mines(board, pickrow - 1, pickcol - 1, ROWS - 1, COLS - 1, mine);		 // ^<
			return 0;
		}
	}
	return 0;
}

/* Checks if conditions of a won game are met. */
void check_win(char **array, int rows, int cols, int mine)
{
	int fields_count = 0;
	int i, j;
	for (i = 1; i < rows; i++) {
		for (j = 1; j < cols; j++) {
			//printf(" %c ", array[i][j]);
			if (array[i][j] == '-') continue;
			if (array[i][j] != 'x') fields_count++;
		}
		//printf("\n\n\n\n");
	}
	if (fields_count == ((rows - 1) * (cols - 1) - mine)) {
		printf("\n    YOU'VE WON\n\n");
		print_arr(array, rows - 1, cols - 1);
		exit(1);
	}
	return;
}

/* A replica used to display the end of the game results. used to reveal the mines in a lost game but stopped working so changes were made */
char **replica_array(char **arrayr, int rows, int cols)
{
	int i, j;
	rows += 2;
	cols += 2;
	char **replica_array = (char **)calloc(rows, sizeof(char *));
	if (replica_array == NULL) {
		printf("could not allocate number of rows\n");
		exit(1);
	}
	for (i = 0; i < rows; i++) {
		replica_array[i] = (char *)calloc(cols, sizeof(char));
		if (replica_array[i] == NULL) {
			printf("could not allocate the column for row %d\n", i);
			exit(1);
		}
	}
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			replica_array[j][i] = arrayr[j][i];
		}
	}
	replica_array[0][0] = 'm';
	return replica_array;
}

/* Checks if it's the first move the player makes, used to make sure the first tile picked isn't a mine. */
bool first_click()
{
	static int firstclicked = 1;
	if (firstclicked == 1) {
		firstclicked *= 0;
		return 1;
	}
	return firstclicked;
}

/* Rests the board, used for when the first move lands player on the mine. */
void board_rest(char **board, int rows, int cols)
{
	int i, j;
	for (i = 1; i < rows + 1; i++) {
		for (j = 1; j < cols + 1; j++) {
			board[i][j] = '-';
		}
	}
}

/* Main function used, lets player pick rows and columns, uses other function to open, determine results and prints them.
   Also rests board if the first move lands player on a mine. */
void picker(char **board, int ROWS, int COLS, int mines)
{
	int pickrow, pickcol;
	bool died_or_won = 0;
	while (died_or_won != 1) {
		printf("GIVE ROW NUMBER ");
		scanf("%d", &pickrow);
		printf("GIVE COLUMN NUMBER ");
		scanf("%d", &pickcol);
		if (COLS < pickcol || ROWS < pickrow) {
			printf("Please enter correct row or column.\n");
			continue;
		}
		/*
		if (board[pickrow][pickcol] == '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8') {	// already revealed, skip, should work, tried other things but doesn't so ignored.
		printf("you choose this index already!\n");
		continue;
		}
		*/
		if (first_click() == 1 && board[pickrow][pickcol] == 'x') {
			while (board[pickrow][pickcol] == 'x') {
				board_rest(board, ROWS, COLS);
				bomber_man(board, COLS, ROWS, mines);
				print_arr(board, ROWS, COLS);
			}
		}
		check_win(board, ROWS + 1, COLS + 1, mines);
		if (board[pickrow][pickcol] == 'x') {
			printf("\n\n       (x_X)\n\n");
			printf("     u ded son\n\n");
			return;
		}
		printf("\n\n       (^U^)\n\n");
		died_or_won = check_near_mines(board, pickrow, pickcol, ROWS + 1, COLS + 1, mines);
		check_win(board, ROWS + 1, COLS + 1, mines);
		print_arr(board, ROWS, COLS);
	}
}

/* Fill board with number of bombs player wants			add size == mines */
void bomber_man(char **array, int columns, int rows, int num_of_mines)
{
	while (columns*rows < num_of_mines) {
		printf("\ntoo many mines!, type number of mines again: ");
		scanf("%d", &num_of_mines);
		return bomber_man(array, columns, rows, num_of_mines);
	}
	int i, j;
	srand(time(NULL));
	while (num_of_mines > 0) {
		i = rand() % (rows + 1);
		if (i == 0) i += 1;
		j = rand() % (columns + 1);
		if (j == 0) j += 1;
		//printf("%d AND %d\n", i, j);
		if (array[i][j] != 'x') {
			array[i][j] = 'x';
			--num_of_mines;
		}
	}
}

/* Displays the welcome message */
void display_welcome()
{
	char c;
	printf("-----------------------Welcome to Minesweeper!---------------------------\n");
	printf("please set the number of rows, columns and mines to start the game!.\n\n\n                     Press ENTER to continue\n\n");
	scanf("%c", &c);
}

/* Build the board */
char  **build_2d_array(int columns, int rows)
{
	int i, j;
	rows += 2;
	columns += 2;
	char **array = (char **)calloc(rows, sizeof(char *)); //+2 for extra rows for when we use recusion.
	if (array == NULL) {
		printf("could not allocate number of rows\n");
		exit(1);
	}
	for (i = 0; i < rows; i++) {
		array[i] = (char *)calloc(columns, sizeof(char));
		if (array[i] == NULL) {
			printf("could not allocate the column for row %d\n", i);
			exit(1);
		}
	}
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			array[i][j] = '-';
		}
	}
	return array;
}

/* Prints the board */
void print_arr(char **arrayr, int rows, int columns)
{
	printf("\r");
	int i, j, cnt;
	printf("   +---+");
	for (i = 0; i < columns - 1; i++) {
		printf("---+");
	}
	printf("\n");
	for (i = 1; i < rows + 1; i++) {
		printf("%2d-|", i);
		for (j = 1; j < columns + 1; j++) {
			/***************** ADD BACK IN *******/
			if (arrayr[0][0] != 'm') {
			if (arrayr[i][j] == 'x') {
			printf(" - |");
			continue;
			}
			}

			printf(" %c |", arrayr[i][j]);
		}
		printf("\n");
		printf("   +---+");
		for (cnt = 0; cnt < columns - 1; cnt++) {
			printf("---+");
		}
		printf("\n");

	}
	for (cnt = 1; cnt < columns + 1; cnt++) {
		if (cnt == 1) {
			printf("     %d", cnt);
		}
		else printf("  %2d", cnt);
	}
	printf("\n");
	/////////////////////////////////////////////////////////printing chart thingy and real sizes and all that. should delete when done
	/*

	printf("\n now printing the real size\n");


	printf("   +---+");
	for (cnt = 0; cnt < rows + 1; cnt++) {
	printf("---+");
	}
	printf("\n");


	for (i = 0; i < rows + 2; i++)
	{
	printf("%2d-|", i + 1);
	for (j = 0; j < columns + 2; j++)
	{
	printf(" %c |", arrayr[i][j]);
	}
	printf("\n");
	}



	printf("  +---+");
	for (cnt = 0; cnt < rows + 1; cnt++) {
	printf("---+");
	}
	*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("\n");
}


/* Checks the area around a tile for mines and returns the value of the number of mines in tile's area. */
char bomb_count(char **board, int pickrow, int pickcol, int ROW, int COL, int mine)
{
	char count = '0';


	if (board[pickrow - 1][pickcol] == 'x') count++;
	if (board[pickrow][pickcol - 1] == 'x') count++;
	if (board[pickrow + 1][pickcol] == 'x') count++;
	if (board[pickrow][pickcol + 1] == 'x') count++;
	if (board[pickrow + 1][pickcol + 1] == 'x') count++;
	if (board[pickrow - 1][pickcol - 1] == 'x') count++;
	if (board[pickrow + 1][pickcol - 1] == 'x') count++;
	if (board[pickrow - 1][pickcol + 1] == 'x') count++;
	board[pickrow][pickcol] = count;
	return count;
}
