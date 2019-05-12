#include "Arm.hpp"
#include <Arduino.h>

// public methods

Arm::Arm(DRV8825 *height, Motor *pan, Encoder *pan_coder, PID *pan_pid, Servo *tilt, Motor *pump):
	height{height},
	pan{pan}, pan_coder{pan_coder}, pan_pid{pan_pid},
	tilt{tilt},
	pump{pump}
{}

void Arm::init() {
	tilt->write(position::tilt::HORIZONTAL);

	height->begin();
	height->enable();
	height->startMove(100*200);
	while(not digitalRead(POS_HIGH)) {
		height->nextAction();
	}
	height->stop();
}

void Arm::grab() {
	pumpOn = true;
	pump->setSpeed(256); // 100% on
}

void Arm::drop() {
	pump->setSpeed(-256); // 100% on, drop
	pumpStopTime = millis() + 2000; // wait a bit before stopping pump, TO ADJUST
	pumpOn = false;
}

void Arm::setTarget(int pan, int tilt, int height) {
	targetPan    = max(position::pan::STORE_1, min(pan, position::pan::STORE_2));
	targetTilt   = max(position::tilt::STORAGE, min(pan, position::tilt::ANGLED_BACK));
	targetHeight = max(position::height::BOTTOM, min(pan, position::height::TOP));
}

/**
 * action:
 *   0: nothing
 *   1: drop at begin
 *   2: pick at begin
 *   3: drop at end
 *   4: pick at end
 */
void Arm::setTarget(int pan, int tilt, int height, int action) {
	setTarget(pan, tilt, height);
	scheduledAction = (action >= 0 && action <= 4) ? action : 0;
	execActionIfOK();
}

int Arm::dropToStorage(int storN) {
	if (storN < 0 || storN > 1 || storageCount[storN] == 3) {
		return -1;
	}

	const int tP = storagesPan[storN];
	const int tT = position::tilt::HORIZONTAL;
	const int tH = storagesHeight[storageCount[storN] + 1];

	setTarget(tP, tT, tH, 3 /*drop at end*/);

	storageCount[storN]++;

	return 0;
}

int Arm::pickFromStorage(int storN) {
	if (storN < 0 || storN > 1 || storageCount[storN] == 0) {
		return -1;
	}

	const int tP = storagesPan[storN];
	const int tT = position::tilt::HORIZONTAL;
	const int tH = storagesHeight[storageCount[storN]];

	setTarget(tP, tT, tH, 4 /*pick at end*/);

	storageCount[storN]--;

	return 0;
}

/**
 * This function :
 *   - updates the position with Arm::updateCurrentPos
 *   - updates the PID
 *   - updates the stepper driver
 *   - turns the pump off if needed
 *   - calls the action via Arm::execActionIfOK
 */
void Arm::update() {
	updateCurrentPos();

	pan_pid; //TODO
	pan; //TODO

	tilt; //TODO

	execActionIfOK();
}

bool Arm::moveEnded() {
	const int panDiff = targetPan - currentPan;
	const int heightDiff = targetHeight - currentHeight;

	const bool tiltOK = millis() >= tilt_arrived;
	const bool panOK = PAN_INTERVAL >= abs(panDiff);
	const bool heightOK = HEIGHT_INTERVAL >= abs(heightDiff);

	return tiltOK && panOK && heightOK;
}

void Arm::log(bool machineFriendly) {
	if (machineFriendly) {
		Serial.print("LOG");
		Serial.print(targetPan);
		Serial.print(",");
		Serial.print(targetTilt);
		Serial.print(",");
		Serial.print(targetHeight);
		Serial.print(",");
		Serial.print(int(moveEnded()));
		Serial.print(",");
		Serial.print(int(pumpOn));
		Serial.println(";");
	} else {
		Serial.print("Move to (p, t, h) :");
		Serial.print(targetPan);
		Serial.print(", ");
		Serial.print(targetTilt);
		Serial.print(", ");
		Serial.println(targetHeight);
		if (moveEnded()) {
			Serial.println("Arrived");
		} else {
			Serial.println("In progress");
		}
		if (pumpOn) {
			Serial.println("Pump is on");
		} else {
			Serial.println("Pump is off or releasing");
		}
	}
}

// private methods

void Arm::updateCurrentPos() {
	lastPan = currentPan;
	lastHeight = currentHeight;

	currentPan = pan_coder->read();
	currentHeight; //TODO
}

void Arm::execActionIfOK() {
	switch (scheduledAction)
	{
	case 1:
		scheduledAction = 0;
		drop();
		break;
	case 2:
		scheduledAction = 0;
		grab();
		break;
	case 3:
		if (moveEnded()) {
			scheduledAction = 0;
			drop();
		}
		break;
	case 4:
		if (moveEnded()) {
			scheduledAction = 0;
			grab();
		}
		break;
	}
}
