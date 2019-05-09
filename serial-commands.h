#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H 1

#include <Arduino.h>

#include "pinout.h"

namespace serial {

// Listens to the serial port in order to answer questions
void listenSerial();

} // namespace serial

#endif
