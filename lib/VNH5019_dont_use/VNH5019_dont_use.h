//
// Created by Bucky Fellini on 2/28/20.
//

#ifndef TRANSCONTROLLER_VNH5019HELPER_H
#define TRANSCONTROLLER_VNH5019HELPER_H

class VNH5019Helper {
public:
	VNH5019Helper();
	void init();


private:

	double _Setpoint, _Input, _Output;
	double _aggKp, _aggKi, _aggKd;
	double _consKp, _consKi, _consKd;


};

#endif //TRANSCONTROLLER_VNH5019HELPER_H
