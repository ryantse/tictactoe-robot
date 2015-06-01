#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

class Keypad {
	public:
		Keypad(int base_pin);
		char readKey();
		char scanKey();
		static const char keyNone = '\0';

	private:
		int base_pin;
		const static char keyMap[];
};

#endif