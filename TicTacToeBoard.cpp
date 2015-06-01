#include "TicTacToeBoard.h"

TicTacToeBoard::TicTacToeBoard() {
	this->reset();
}

TicTacToeBoard::TicTacToeBoard(const TicTacToeBoard& origin) {
	for(int i = 1; i <= 9; i++) {
		board[i-1] = origin.getPosition(i);
	}
}

void TicTacToeBoard::reset() {
	for(int i = 0; i < 9; i++) {
		board[i] = TicTacToeCell::EMPTY;
	}
}

TicTacToeWinner TicTacToeBoard::getWinner() {
	TicTacToeWinner winnerData;
	winnerData.type = winType::NONE;
	winnerData.position = 0;
	winnerData.player = TicTacToeCell::EMPTY;

	for(int row = 0; row < 3; row++) {
		if(this->board[row*3] != TicTacToeCell::EMPTY && this->board[row*3] == this->board[row*3 + 1] && this->board[row*3 + 1] == this->board[row*3 + 2]) {
			DEBUG << "Winner (type, position, player): (row, " << row << ", " << this->board[row*3] << ")";
			winnerData.type = winType::ROW;
			winnerData.position = row;
			winnerData.player = this->board[row*3];
			return winnerData;
		}
	}

	for(int column = 0; column < 3; column++) {
		if(this->board[column] != TicTacToeCell::EMPTY && this->board[column] == this->board[column+3] && this->board[column+3] == this->board[column+6]) {
			DEBUG << "Winner (type, position, player): (column, " << column << ", " << this->board[column] << ")";
			winnerData.type = winType::COLUMN;
			winnerData.position = column;
			winnerData.player = this->board[column];
			return winnerData;
		}
	}

	if(this->board[0] != TicTacToeCell::EMPTY && this->board[0] == this->board[4] && this->board[4] == this->board[8]) {
		DEBUG << "Winner (type, position, player): (diagonal, 0, " << this->board[0] << ")";
		winnerData.type = winType::DIAGONAL;
		winnerData.player = this->board[0];
		return winnerData;
	}

	if(this->board[2] != TicTacToeCell::EMPTY && this->board[2] == this->board[4] && this->board[4] == this->board[6]) {
		DEBUG << "Winner (type, position, player): (antidiagonal, 0, "<< this->board[2] << ")";
		winnerData.type = winType::ANTIDIAGONAL;
		winnerData.player = this->board[2];
		return winnerData;
	}

	if(this->isFull()) {
		DEBUG << "Winner (type, position, player): (tie, 0, 0)";
		winnerData.type = winType::TIE;
	}

	return winnerData;
}

bool TicTacToeBoard::move(int position, TicTacToeCell::TicTacToeCell player) {
	if(player == TicTacToeCell::EMPTY || this->board[position-1] != TicTacToeCell::EMPTY || position < 1 || position > 9) {
		return false;
	}

	this->board[position-1] = player;

	DEBUG << "Board State:";
	for(int i = 0; i < 3; i++) {
		DEBUG << this->board[i*3] << " " << this->board[i*3 + 1] << " " << this->board[i*3 + 2];
	}
	return true;
}

TicTacToeCell::TicTacToeCell TicTacToeBoard::getPosition(int position) const {
	return this->board[position-1];
}

bool TicTacToeBoard::isFull() {
	for(int i = 0; i < 9; i++) {
		if(this->board[i] == TicTacToeCell::EMPTY) {
			return false;
		}
	}
	return true;
}