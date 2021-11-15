#ifndef _GAME_
#define _GAME_

#include "Player.h"
#include "Board.h"
#include <string>
#include <stdlib.h>
class Game {
private:
	Player playerB;
	Player playerW;
	Board board;
public:
	Game() :playerB('B'), playerW('W') { playerW.SwitchTurn(False); }
	void Innit();
	void ConcludeGame();
	Player* turnSwap(Player *pointer);
	void checkBoard();
};












#endif