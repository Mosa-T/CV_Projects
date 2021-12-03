#ifndef _BOARD_
#define _BOARD_
#include <iostream>

using namespace std;

class Board {


private:
	int spaces;
	char board[8][8];
public:
	int SpaceLeft() { return spaces; }
	void SpaceDec() { spaces--; }
	Board();
	void Print()const;
	void AttemptedMove(int i, int j, char x);
	int GetPlayerCount(const char x);
	char GetIndex(int i, int j)const;
	void SetIndex(int i, int j,const char x);
	void CheckMove(int i, int j,const char x,int addToI,int addToJ);
	bool isFull() { if (SpaceLeft() == 0) return true; else return false; }
};











#endif