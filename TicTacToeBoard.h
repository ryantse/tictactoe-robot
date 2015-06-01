#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include <Arduino.h>
#include "TicTacToeCell.h"
#include "TicTacToeWinner.h"
#include "Debug.h"

class TicTacToeBoard {
	public:
		TicTacToeBoard();
		TicTacToeBoard(const TicTacToeBoard& origin);

		TicTacToeCell::TicTacToeCell getPosition(int position) const;
		bool move(int position, TicTacToeCell::TicTacToeCell player);

		TicTacToeWinner getWinner();
		bool hasWinner();
		bool hasTie();

		bool isFull();

		void reset();

	private:
		TicTacToeCell::TicTacToeCell board[9];
};

#endif