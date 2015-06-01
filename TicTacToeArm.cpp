#include "TicTacToeArm.h"

TicTacToeArm::TicTacToeArm(int pin_base, int pin_shoulder, int pin_elbow) {
	this->base.attach(pin_base);
	this->shoulder.attach(pin_shoulder);
	this->elbow.attach(pin_elbow);
}

void TicTacToeArm::home(unsigned long step_delay) {
	float tb, ts, te;
	float cb, cs, ce;
	float db, ds, de;

	this->penState = 1;
	this->getAngleMap(80, 90, tb, ts, te);

	cb = this->base.readMicroseconds();
	cs = this->shoulder.readMicroseconds();
	ce = this->elbow.readMicroseconds();

	db = (tb - cb) / STEP_MAX;
	ds = (ts - cs) / STEP_MAX;
	de = (te - ce) / STEP_MAX;

	if(db != 0 || ds !=0 || de !=0) {
		for(int i = 0; i < STEP_MAX; i++) {
			cb += db;
			cs += ds;
			ce += de;
			this->setServoMicroseconds(cb, cs, ce);
			delay(step_delay);
		}
	}

	this->pen_X = 0;
	this->pen_Y = 80;
}

void TicTacToeArm::penUp() {
	if(this->penState == 0) {
		float cb, cs, ce;
		float tb, ts, te;
		float db, ds, de;

		this->penState = 1;
		this->getAngleMap(this->_toRadius(this->pen_X, this->pen_Y), this->_toAngle(this->pen_X, this->pen_Y), tb, ts, te);
		
		cb = this->base.readMicroseconds();
		cs = this->shoulder.readMicroseconds();
		ce = this->elbow.readMicroseconds();

		db = (tb - cb) / STEP_MAX;
		ds = (ts - cs) / STEP_MAX;
		de = (te - ce) / STEP_MAX;

		if(db != 0 || ds !=0 || de !=0) {
			for(int i = 0; i < STEP_MAX; i++) {
				cb += db;
				cs += ds;
				ce += de;
				this->setServoMicroseconds(cb, cs, ce);
				delay(DEFAULT_STEP_MS);
			}
		}
	}
}

void TicTacToeArm::penDown() {
	if(this->penState == 1) {
		float cb, cs, ce;
		float tb, ts, te;
		float db, ds, de;

		this->penState = 0;
		this->getAngleMap(this->_toRadius(this->pen_X, this->pen_Y), this->_toAngle(this->pen_X, this->pen_Y), tb, ts, te);
		
		cb = this->base.readMicroseconds();
		cs = this->shoulder.readMicroseconds();
		ce = this->elbow.readMicroseconds();

		db = (tb - cb) / STEP_MAX;
		ds = (ts - cs) / STEP_MAX;
		de = (te - ce) / STEP_MAX;

		if(db != 0 || ds !=0 || de !=0) {
			for(int i = 0; i < STEP_MAX; i++) {
				cb += db;
				cs += ds;
				ce += de;
				this->setServoMicroseconds(cb, cs, ce);
				delay(DEFAULT_STEP_MS);
			}
		}
	}
}

void TicTacToeArm::lineTo(float x, float y) {
	float dx, dy;
	float cx, cy;
	float tb, ts, te;

	cx = this->pen_X;
	cy = this->pen_Y;

	DEBUG << "Current (x, y): (" << cx << ", " << cy << ")";
	DEBUG << "Target (x, y): (" << x << ", " << y << ")";

	dx = (x - cx) / STEP_MAX;
	dy = (y - cy) / STEP_MAX;

	DEBUG << "Step (dx, dy): (" << dx << ", " << dy << ")";

	if(dx != 0 || dy != 0) {
		for (int i = 0; i < STEP_MAX; i++ ) {
			cx += dx;
			cy += dy;
			this->getAngleMap(this->_toRadius(cx, cy), this->_toAngle(cx, cy), tb, ts, te);
			this->setServoMicroseconds(tb, ts, te);
			delay(DEFAULT_STEP_MS);
		}

		this->pen_X = x;
		this->pen_Y = y;
	}
}

void TicTacToeArm::getAngleMap(float r, float a, float& b, float& s, float& e) {
	if(this->penState == 1) {
		b = map(a, 60.0, 120.0, 1087, 1697);
		s = map(r, 88.0, 158.0, 1786, 2036);
		e = map(r, 88.0, 158.0, 1225, 1675);
	} else {
		b = map(a, 60.0, 120.0, 1087, 1697);
		s = map(r, 88.0, 158.0, 1936, 2156);
		e = map(r, 88.0, 158.0, 1105, 1655);
	}
}

void TicTacToeArm::setServoMicroseconds(float b, float s, float e) {
	DEBUG << "Servo Microseconds (b, s, e): (" << b << ", " << s << ", " << e << ")";
	this->base.writeMicroseconds(b);
	this->shoulder.writeMicroseconds(s);
	this->elbow.writeMicroseconds(e);
}

float TicTacToeArm::_toAngle(float x, float y) {
	return (atan2(y, x)*180.0)/PI;
}

float TicTacToeArm::_toRadius(float x, float y) {
	return sqrt(x*x + y*y);
}