#ifndef TICTACTOEUI_H
#define TICTACTOEUI_H

#include <Servo.h>
#include <math.h>
#include "Debug.h"
#include "TicTacToeArm.h"
#include "TicTacToeWinner.h"

class TicTacToeUI {
	public:
		TicTacToeUI();
		void attachArm(TicTacToeArm* arm);

		void drawBoard(float x = -30, float y = 100, float width = 60, float height = 60);
		void drawO(int position);
		void drawX(int position);
		void drawO(float x, float y, float radius);
		void drawX(float x, float y, float radius);
		void drawWinner(TicTacToeWinner winnerData);

		float getX() { return this->x; };
		float getY() { return this->y; };
		float getWidth() { return this->width; };
		float getHeight() { return this->height; };

	private:
		TicTacToeArm* arm;
		float x, y, width, height;
};

#endif