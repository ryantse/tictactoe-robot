#include "TicTacToePlayer.h"

void TicTacToePlayer::setGame(TicTacToeGame* game) {
	this->game = game;
}

void TicTacToePlayer::setTeam(TicTacToeCell::TicTacToeCell team) {
	this->team = team;
}

TicTacToeCell::TicTacToeCell TicTacToePlayer::getTeam() const {
	return this->team;
}