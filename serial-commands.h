#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H 1

#include <Arduino.h>

#include "pinout.h"

namespace enigma {
namespace serial {

// Listens to the serial port in order to answer questions
void listenSerial();

} // namespace pinout
} // namespace serial

#endif
