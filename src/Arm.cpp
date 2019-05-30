#include "Arm.hpp"
#include <Arduino.h>

#define MAX_PWM 256


Arm::Arm(DRV8825 *height, Motor *pan, Encoder *pan_coder, PID *pan_pid, Servo *tilt, Motor *pump):
	height{height},
	pan{pan}, pan_coder{pan_coder}, pan_pid{pan_pid},
	tilt{tilt},
	pump{pump}
{}

void Arm::init() {
	height->begin();
	height->enable();
	height->startMove(100 * 200); // 100 tours de 200 pas
	while (digitalRead(POS_HIGH)) {
		height->nextAction();
	}
	height->stop();

	addTarget(position::pan::STORE_1, position::tilt::HORIZONTAL, position::height::STORE_1);
}

void Arm::grab() {
	pumpOn = true;
	pump->setSpeed(MAX_PWM); // 100% on
}

void Arm::drop() {
	pump->setSpeed(-MAX_PWM); // 100% on, drop
	pumpStopTime = millis() + 2000; // wait a bit before stopping pump, TO ADJUST if the pallet is not dropped when pump stops
	pumpOn = false;
}


void Arm::addTarget(const int told_pan, const int told_tilt, const int told_height) {
	targetPan = max(position::pan::STORE_1, min(told_pan, position::pan::STORE_2));
	const int constrained_tilt = max(position::tilt::STORAGE, min(told_tilt, position::tilt::ANGLED_BACK));
	tilt_arrived = millis() + abs(told_tilt - targetTilt) * 10;
	targetTilt = constrained_tilt;
	targetHeight = max(position::height::BOTTOM, min(told_height, position::height::TOP));

	height->startMove(currentHeight - targetHeight);
}

void Arm::addTarget(int pan, int tilt, int height, Action action) {
	addTarget(pan, tilt, height);
	scheduledAction =  action;
	execActionIfOK();
}

int Arm::dropToStorage(int storN) {
	if (storN < 0 || storN > 1 || storageCount[storN] == 3) {
		return -1;
	}

	const int tP = storagesPan[storN];
	const int tT = position::tilt::HORIZONTAL;
	const int tH = storagesHeight[storageCount[storN] + 1];

	addTarget(tP, tT, tH, DROP_END);

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

	addTarget(tP, tT, tH, PICK_END);

	storageCount[storN]--;

	return 0;
}

/**
 * This function :
 *   - updates the position
 *   - updates the PID
 *   - updates the stepper driver
 *   - turns the pump off if needed
 *   - calls the action via Arm::execActionIfOK
 */
void Arm::update() {
	lastPan = currentPan;
	currentPan = pan_coder->read();

	pan_pid->setTarget(targetPan);
	pan_pid->update(currentPan);
	pan->setSpeed(max(-MAX_PWM, min(MAX_PWM, pan_pid->getCommand())));

	tilt->write(targetTilt);

	if (height->nextAction() == 0) {
		currentHeight = targetHeight;
	}

	if (not pumpOn and millis() >= pumpStopTime) {
		pump->setSpeed(0);
	}

	execActionIfOK();
}

bool Arm::moveEnded() {
	const int panDiff = targetPan - currentPan;

	const bool tiltOK = millis() >= tilt_arrived;
	const bool panOK = PAN_INTERVAL >= abs(panDiff);
	const bool heightOK = targetHeight == currentHeight;

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
		Serial.print("Move to (p, t, h) : ");
		Serial.print(targetPan);
		Serial.print(", ");
		Serial.print(targetTilt);
		Serial.print(", ");
		Serial.println(targetHeight);
		Serial.print("Current (p, h) : ");
		Serial.print(currentPan);
		Serial.print(", ");
		Serial.println(currentHeight);
		Serial.println(digitalRead(POS_HIGH));
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

void Arm::execActionIfOK() {
	switch (scheduledAction)
	{
	case 1:
		scheduledAction = NOTHING;
		drop();
		break;
	case 2:
		scheduledAction = NOTHING;
		grab();
		break;
	case 3:
		if (moveEnded()) {
			scheduledAction = NOTHING;
			drop();
		}
		break;
	case 4:
		if (moveEnded()) {
			scheduledAction = NOTHING;
			grab();
		}
		break;
	}
}
