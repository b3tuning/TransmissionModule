//
// Created by Bucky Fellini on 2/28/20.
//

#ifndef TRANSCONTROLLER_CONFIGHELPER_H
#define TRANSCONTROLLER_CONFIGHELPER_H

#include <Arduino.h>
#include <FlashHelper.h>

/**
 * Override to print all debug messages
 */
#define MAIN_DEBUG 0

#define CANBUS_DEBUG 0
#define FLASH_DEBUG 0
#define PID_DEBUG 0
#define EMS22A_DEBUG 0
#define VNH5019_DEBUG 0

#define DBL_TAP_PTR ((volatile uint32_t *)(HSRAM_ADDR + HSRAM_SIZE -4))
#define DBL_TAP_MAGIC 0xF01669EF
#define DBL_TAP_MAGIC_QUICK_BOOT 0xF0266EF

#define CAN0_INT 3
#define CAN_CS 10

#define EMS_CS 6
#define EMS_CLK 4
#define EMS_DATA 5

#define VNH5019_INA A2
#define VNH5019_INB A4
#define VNH5019_ENADIAG A1
#define VNH5019_ENBDIAG A5
#define VNH5019_CS A3

#define FILE_NAME "config.ini"

#define j_CANBUS "canBus"
#define j_ADDRTX "addrTX"
#define j_BOOTRX "bootRX"
#define j_BOOTTX "bootTX"
#define j_INTVLTX "intvlTX"
#define j_MASK0 "mask0"
#define j_MASK1 "mask1"
#define j_FILTER0_0 "filter0_0"
#define j_FILTER0_1 "filter0_1"
#define j_FILTER1_0 "filter1_0"
#define j_FILTER1_1 "filter1_1"
#define j_FILTER1_2 "filter1_2"
#define j_FILTER1_3 "filter1_3"

#define j_EMS22A "ems22a"
#define j_enc_MAX "encMAX"
#define j_enc_MIN "encMIN"

#define j_VNH5019 "vnh5019"
#define j_MAX_CURRENT "maxCurrent"

#define j_PID "pid"
#define j_AGG_KD "aggKd"
#define j_AGG_KI "aggKi"
#define j_AGG_KP "aggKp"
#define j_CONS_KD "consKd"
#define j_CONS_KI "consKi"
#define j_CONS_KP "consKp"

#define REBOOT_KEY 0xB007AB1E
#define REBOOT_LOADER_KEY 0xDEC0DED

inline void printDebug(const char* s, bool debug) {
	if(MAIN_DEBUG || debug) {
		Serial.println(s);
	}
}

struct CAN_BUS_CFG {
	unsigned long addrTX;
	unsigned long bootRX;
	unsigned long bootTX;
	uint8_t       intvlTX;
	unsigned long mask0;
	unsigned long filter0_0;
	unsigned long filter0_1;
	unsigned long mask1;
	unsigned long filter1_0;
	unsigned long filter1_1;
	unsigned long filter1_2;
	unsigned long filter1_3;

};

struct EMS22A_CFG {

};

struct CONFIG {
	CAN_BUS_CFG canBus;
};

enum class SHIFTER {
	PARK    = 1,
	REVERSE = 2,
	NEUTRAL = 3,
	DRIVE   = 4,
	DOWN    = 5,
	MANUAL  = 6,
	UP      = 7
};

class ConfigHelper {
public:
	ConfigHelper();

	void pinSetup();

	static void popConfig(FlashHelper& flashHelper, CONFIG& c);

	static void reconfigure(FlashHelper& flashHelper);

	void reboot();

	void rebootBootLoader();

};

#endif //TRANSCONTROLLER_CONFIGHELPER_H
