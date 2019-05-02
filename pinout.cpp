#include "pinout.h"

namespace enigma {
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

	pinMode(END_STOP_T, INPUT);
	pinMode(END_STOP_R, INPUT);
}

} // namespace pinout
} // namespace enigma