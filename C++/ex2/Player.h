#ifndef _PLAYER_
#define _PLAYER_
#include "Board.h"
enum Turn { False,True, pass };
class Player {
private:
	char type;
	int totalCount;
	Turn myTurn;
public:
	Player(const char type) { this->type = type; this->totalCount = 2; myTurn = True; }
	int GetCount()const { return totalCount; }
	void IncCount(Board a) { this->totalCount = a.GetPlayerCount(this->type); }
	char GetType()const { return type; }
	void SwitchTurn() { if (myTurn) myTurn = False; else myTurn = True; }
	void SwitchTurn(Turn a) { myTurn = a; }
	Player(const Player& a) { this->type = a.type; this->totalCount = a.totalCount; this->myTurn = a.myTurn; }
	Player() { this->type = 'O'; };
	Turn turnStat() { return myTurn; }
};









#endif