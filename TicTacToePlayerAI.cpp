#include "TicTacToePlayerAI.h"

TicTacToePlayerAI::TicTacToePlayerAI(TicTacToeCell::TicTacToeCell team) {
	this->setTeam(team);
}

int TicTacToePlayerAI::makeMove(TicTacToeBoard* board) {
	TicTacToeBoard* currentBoard;
	TicTacToeWinner winnerData;
	TicTacToeCell::TicTacToeCell opponent = (this->getTeam() == TicTacToeCell::X) ? TicTacToeCell::O : TicTacToeCell::X;

	for(int i = 1; i <= 9; i++) {
		currentBoard = new TicTacToeBoard(*board);
		currentBoard->move(i, this->getTeam());
		if((winnerData = currentBoard->getWinner()).player == this->getTeam()) {
			DEBUG << "Found winning move.";
			DEBUG << "Chosen Location: " << i;
			delete currentBoard;
			return i;
		}
		delete currentBoard;
	}

	for(int i = 1; i <= 9; i++) {
		currentBoard = new TicTacToeBoard(*board);
		currentBoard->move(i, opponent);
		if((winnerData = currentBoard->getWinner()).player == opponent) {
			DEBUG << "Found opponent's winning position, blocking.";
			DEBUG << "Chosen Location: " << i;
			delete currentBoard;
			return i;
		}
		delete currentBoard;
	}

	int random_position;
	while(true) {
		random_position = this->_randInt(1, 9);
		if(board->getPosition(random_position) == TicTacToeCell::EMPTY) {
			DEBUG << "Chosen Location: " << random_position;
			return random_position;
		}
	}
}

int TicTacToePlayerAI::_randInt(int min, int max) {
	return random(min, max+1);
}