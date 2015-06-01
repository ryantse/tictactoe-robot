#ifndef TICTACTOEPLAYER_H
#define TICTACTOEPLAYER_H

#include "TicTacToeClasses.h"
#include "TicTacToeBoard.h"
#include "TicTacToeCell.h"

class TicTacToePlayer {
	public:
		virtual int makeMove(TicTacToeBoard* board) = 0;
		void setGame(TicTacToeGame* game);
		TicTacToeCell::TicTacToeCell getTeam() const;
		void setTeam(TicTacToeCell::TicTacToeCell team);

	protected:
		TicTacToeGame* game;

	private:
		TicTacToeCell::TicTacToeCell team;
};

#endif