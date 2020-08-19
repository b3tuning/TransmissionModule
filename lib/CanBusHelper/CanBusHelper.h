//
// Created by Bucky Fellini on 2/28/20.
//

#ifndef TRANSCONTROLLER_CANBUSHELPER_H
#define TRANSCONTROLLER_CANBUSHELPER_H

#include <ConfigHelper.h>
#include <mcp_can.h>

class CanBusHelper {
public:
	CanBusHelper(CONFIG& config, SHIFTER& position);

//	void init(CAN_BUS_CFG& config);

	void buildMessage(SHIFTER& config);

	void sendMessage(Shifter& position);

	void receiveMessage();

private:
	CONFIG & _config;
	SHIFTER& _position;

	void setMasks();

	void handleMessage();
};

#endif //TRANSCONTROLLER_CANBUSHELPER_H
