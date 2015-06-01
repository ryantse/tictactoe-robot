#ifndef TICTACTOEARM_H
#define TICTACTOEARM_H

#include <Arduino.h>
#include <Servo.h>
#include <math.h>
#include "Debug.h"

#ifndef DEFAULT_STEP_MS
#define DEFAULT_STEP_MS 25
#endif

#ifndef STEP_MAX
#define STEP_MAX 80
#endif

class TicTacToeArm {
	public:
		TicTacToeArm(int pin_base, int pin_shoulder, int pin_elbow);
		void home(unsigned long step_delay = DEFAULT_STEP_MS);
		void penUp();
		void penDown();
		void lineTo(float x, float y);

	private:
		void getAngleMap(float r, float a, float& b, float& s, float& e);
		void setServoMicroseconds(float b, float s, float e);

		float _toAngle(float x, float y);
		float _toRadius(float x, float y);

		Servo base, shoulder, elbow;
		float pen_X, pen_Y;
		int penState;
};

#endif
