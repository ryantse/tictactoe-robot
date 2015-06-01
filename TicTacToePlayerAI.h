#ifndef TICTACTOEPLAYERAI_H
#define TICTACTOEPLAYERAI_H

#include "TicTacToePlayer.h"
#include "TicTacToeCell.h"
#include "Debug.h"

class TicTacToePlayerAI : public TicTacToePlayer {
	public:
		TicTacToePlayerAI(TicTacToeCell::TicTacToeCell team);
		int makeMove(TicTacToeBoard* board);

	private:
		int _randInt(int min, int max);
};

#endif