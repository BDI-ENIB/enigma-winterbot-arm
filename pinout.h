#ifndef PINOUT_H
#define PINOUT_H 1

#include <Arduino.h>

#define DEBUG_LED 13

#define MOTOR_CH_A 32
#define MOTOR_CH_B 31
#define MOTOR_BRAKE 35
#define MOTOR_DIR 36
#define MOTOR_PWM 37
#define MOTOR_THERM 38

#define PUMP_BRAKE 30
#define PUMP_DIR 28
#define PUMP_PWM 29
#define PUMP_THERM 27

#define SERVO_1 22
#define SERVO_2 23

#define STEPPER_FAULT 8
#define STEPPER_SLEEP 7
#define STEPPER_STEP 6
#define STEPPER_DIR 5

#define POS_ZERO 2
#define POS_HIGH 3

#define RX_12V1 21
#define TX_12V1 20
#define RX_12V2 19
#define TX_12V2 18
#define RX_24V 17
#define TX_24V 16


namespace enigma {
namespace pinout {

void setPinModes();

} // namespace pinout
} // namespace enigma

#endif
