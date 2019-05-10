#include "src/pinout.h"
#include "src/serial-commands.h"

void setup()
{
	Serial.begin(9600);
	
	pinout::setPinModes();
}

void loop()
{
	static bool led_state = LOW;
	led_state = !led_state;
	digitalWrite(DEBUG_LED, led_state);

	serial::listenSerial();
}
