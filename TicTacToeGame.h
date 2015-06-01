#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Debug.h"
#include "Keypad.h"
#include "TicTacToeClasses.h"
#include "TicTacToeArm.h"
#include "TicTacToeBoard.h"
#include "TicTacToeCell.h"
#include "TicTacToeUI.h"
#include "TicTacToePlayer.h"
#include "TicTacToePlayerAI.h"
#include "TicTacToePlayerHuman.h"

class TicTacToeGame {
	public:
		TicTacToeGame();
		void setup(LiquidCrystal_I2C* lcd, TicTacToeArm* arm, Keypad* keypad_primary, Keypad* keypad_secondary);
		void loop();
		void interruptMenu(Keypad* keypad);
		void refreshScreen();

	private:
		void resetGame();
		void resetScores();

		enum gameState { STATE_GETPLAYERS, STATE_PLAYING, STATE_INTERRUPTMENU };
		enum gameType { TYPE_UNSET, TYPE_SINGLEPLAYER, TYPE_TWOPLAYER, TYPE_AI };

		gameState state = STATE_GETPLAYERS;
		gameType type = TYPE_UNSET;

		TicTacToeBoard* board;
		Keypad* keypad[2];

		int scores[3] = {0,0,0};
		int lastPlayer = -1;

		TicTacToeUI ui;
		TicTacToeArm* arm;
		TicTacToePlayer* player[2];

		LiquidCrystal_I2C* lcd;
};

#endif