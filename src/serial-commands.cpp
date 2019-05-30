#include "serial-commands.hpp"
#include <Arduino.h>

namespace serial {

void listenSerial(Arm arm) {
	if (Serial.available() > 0) {
		// read the incoming byte:
		String message = Serial.readStringUntil(';');

		// test the obtained string to know the received command

		if (message.equals("whois"))
			Serial.print("ArmBoard;");
		else if (message.equals("isbusy")) {
			Serial.print(int(not arm.moveEnded()));
			Serial.print(";");
		}
	}
}

} // namespace pinout
