#ifndef PINOUT_H
#define PINOUT_H 1

#define DEBUG_LED 13

#define MOTOR_CH_A 32   // in
#define MOTOR_CH_B 31   // in
#define MOTOR_BRAKE 35  // out
#define MOTOR_DIR 36    // out
#define MOTOR_PWM 37    // out
#define MOTOR_THERM 38  // in

#define PUMP_BRAKE 30   // out
#define PUMP_DIR 28     // out
#define PUMP_PWM 29     // out
#define PUMP_THERM 27   // in

#define SERVO_1 22      // out
#define SERVO_2 23      // out

#define STEPPER_FAULT 8 // in
#define STEPPER_SLEEP 7 // out
#define STEPPER_STEP 6  // out
#define STEPPER_DIR 5   // out

#define POS_ZERO 2      // in
#define POS_HIGH 3      // in

#define RX_12V1 21      // in
#define TX_12V1 20      // out
#define RX_12V2 19      // in
#define TX_12V2 18      // out
#define RX_24V 17       // in
#define TX_24V 16       // out


namespace pinout {

void setPinModes();

} // namespace pinout

#endif
