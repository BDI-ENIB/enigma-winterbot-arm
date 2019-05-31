#include "src/pinout.hpp"
#include "src/serial-commands.hpp"
#include "src/DRV8825.hpp"
#include "src/PID.hpp"
#include "src/Motor.hpp"
#include "src/DRV8825.hpp"
#include <Servo.h>
#include <Encoder.h>

#define MAX_PWM 100

IntervalTimer controlTimer;
DRV8825 *height = new DRV8825(200, STEPPER_DIR, STEPPER_STEP, STEPPER_SLEEP);
Encoder pan_coder(MOTOR_CH_A, MOTOR_CH_B);
Motor *pan = new Motor(MOTOR_PWM, MOTOR_BRAKE, MOTOR_DIR);
PID *pan_pid = new PID(1, 0, 0, 0);
Motor *pump = new Motor(PUMP_PWM, PUMP_BRAKE, PUMP_DIR);

bool moving = false;
bool pumping = false;
bool side = false;

int lastPan, currentPan, targetPan = 0;

void setup()
{
	Serial.begin(250000);
	delay(3000);

	//pinout::setPinModes();
	pinMode(DEBUG_LED, OUTPUT);

	height->begin();
	height->enable();
}

void loop()
{
	static bool first = true;
	if (first) {
		// On lance "l'asservissement"
		controlTimer.begin(mainLoop, 4166);
		controlTimer.priority(129);
		first = false;
	}

	static bool led_state = LOW;
	led_state = !led_state;
	digitalWrite(DEBUG_LED, led_state);

	serial::listenSerial(moving, pumping, side, targetPan, height);

	//Serial.println(pan_coder.read());

	delay(height->nextAction() or 50);
}

void mainLoop() {
	lastPan = currentPan;
	
	currentPan = pan_coder.read();

	pan_pid->setTarget(targetPan);
	pan_pid->update(currentPan);
	if (currentPan <= 5500 and currentPan >= -500) {
		pan->setSpeed(max(-MAX_PWM, min(MAX_PWM, -pan_pid->getCommand())));
	} else {
		pan->setSpeed(0);
	}

	if (abs(currentPan - targetPan) <= 10) {
		moving = false;
	}
	

	if (pumping) {
		pump->setSpeed(256);
	} else {
		pump->setSpeed(0);
	}
}
