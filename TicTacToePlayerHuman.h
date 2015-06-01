#ifndef TICTACTOEPLAYERHUMAN_H
#define TICTACTOEPLAYERHUMAN_H

#include "TicTacToePlayer.h"
#include "TicTacToeCell.h"
#include "TicTacToeGame.h"
#include "Keypad.h"

class TicTacToePlayerHuman : public TicTacToePlayer {
	public:
		TicTacToePlayerHuman(TicTacToeCell::TicTacToeCell team);
		void attachKeypad(Keypad* keypad);
		int makeMove(TicTacToeBoard* board);

	private:
		int _toInt(char x);
		Keypad* keypad;
};

#endif