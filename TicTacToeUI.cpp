#include "TicTacToeUI.h"

TicTacToeUI::TicTacToeUI() {

}

void TicTacToeUI::attachArm(TicTacToeArm* arm) {
	this->arm = arm;
}

void TicTacToeUI::drawBoard(float x, float y, float width, float height) {
	float dx, dy;
	dx = width / 3;
	dy = height / 3;

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	DEBUG << "Board X: " << x << " Board Y: " << y << " Board Width: " << width << " Board Height: " << height << " (dx= " << dx << ", dy= " << dy << ")";

	this->arm->penUp();

	for(int i = 2; i > 0; i--) {
		this->arm->lineTo(x + (dx*i), y);
		this->arm->penDown();
		this->arm->lineTo(x + (dx*i), y + height);
		this->arm->penUp();
	}

	for(int i = 1; i < 3; i++) {
		this->arm->lineTo(x + width, y + (dy*i));
		this->arm->penDown();
		this->arm->lineTo(x, y + (dy*i));
		this->arm->penUp();
	}

	this->arm->home();
}

void TicTacToeUI::drawO(int position) {
	int row = (position-1)/3;
	int column = (position-1)%3;

	DEBUG << "Draw O Position: " << position;

	this->drawO(this->x + this->width - ((column+1)*(this->width/3)) + ((this->height/3)/2), this->y + (this->height/3)*row + ((this->height/3)/2), ((this->width/3)*0.75)/2);
}

void TicTacToeUI::drawX(int position) {
	int row = (position-1)/3;
	int column = (position-1)%3;

	DEBUG << "Draw X Position: " << position;

	this->drawX(this->x + this->width - ((column+1)*(this->width/3)) + ((this->height/3)/2), this->y + (this->height/3)*row + ((this->height/3)/2), ((this->width/3)*0.75)/2);
}

void TicTacToeUI::drawX(float x, float y, float radius) {
	DEBUG << "Draw X (x, y, radius): (" << x << ", " << y << ", " << radius << ")";

	this->arm->penUp();

	this->arm->lineTo(x+radius, y-radius);
	this->arm->penDown();
	this->arm->lineTo(x-radius, y+radius);

	this->arm->penUp();
	this->arm->lineTo(x+radius, y+radius);
	this->arm->penDown();
	this->arm->lineTo(x-radius, y-radius);

	this->arm->penUp();
	this->arm->home();
}

void TicTacToeUI::drawO(float x, float y, float radius) {
	DEBUG << "Draw O (x, y, radius): (" << x << ", " << y << ", " << radius << ")";

	static const int sides = 8;
	this->arm->penUp();

	for(int i = 0; i <= sides; i++) {
		this->arm->lineTo(radius * cos(2*PI*i/sides) + x, radius * sin(2*PI*i/sides) + y);
		arm->penDown();
	}

	this->arm->penUp();
	this->arm->home();
}

void TicTacToeUI::drawWinner(TicTacToeWinner winnerData) {
	switch(winnerData.type) {
		case winType::ROW:
			this->arm->penUp();
			this->arm->lineTo(this->x + this->width, this->y + (this->height/3)*winnerData.position + ((this->height/3)/2));
			this->arm->penDown();
			this->arm->lineTo(this->x, this->y + (this->height/3)*winnerData.position + ((this->height/3)/2));
			this->arm->penUp();
			this->arm->home();
			break;

		case winType::COLUMN:
			this->arm->penUp();
			this->arm->lineTo(this->x + (this->width/3)*(2-winnerData.position) + ((this->width/3)/2), this->y);
			this->arm->penDown();
			this->arm->lineTo(this->x + (this->width/3)*(2-winnerData.position) + ((this->width/3)/2), this->y + this->height);
			this->arm->penUp();
			this->arm->home();
			break;

		case winType::DIAGONAL:
			this->arm->penUp();
			this->arm->lineTo(this->x + this->width, this->y);
			this->arm->penDown();
			this->arm->lineTo(this->x, this->y + this->height);
			this->arm->penUp();
			this->arm->home();
			break;

		case winType::ANTIDIAGONAL:
			this->arm->penUp();
			this->arm->lineTo(this->x + this->width, this->y + this->height);
			this->arm->penDown();
			this->arm->lineTo(this->x, this->y);
			this->arm->penUp();
			this->arm->home();
			break;
	}
}