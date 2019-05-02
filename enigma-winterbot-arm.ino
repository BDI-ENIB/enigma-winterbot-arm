#include "pinout.h"
#include "serial-commands.h"

void setup()
{
	Serial.begin(9600);
	
	enigma::pinout::setPinModes();
}

void loop()
{
	static bool led_state = LOW;
	led_state = !led_state;
	digitalWrite(DEBUG_LED, led_state);

	enigma::serial::listenSerial();
}
