#ifndef TICTACTOEGAMEDATA_H
#define TICTACTOEGAMEDATA_H

#include <avr/eeprom.h>
#include "TicTacToeCell.h"

class TicTacToeGameData {
	public:
		TicTacToeGameData();
		void incrementPlayerScore(TicTacToeCell::TicTacToeCell player);
		int getPlayerScore(TicTacToeCell::TicTacToeCell player);
		void resetScores();

	private:
		void saveData();

		struct gameData {
			int scores[3];
		} data;
};

#endif