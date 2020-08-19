//
// Created by Bucky Fellini on 3/3/20.
//

#ifndef TRANSCONTROLLER_VNH5019HELPER_H
#define TRANSCONTROLLER_VNH5019HELPER_H

class VNH5019Helper {
public:
	VNH5019Helper();
//	void init();
	static void setSpeed(int speed);
	static void setBrake(int brake);
	static unsigned int getCurrentMilliAmps();
	static unsigned char hasFault();
	static void stopIfFault();

};
#endif //TRANSCONTROLLER_VNH5019HELPER_H
