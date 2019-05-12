#ifndef ARM_HPP
#define ARM_HPP 1

#include "DRV8825.hpp"
#include "Motor.hpp"
#include "PID.hpp"
#include "positions.hpp"
#include <Servo.h>
#include <Encoder.h>

#define PAN_INTERVAL 20
#define HEIGHT_INTERVAL 2


class Arm
{
public:
	Arm(DRV8825 *height, Motor *pan, Encoder *pan_coder, PID *pan_pid, Servo *tilt, Motor *pump);

	void grab();
	void drop();

	void setTarget(int pan, int tilt, int height);
	void setTarget(int pan, int tilt, int height, int action);

	/**
	 * Schedules a storage action to do and updates counts
	 * Returns: 0 if ok to do so, -1 if not
	 */
	int dropToStorage(int num);
	int pickFromStorage(int num);

	void update();

	bool moveEnded();

	void log();
private:
	void updateCurrentPos();
	void execActionIfOK();

	int targetPan = 0, targetTilt = 0, targetHeight = 0;
	int lastPan = 0, lastHeight = 0;
	int currentPan = 0, currentHeight = 0; // no currentTilt as it has no feedback
	unsigned long tilt_arrived = 0; // time at which the tilt servo will arrive, estimation

	const int storagesPan[2] = {positions::pan::STORE_1, positions::pan::STORE_2};
	const int storagesHeight[4] = {positions::height::STORE_0, positions::height::STORE_1, positions::height::STORE_2, positions::height::STORE_3};
	int storageCount[2] = {0, 0};

	bool pumpOn = false;
	unsigned long pumpStopTime = 0; // time at which to shut the pump off after dropping

	int scheduledAction = 0;

	DRV8825 *height;
	Motor *pan;
	Encoder *pan_coder;
	PID *pan_pid;
	Servo *tilt;
	Motor *pump;
};

#endif
