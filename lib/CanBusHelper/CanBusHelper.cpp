//
// Created by Bucky Fellini on 2/28/20.
//

#include <CanBusHelper.h>

const char* CANBUS_SUCCESS  = "CanBus initialized successfully";
const char* CANBUS_FAILURE  = "ERROR initializing CanBus";
const char* MESSAGE_SUCCESS = "Message sent successfully";
const char* MESSAGE_FAILURE = "ERROR sending message";

byte canData[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned long prevTX  = 0;

long unsigned int rxId;
unsigned char     len = 8;
unsigned char     rxBuf[8];
// Serial Output String Buffer
char              msgString[128];

MCP_CAN CAN0(CAN_CS);

CanBusHelper::CanBusHelper(CONFIG& config, SHIFTER& position) : _config(config),
																_position(position) {
	if(CAN0.begin(MCP_STD, CAN_1000KBPS, MCP_20MHZ) == CAN_OK) {
		printDebug(CANBUS_SUCCESS, CANBUS_DEBUG);
	} else {
		printDebug(CANBUS_FAILURE, CANBUS_DEBUG);
	}
	setMasks();
	CAN0.setMode(MCP_NORMAL);

}

//void CanBusHelper::init(CAN_BUS_CFG& config) {
//	_config = config;
//	if(CAN0.begin(MCP_STD, CAN_1000KBPS, MCP_20MHZ) == CAN_OK) {
//		printDebug(CANBUS_SUCCESS, CANBUS_DEBUG);
//	} else {
//		printDebug(CANBUS_FAILURE, CANBUS_DEBUG);
//	}
//	setMasks();
//	CAN0.setMode(MCP_NORMAL);
//}

void CanBusHelper::buildMessage(SHIFTER& position) {
	for(int i = 0; i < len; i++) {
		canData[i] = ((i == static_cast<int>(position)) ? 0x01 : 0x00);
	}
	if((position == SHIFTER::UP) || (position == SHIFTER::DOWN)) {
		canData[static_cast<int>(SHIFTER::MANUAL)] = 0x01;
	}
}

void CanBusHelper::sendMessage(SHIFTER& position) {
	unsigned long now = millis();
	if(now - prevTX >= _config.canBus.intvlTX) {
		prevTX       = now;
		buildMessage(position);
		byte sndStat = CAN0.sendMsgBuf(_config.canBus.addrTX, len, canData);

		if(sndStat == CAN_OK) {
			printDebug(MESSAGE_SUCCESS, CANBUS_DEBUG);
		} else {
			printDebug(MESSAGE_FAILURE, CANBUS_DEBUG);
		}
	}
}

void CanBusHelper::setMasks() {
	CAN0.init_Mask(0, 0, _config.canBus.mask0);     //0x07FF0000);
	CAN0.init_Filt(0, 0, _config.canBus.filter0_0); //0x06660000);
	CAN0.init_Filt(1, 0, _config.canBus.filter0_1); //0x01010000);

	CAN0.init_Mask(1, 0, _config.canBus.mask1);     //0x07FF0000);
	CAN0.init_Filt(2, 0, _config.canBus.filter1_0); //0x01030000);
	CAN0.init_Filt(3, 0, _config.canBus.filter1_1); //0x01040000);
	CAN0.init_Filt(4, 0, _config.canBus.filter1_2); //0x01060000);
	CAN0.init_Filt(5, 0, _config.canBus.filter1_3); //0x01070000);

}

void CanBusHelper::receiveMessage() {
	if(!digitalRead(CAN0_INT)) {
		CAN0.readMsgBuf(&_config.canBus.bootRX, &len, rxBuf);
#if MAIN_DEBUG || CANBUS_DEBUG
		if((rxId & 0x80000000) ==
		   0x80000000) { // Determine if ID is standard (11 bits) or extended (29 bits)
			sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:",
					(rxId & 0x1FFFFFFF), len);
		} else {
			sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
		}
		Serial.print(msgString);
#endif

		if((rxId & 0x40000000) == 0x40000000) {
#if MAIN_DEBUG || CANBUS_DEBUG
			sprintf(msgString, "  REMOTE REQUEST FRAME");
			Serial.print(msgString);
#endif
		} else {
#if MAIN_DEBUG || CANBUS_DEBUG
			for(byte i = 0; i < len; i++) {
				sprintf(msgString, " 0x%.2X, rxBuf[i])";
				Serial.orint(msgString);
			}
#endif
			handleMessage();
#if MAIN_DEBUG || CANBUS_DEBUG
			Serial.println();
#endif
		}
	}
}

void CanBusHelper::handleMessage() {

}