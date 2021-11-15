#include "Game.h"
#include "Board.h"


void Game::ConcludeGame() { 
	int whoWins = board.GetPlayerCount('B') - board.GetPlayerCount('W'); // Positive if B wins negative if W wins, zero if tie.
	if (whoWins > 0) {
		cout << "B wins the game." << endl;
		exit(1);
	}
	if (whoWins < 0) {
		cout << "W wins the game." << endl;
		exit(1);
	}
	if (whoWins == 0) {
		cout << "The game ends in a tie." << endl;
		exit(1);
	}
}



Player *Game::turnSwap(Player* pointer) {
	if (playerW.turnStat() == pass && playerB.turnStat() == pass) {
		pointer = NULL;
		ConcludeGame();
	}
	if ((*pointer).GetType() == 'B') {
		pointer = &playerW;
		(*pointer).SwitchTurn(True);
		return pointer;
	}
	else {
		pointer = &playerB;
		(*pointer).SwitchTurn(True);
		return pointer;
	}
}


void Game::checkBoard() {
	if (board.SpaceLeft() > 0)
		board.SpaceDec();
	if (board.isFull()) {
		ConcludeGame();
	}
}

void Game::Innit() {
	Player *playingPlayer = &playerB;
	string str;
	int indexI;
	int indexJ;
	while (true) {
		board.Print();
		if (playingPlayer->GetCount() == 0)
			ConcludeGame();
		cout << (*playingPlayer).GetType() << ":" << endl;
		cin >> str;
		if (str == "PASS") {
			(*playingPlayer).SwitchTurn(pass);
			playingPlayer = turnSwap(playingPlayer);
			continue;
		}
		if (str == "QUIT") {
			cout << (*playingPlayer).GetType() << ": QUIT" << endl;
			if ((*playingPlayer).GetType() == 'B') {
				cout << "W wins the game." << endl;
				playingPlayer = NULL;
				exit(1);
			}
			else {
				cout << "B wins the game." << endl;
				playingPlayer = NULL;
				exit(1);
			}
		}
		if (str.length() != 2) {
			cout << "Invalid move; the game awaits a valid move." << endl;
			continue;
		}
		indexJ = str.at(0) - 'A';
		indexI = (str.at(1) - '0' - 1);
		if (indexJ < 8 && indexJ >= 0 && indexI < 8 && indexI >= 0 && board.GetIndex(indexI, indexJ) == 'O') {
			board.AttemptedMove(indexI, indexJ, (*playingPlayer).GetType());
				if (board.GetIndex(indexI,indexJ) != 'O') {
					checkBoard();
					playingPlayer->IncCount(board); //Count of the player who made a move
					(*playingPlayer).SwitchTurn(False);
					playingPlayer = turnSwap(playingPlayer);
					playingPlayer->IncCount(board); //Count of the player whose turn is after a move
				}
				else cout << "Invalid move; the game awaits a valid move." << endl;
			}
		else cout << "Invalid move; the game awaits a valid move." << endl;
	}
}


