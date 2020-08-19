//
// Created by Bucky Fellini on 3/3/20.
//
#include <VNH5019Helper.h>
#include <ConfigHelper.h>

// Pin assignments from ConfigHelper.h
#define _INA VNH5019_INA
#define _INB VNH5019_INB
#define _ENADIAG VNH5019_ENADIAG
#define _ENBDIAG VNH5019_ENBDIAG
#define _CS VNH5019_CS

// This is the same as the period register set for 20kHz
// from PWM_20khz.h
const int PWM_MAX = 749;

VNH5019Helper::VNH5019Helper() {
	pinMode(_INA, OUTPUT);
	pinMode(_INB, OUTPUT);
	pinMode(_ENADIAG, INPUT);
	pinMode(_ENBDIAG, INPUT);
	pinMode(_CS, INPUT);
}

//void VNH5019Helper::init() {
//	pinMode(_INA, OUTPUT);
//	pinMode(_INB, OUTPUT);
//	pinMode(_ENADIAG, INPUT);
//	pinMode(_ENBDIAG, INPUT);
//	pinMode(_CS, INPUT);
//}

void VNH5019Helper::setSpeed(int speed) {
	unsigned char reverse = speed < 0 ? 1 : 0;

	speed = abs(speed);
	speed = min(speed, PWM_MAX);

	TCC0->CCBUF[0].reg = speed;

	if (0 == speed) {
		digitalWrite(_INA, LOW);
		digitalWrite(_INB, LOW);
	}
	else if (reverse) {
		digitalWrite(_INA, LOW);
		digitalWrite(_INB, HIGH);
	}
	else {
		digitalWrite(_INA, HIGH);
		digitalWrite(_INB, LOW);
	}
}

void VNH5019Helper::setBrake(int brake) {
	brake = abs(brake);
	brake = min(brake, PWM_MAX);

	digitalWrite(_INA, LOW);
	digitalWrite(_INB, LOW);

	TCC0->CCBUF[0].reg = brake;
}

unsigned int VNH5019Helper::getCurrentMilliAmps() {
	return analogRead(_CS) * 22;
}

unsigned char VNH5019Helper::hasFault() {
	return !digitalRead(_ENADIAG);
}

void VNH5019Helper::stopIfFault() {
	if (hasFault()) {
		while(1) {
			printDebug("VNH5019 FAULT!!!!", VNH5019_DEBUG);
		}
	}
}