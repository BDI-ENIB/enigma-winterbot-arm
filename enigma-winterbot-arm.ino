#include "src/pinout.hpp"
#include "src/serial-commands.hpp"
#include "src/PID.hpp"
#include "src/DRV8825.hpp"
#include "src/Motor.hpp"
#include "src/Arm.hpp"
#include <Servo.h>
#include <Encoder.h>

IntervalTimer controlTimer;
DRV8825 *height = new DRV8825(200, STEPPER_DIR, STEPPER_STEP, STEPPER_SLEEP);
Servo *tilt = new Servo();
Encoder *pan_coder = new Encoder(MOTOR_CH_A, MOTOR_CH_B);
Motor *pan = new Motor(MOTOR_PWM, MOTOR_BRAKE, MOTOR_DIR);
PID *pan_pid = new PID(0, 0, 0, 0);
Motor *pump = new Motor(PUMP_PWM, PUMP_BRAKE, PUMP_DIR);

Arm arm(height, pan, pan_coder, pan_pid, tilt, pump);

const bool machineFriendly = false; //log format

void setup()
{
	Serial.begin(250000);
	delay(3000);

	pinout::setPinModes();

	tilt->attach(SERVO_1);

	// On lance l'asservissement
	controlTimer.begin(mainLoop, 4166);
	controlTimer.priority(129);
}

void loop()
{
	static bool led_state = LOW;
	led_state = !led_state;
	digitalWrite(DEBUG_LED, led_state);

	serial::listenSerial();

	arm.log(machineFriendly);
}

void mainLoop()
{
	arm.update();
}
