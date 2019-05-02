#include "serial-commands.h"

namespace enigma {
namespace serial {

void listenSerial() {
	if (Serial.available() > 0) {
		// read the incoming byte:
		String message = Serial.readStringUntil(';');

		// test the obtained string to know the received command

		if (message.equals("whois"))
			Serial.println("ArmBoard;");
	}
}

} // namespace pinout
} // namespace serial
