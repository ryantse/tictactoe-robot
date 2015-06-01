#ifndef TICTACTOEWINNER_H
#define TICTACTOEWINNER_H

#include "TicTacToeCell.h"

namespace winType {
	enum winType {ROW, COLUMN, DIAGONAL, ANTIDIAGONAL, TIE, NONE};
}

struct TicTacToeWinner {
	winType::winType type;
	int position;
	TicTacToeCell::TicTacToeCell player;
};

#endif