#include "serial-commands.hpp"
#include <Arduino.h>

namespace serial {

void listenSerial(bool &moving, bool &pumping, bool &side, int &targetPan, DRV8825 *height) {
	if (Serial.available() > 0) {
		// read the incoming byte:
		String message = Serial.readStringUntil(';');

		// test the obtained string to know the received command

		if (message.equals("whois"))
			Serial.print("ArmBoard;");
		else if (message.equals("isbusy")) {
			Serial.print(int(moving));
			Serial.print(";");
		}
		else if (message.equals("moveM")) {
			moving = true;
			targetPan = MIDDLE;
		}
		else if (message.equals("moveL")) {
			moving = true;
			targetPan = LEFT;
		}
		else if (message.equals("moveR")) {
			moving = true;
			targetPan = RIGHT;
		}
		else if (message.startsWith("moveTo")) {
			message.remove(0, 6);
			int target = message.toInt();
			targetPan = max(min(5000, target), 0);
		}
		else if (message.equals("pumpon")) {
			pumping = true;
		}
		else if (message.equals("pumpoff")) {
			pumping = false;
		}
	}
}

} // namespace pinout
