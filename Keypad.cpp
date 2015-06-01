#include "Keypad.h"

const char Keypad::keyMap[] PROGMEM = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};

Keypad::Keypad(int base_pin) {
	int currentPin = base_pin;
	for(int i = 0; i < 3; i++) {
		pinMode(currentPin, INPUT_PULLUP);
		currentPin += 2;
	}
	for(int i = 0; i < 4; i++) {
		pinMode(currentPin, OUTPUT);
		digitalWrite(currentPin, HIGH);
		currentPin += 2;
	}
	this->base_pin = base_pin;
}

char Keypad::readKey() {
	char key = this->scanKey();
	if (!key || key != this->scanKey()) {
		return this->keyNone;
	} else {
		while(this->scanKey()) {}
		return key;
	}
}

char Keypad::scanKey() {
	char key = this->keyNone;

	for (int row=0; (row<4) && (key == this->keyNone); row++) {
		digitalWrite((this->base_pin + 12)-row*2, LOW);
		for (int col=0; col<3; col++) {
			if (digitalRead((this->base_pin + 4)-col*2) == LOW ) {
				key = pgm_read_byte_near(this->keyMap + (row * 3 + col));
				break;
			}
		}
		digitalWrite((this->base_pin + 12)-row*2, HIGH);
	}

	return key;
}