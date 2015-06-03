#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame() {
	this->board = new TicTacToeBoard();
}

void TicTacToeGame::setup(LiquidCrystal_I2C* lcd, TicTacToeArm* arm, Keypad* keypad_primary, Keypad* keypad_secondary) {
	byte refreshScreenChar[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00001};
	
	this->lcd = lcd;
	this->lcd->begin(20,4);
	this->lcd->createChar(0, refreshScreenChar);

	this->arm = arm;
	this->arm->home(0);

	this->ui.attachArm(this->arm);
	this->keypad[0] = keypad_primary;
	this->keypad[1] = keypad_secondary;
}

void TicTacToeGame::resetGame() {
	delete this->board;
	this->board = new TicTacToeBoard();

	for(int i = 0; i < 2; i++) {
		delete this->player[i];
	}

	this->lastPlayer = -1;
	this->arm->home();
}

void TicTacToeGame::resetScores() {
	for(int i = 0; i < 3; i++) {
		this->scores[i] = 0;
	}
}

void TicTacToeGame::refreshScreen() {
	if(this->lcd != NULL) {
		DEBUG << "Refreshing screen.";
		this->lcd->setCursor(19,3);
		if(random(0,1000) > 500) {
			this->lcd->write(byte(0));
		} else {
			this->lcd->print(F(" "));
		}
	}
}

void TicTacToeGame::loop() {
	char current_key;

	switch(this->state) {
		case STATE_GETPLAYERS:
			DEBUG << "Changing State: STATE_GETPLAYERS";

			this->lcd->clear();
			this->lcd->setCursor(0, 0);
			this->lcd->print(F("Tic-Tac-Toe Robot v1"));
			this->lcd->setCursor(0, 1);
			this->lcd->print(F("Score X:"));
			this->lcd->print(this->scores[TicTacToeCell::X]);
			this->lcd->print(F(" O:"));
			this->lcd->print(this->scores[TicTacToeCell::O]);
			this->lcd->print(F(" T:"));
			this->lcd->print(this->scores[TicTacToeCell::EMPTY]);
			this->lcd->setCursor(0, 2);
			this->lcd->print(F("[1] 1P [2] 2P [0] AI"));
			this->lcd->setCursor(0, 3);
			this->lcd->print(F("[*] Advanced Menu"));

			DEBUG << "Reset game.";
			this->resetGame();

			DEBUG << "Scores: Tie[" << this->scores[TicTacToeCell::EMPTY] << "] X[" << this->scores[TicTacToeCell::X] << "] O[" << this->scores[TicTacToeCell::O] << "]";
			while((current_key = this->keypad[0]->readKey()) == Keypad::keyNone) {
				this->refreshScreen();
				continue;
			}

			DEBUG << "Received Key: " << current_key;

			if(current_key == '*') {
				this->interruptMenu(this->keypad[0]);
				return;
			}

			switch(current_key) {
				case '1':
					this->type = TYPE_SINGLEPLAYER;

					this->player[0] = new TicTacToePlayerHuman(TicTacToeCell::X);
					((TicTacToePlayerHuman*)this->player[0])->attachKeypad(this->keypad[0]);

					this->player[1] = new TicTacToePlayerAI(TicTacToeCell::O);
					break;

				case '2':
					this->type = TYPE_TWOPLAYER;

					this->player[0] = new TicTacToePlayerHuman(TicTacToeCell::X);
					((TicTacToePlayerHuman*)this->player[0])->attachKeypad(this->keypad[0]);

					this->player[1] = new TicTacToePlayerHuman(TicTacToeCell::O);
					((TicTacToePlayerHuman*)this->player[1])->attachKeypad(this->keypad[1]);
					break;

				case '0':
					this->type = TYPE_AI;

					this->player[0] = new TicTacToePlayerAI(TicTacToeCell::X);
					this->player[1] = new TicTacToePlayerAI(TicTacToeCell::O);
					break;

				default:
					return;
					break;
			}
			this->state = STATE_PLAYING;
			this->player[0]->setGame(this);
			this->player[1]->setGame(this);

			DEBUG << "Drawing board.";
			this->lcd->clear();
			this->lcd->setCursor(3, 0);
			this->lcd->print(F("Please Wait..."));
			this->lcd->setCursor(1, 2);
			this->lcd->print(F("Busy Drawing Board"));

			this->ui.drawBoard();
			break;

		case STATE_PLAYING:
			DEBUG << "Changing State: STATE_PLAYING";
			this->lastPlayer = (this->lastPlayer == -1 || this->lastPlayer == 1) ? 0 : 1;

			this->lcd->clear();
			this->lcd->setCursor(0, 0);
			this->lcd->print(F("Player "));
			this->lcd->print((this->lastPlayer + 1));
			this->lcd->print(F("'s Turn:"));
			this->lcd->setCursor(0, 1);
			this->lcd->print(F("[1-9] Position"));
			this->lcd->setCursor(0, 2);
			this->lcd->print(F("[*] Advanced Menu"));			

			DEBUG << "Last Player State: " << this->lastPlayer;
			int playerMove = this->player[this->lastPlayer]->makeMove(this->board);
			DEBUG << "Received Player " << (this->lastPlayer+1) << " Move: " << playerMove;
			if(this->board->move(playerMove, this->player[this->lastPlayer]->getTeam())) {
				this->lcd->setCursor(0, 2);
				this->lcd->print(F("Chose position "));
				this->lcd->print(playerMove);
				this->lcd->print(F("."));
				this->lcd->setCursor(0, 3);
				if(this->player[this->lastPlayer]->getTeam() == TicTacToeCell::X) {
					this->lcd->print(F("Drawing X."));
					this->ui.drawX(playerMove);
				} else if(this->player[this->lastPlayer]->getTeam() == TicTacToeCell::O) {
					this->lcd->print(F("Drawing O."));
					this->ui.drawO(playerMove);
				}

				TicTacToeWinner winnerData;
				if((winnerData = this->board->getWinner()).type != winType::NONE) {
					this->lcd->clear();
					this->lcd->setCursor(5, 0);
					this->lcd->print(F("Game over!"));
					for(int i = 0; i < 3; i++) {
						this->lcd->backlight();
						delay(250);
						this->lcd->noBacklight();
						delay(250);
					}
					this->lcd->backlight();

					if(winnerData.type == winType::TIE) {
						this->lcd->setCursor(5, 2);
						this->lcd->print(F("Tied Game."));
					} else {
						this->lcd->setCursor(4, 2);
						this->lcd->print(F("Player "));
						this->lcd->print((winnerData.player == TicTacToeCell::X) ? F("X") : F("O"));
						this->lcd->print(F(" Won"));
					}

					this->ui.drawWinner(winnerData);
					this->scores[winnerData.player]++;
					this->state = STATE_GETPLAYERS;
					delay(3000);
				}
			} else {
				this->lastPlayer = (this->lastPlayer == 1) ? 0 : 1;
			}
			break;
	}
}

void TicTacToeGame::interruptMenu(Keypad* keypad) {
	INTERRUPT_BEGIN:

	char current_key;

	this->lcd->clear();
	this->lcd->setCursor(0, 0);
	this->lcd->print(F("Interrupt Menu"));
	this->lcd->setCursor(0, 1);
	this->lcd->print(F("[#] Main Menu"));
	this->lcd->setCursor(0, 2);
	this->lcd->print(F("[1] Reset Scores"));
	this->lcd->setCursor(0, 3);
	this->lcd->print(F("[*] Cancel"));

	while((current_key = keypad->readKey()) == Keypad::keyNone) {
		this->refreshScreen();
		continue;
	}
	DEBUG << "Received Key: " << current_key;
	switch(current_key) {
		case '#':
			this->state = STATE_GETPLAYERS;
			break;

		case '1':
			this->resetScores();
			break;

		case '*':
			return;
			break;

		default:
			goto INTERRUPT_BEGIN;
			break;
	}
	return;
}