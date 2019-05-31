#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H 1

#define RIGHT 0;
#define MIDDLE 2150;
#define LEFT 4300;

#include "DRV8825.hpp"

namespace serial {

// Listens to the serial port in order to answer questions
void listenSerial(bool&, bool&, bool&, int&, DRV8825 *height);

} // namespace serial

#endif
