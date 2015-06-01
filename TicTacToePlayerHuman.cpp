#include "TicTacToePlayerHuman.h"

TicTacToePlayerHuman::TicTacToePlayerHuman(TicTacToeCell::TicTacToeCell team) {
	this->setTeam(team);
}

void TicTacToePlayerHuman::attachKeypad(Keypad* keypad) {
	this->keypad = keypad;
}

int TicTacToePlayerHuman::makeMove(TicTacToeBoard* board) {
	char current_key;
	while((current_key = this->keypad->readKey()) == Keypad::keyNone) {
		this->game->refreshScreen();
		continue;
	}
	DEBUG << "Received Key: " << current_key;
	if(current_key == '*') {
		this->game->interruptMenu(this->keypad);
		return -1;
	} else if(current_key == '0' || current_key == '#' || board->getPosition(_toInt(current_key)) != TicTacToeCell::EMPTY) {
		return 0;
	}
	return _toInt(current_key);
}

int TicTacToePlayerHuman::_toInt(char x) {
	return x - '0';
}