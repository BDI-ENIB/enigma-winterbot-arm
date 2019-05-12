#include "pinout.hpp"
#include <Arduino.h>

namespace pinout {

void setPinModes() {
	pinMode(DEBUG_LED, OUTPUT);

	pinMode(MOTOR_CH_A, INPUT);
	pinMode(MOTOR_CH_B, INPUT);
	pinMode(MOTOR_BRAKE, OUTPUT);
	pinMode(MOTOR_DIR, OUTPUT);
	pinMode(MOTOR_PWM, OUTPUT);
	pinMode(MOTOR_THERM, INPUT);

	pinMode(PUMP_BRAKE, OUTPUT);
	pinMode(PUMP_DIR, OUTPUT);
	pinMode(PUMP_PWM, OUTPUT);
	pinMode(PUMP_THERM, INPUT);

	pinMode(SERVO_1, OUTPUT);
	pinMode(SERVO_2, OUTPUT);

	pinMode(STEPPER_FAULT, INPUT);
	pinMode(STEPPER_SLEEP, OUTPUT);
	pinMode(STEPPER_STEP, OUTPUT);
	pinMode(STEPPER_DIR, OUTPUT);

	pinMode(POS_ZERO, INPUT);
	pinMode(POS_HIGH, INPUT);

	pinMode(RX_12V1, INPUT);
	pinMode(TX_12V1, OUTPUT);
	pinMode(RX_12V2, INPUT);
	pinMode(TX_12V2, OUTPUT);
	pinMode(RX_24V, INPUT);
	pinMode(TX_24V, OUTPUT);
}

} // namespace pinout
