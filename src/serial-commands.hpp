#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H 1

#include "Arm.hpp"

namespace serial {

// Listens to the serial port in order to answer questions
void listenSerial(Arm);

} // namespace serial

#endif
