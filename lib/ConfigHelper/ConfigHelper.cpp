//
// Created by Bucky Fellini on 2/28/20.
//

#include <ConfigHelper.h>
#include <ArduinoJson.h>

const char* FILE_OPEN_SUCCESS   = "Opened file successfully";
const char* FILE_OPEN_FAILURE   = "ERROR failed to open file";
const char* FILE_CREATE_FAILURE = "ERROR failed to create file";
const char* FILE_READ_FAILURE   = "ERROR failed to read file";
const char* FILE_WRITE_FAILURE  = "ERROR failed to write file";

const size_t capacity = JSON_ARRAY_SIZE(1);

ConfigHelper::ConfigHelper() {}

void ConfigHelper::pinSetup() {

}

void ConfigHelper::popConfig(FlashHelper& flashHelper, CONFIG& c) {
	File file = FlashHelper::openFile(FILE_NAME);

	StaticJsonDocument<capacity> doc;

	DeserializationError error = deserializeJson(doc, file);
	if(error) {
		printDebug(FILE_READ_FAILURE, FLASH_DEBUG);
	}

	c.canBus.addrTX    = doc[j_CANBUS][j_ADDRTX];
	c.canBus.bootRX    = doc[j_CANBUS][j_BOOTRX];
	c.canBus.intvlTX   = doc[j_CANBUS][j_INTVLTX];
	c.canBus.mask0     = doc[j_CANBUS][j_MASK0];
	c.canBus.filter0_0 = doc[j_CANBUS][j_FILTER0_0];
	c.canBus.filter0_1 = doc[j_CANBUS][j_FILTER0_1];
	c.canBus.mask1     = doc[j_CANBUS][j_MASK1];
	c.canBus.filter1_0 = doc[j_CANBUS][j_FILTER1_0];
	c.canBus.filter1_1 = doc[j_CANBUS][j_FILTER1_1];
	c.canBus.filter1_2 = doc[j_CANBUS][j_FILTER1_2];
	c.canBus.filter1_3 = doc[j_CANBUS][j_FILTER1_3];

	file.close();
}

void ConfigHelper::reconfigure(FlashHelper& flashHelper) {
	FlashHelper::removeFile(FILE_NAME);

	File dataFile = FlashHelper::openFile(FILE_NAME, FILE_READ);
	if(dataFile) {
		printDebug(FILE_OPEN_SUCCESS, FLASH_DEBUG);
		while(dataFile.available()) {
			char c = dataFile.read();
			Serial.print(c);
		}
		Serial.println();
		dataFile.close();
	} else {
		printDebug(FILE_OPEN_FAILURE, FLASH_DEBUG);
	}

	File file = FlashHelper::openFile(FILE_NAME, FILE_WRITE);
	if(!file) {
		printDebug(FILE_CREATE_FAILURE, FLASH_DEBUG);
		return;
	}

	DynamicJsonDocument doc(capacity);

	JsonObject canBus = doc.createNestedObject(j_CANBUS);
	canBus[j_ADDRTX]    = 0x100;
	canBus[j_BOOTRX]    = 0x666;
	canBus[j_INTVLTX]   = 10;
	canBus[j_MASK0]     = 0x07FF0000;
	canBus[j_FILTER0_0] = 0x01000000;
	canBus[j_FILTER0_1] = 0x01010000;
	canBus[j_MASK1]     = 0x07FF0000;
	canBus[j_FILTER1_0] = 0x01030000;
	canBus[j_FILTER1_1] = 0x01040000;
	canBus[j_FILTER1_2] = 0x01060000;
	canBus[j_FILTER1_3] = 0x01070000;


	if(serializeJson(doc, file) == 0) {
		printDebug(FILE_WRITE_FAILURE, FLASH_DEBUG);
	}

	file.close();
}

void reboot() {
	*DBL_TAP_PTR = DBL_TAP_MAGIC_QUICK_BOOT;
	NVIC_SystemReset();
}

void rebootBootLoader() {
	*DBL_TAP_PTR = DBL_TAP_MAGIC;
	NVIC_SystemReset();
}
