#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/atomic.h>
#include "Debug.h"
#include "TicTacToeGame.h"

#define KEYPAD1_BASE 41
#define KEYPAD2_BASE 27

#define SERVO_ELBOW 11
#define SERVO_SHOULDER 12
#define SERVO_BASE 13

TicTacToeGame game;
TicTacToeArm* arm;
Keypad* keypad_primary;
Keypad* keypad_secondary;
LiquidCrystal_I2C* lcd;

volatile uint32_t seed;
volatile int8_t nrot;

void random_seed();
ISR(WDT_vect);

void random_seed() {
  
	seed = 0;
	nrot = 32;

	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);
	_WD_CONTROL_REG = (1<<WDIE);
	sei();

	while (nrot > 0);

	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (0<<WDE);
	_WD_CONTROL_REG = (0<< WDIE);
	sei();
}
 
ISR(WDT_vect) {
	nrot--;
	seed = seed << 8;
	seed = seed ^ TCNT1L;
}

void setup() {
	random_seed();
	randomSeed(seed);
	Serial.begin(115200);
	lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
	arm = new TicTacToeArm(SERVO_BASE, SERVO_SHOULDER, SERVO_ELBOW);
	keypad_primary = new Keypad(KEYPAD1_BASE);
	keypad_secondary = new Keypad(KEYPAD2_BASE);
	game.setup(lcd, arm, keypad_primary, keypad_secondary);
}

void loop() {
	game.loop();
}

