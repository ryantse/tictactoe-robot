#include "TicTacToeGameData.h"

TicTacToeGameData::TicTacToeGameData() {
	eeprom_read_block((void*)&this->data, (void*)0, sizeof(this->data));
}

void TicTacToeGameData::incrementPlayerScore(TicTacToeCell::TicTacToeCell player) {
	this->data.scores[player]++;
	this->saveData();
}

int TicTacToeGameData::getPlayerScore(TicTacToeCell::TicTacToeCell player) {
	return this->data.scores[player];
}

void TicTacToeGameData::resetScores() {
	for(int i = 0; i < 3; i++) {
		this->data.scores[i] = 0;
	}
	this->saveData();
}

void TicTacToeGameData::saveData() {
	eeprom_write_block((const void*)&this->data, (void*)0, sizeof(this->data));
}