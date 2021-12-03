#include "Board.h"

Board::Board() {
	spaces = 64;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 'O';
		}
	}
	board[3][3] = 'W';
	board[3][4] = 'B';
	board[4][3] = 'B';
	board[4][4] = 'W';
}

void Board::Print()const {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			cout << board[i][j] << " ";
		}
		cout << board[i][7] << "";
		cout << endl;
	}
}

int Board::GetPlayerCount(const char x) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == x)
				count++;
		}
	}
	return count;
}
char Board::GetIndex(const int i,const int j)const {
	if (i < 7 || i > 0 || j  < 7 || j > 0) {
		return board[i][j];
	}
	else return 0;
}

void Board::SetIndex(int i, int j, const char x) {
	if (i > 7 || i < 0 || j  > 7 || j < 0) {
		return;
	}
	board[i][j] = x;
}
void Board::AttemptedMove(int i, int j, char x) {
	CheckMove(i, j, x, -1, -1);
	CheckMove(i, j, x, 0, -1);
	CheckMove(i, j, x, 1, -1);
	CheckMove(i, j, x, 1, 0);
	CheckMove(i, j, x, 1, 1);
	CheckMove(i, j, x, 0, 1);
	CheckMove(i, j, x, -1, 1);
	CheckMove(i, j, x, -1, 0);
}



void Board::CheckMove(int i, int j,const char x,int addToI,int addToJ) {
	int iTemp = i;
	int jTemp = j;
	bool flag = false;
	if (GetIndex(i + addToI, j + addToJ) == x) {
		//cout << "Invalid move; the game awaits a valid move." << endl;
		return;
	}
	i = i + addToI;
	j = j + addToJ;
	char conquring;
	if (x == 'B') {
		conquring = 'W';
	}
	else conquring = 'B';
	while(GetIndex(i,j) != 'O' && i <= 7 && i >= 0 && j <= 7 && j >= 0){
		if (GetIndex(i, j) == x) {
			flag = true;
			break;
		}
		i = i + addToI;
		j = j + addToJ;
	}
	if (GetIndex(i, j) == conquring) return;
	if (flag){
		while (i != iTemp || j != jTemp){
			i = i - addToI;
			j = j - addToJ;
			SetIndex(i, j, x);
		}
		return;
	}
}