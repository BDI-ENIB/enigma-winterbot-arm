#ifndef ARM_HPP
#define ARM_HPP 1

#include "DRV8825.hpp"
#include "Motor.hpp"
#include "PID.hpp"
#include "position.hpp"
#include "pinout.hpp"
#include <Servo.h>
#include <Encoder.h>

#define PAN_INTERVAL 20


class Arm
{
public:
	enum Action {
		NOTHING = 0,
		DROP_BEGIN,
		PICK_BEGIN,
		DROP_END,
		PICK_END
	};

	Arm(DRV8825 *height, Motor *pan, Encoder *pan_coder, PID *pan_pid, Servo *tilt, Motor *pump);

	void init();

	void grab();
	void drop();

	void addTarget(int pan, int tilt, int height);
	void addTarget(int pan, int tilt, int height, Action action);

	/**
	 * Schedules a storage action to do and updates counts
	 * Returns: 0 if ok to do so, -1 if not
	 */
	int dropToStorage(int num);
	int pickFromStorage(int num);

	void update();

	bool moveEnded();

	void log(bool machineFriendly);
private:
	void execActionIfOK();

	int targetPan = 0, targetTilt = 0, targetHeight = 0;
	int lastPan = 0, lastHeight = 0;
	int currentPan = 0, currentHeight = 0; // no currentTilt as it has no feedback, currentHeight saves position only when arrived
	unsigned long tilt_arrived = 0; // time at which the tilt servo will arrive, estimation

	const int storagesPan[2] = {position::pan::STORE_1, position::pan::STORE_2};
	const int storagesHeight[4] = {position::height::STORE_0, position::height::STORE_1, position::height::STORE_2, position::height::STORE_3};
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
