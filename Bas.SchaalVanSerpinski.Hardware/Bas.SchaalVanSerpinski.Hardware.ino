
#include "CommandHandler.h"

int ledPins[] = { 3, 5, 6, 9, 10 };
int fadeInSpeed = 2;
int fadeInMaxValue = 255;
int glowSpeed = 2;
int pentagramDisplayDuration = 5000;

constexpr auto handshakeCommand = "SERPINSKI";
constexpr auto handshakeResponse = "SERPINSKI_OK";
constexpr auto showPentagramStartCommand = "PENTAGRAM_START";
constexpr auto showPentagramEndCommand = "PENTAGRAM_END";

Bas::CommandHandler commandHandler;

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	Serial.println("Schaal van Serpinski hardware controller v1.0");

	for (size_t i = 0; i < sizeof(ledPins) / sizeof(int); i++)
	{
		pinMode(ledPins[i], OUTPUT);
	}

	// Listen for the handshake command. If we receive it, enable all other commands.
	commandHandler.setCallback(handshakeCommand, enableSerialCommands);
}

// Add the main program code into the continuous loop() function
void loop()
{
	commandHandler.update();
}

void showPentagramStart()
{
	int numLeds = sizeof(ledPins) / sizeof(int);
	for (size_t i = 0; i < numLeds; i++)
	{
		for (int fadeInValue = 0; fadeInValue <= fadeInMaxValue; fadeInValue++)
		{
			analogWrite(ledPins[i], fadeInValue);
			delay(fadeInSpeed);
		}
	}

	delay(pentagramDisplayDuration);

	for (int glowOutValue = fadeInMaxValue; glowOutValue >= 0; glowOutValue--)
	{
		for (size_t i = 0; i < numLeds; i++)
		{
			analogWrite(ledPins[i], glowOutValue);
		}

		delay(glowSpeed);
	}
}

void showPentagramEnd()
{
	int numLeds = sizeof(ledPins) / sizeof(int);

	for (int fadeInValue = 0; fadeInValue <= fadeInMaxValue; fadeInValue++)
	{
		for (size_t i = 0; i < numLeds; i++)
		{
			analogWrite(ledPins[i], fadeInValue);
		}

		delay(fadeInSpeed);
	}


	delay(pentagramDisplayDuration);

	for (int glowOutValue = fadeInMaxValue; glowOutValue >= 0; glowOutValue--)
	{
		for (size_t i = 0; i < numLeds; i++)
		{
			analogWrite(ledPins[i], glowOutValue);
		}

		delay(glowSpeed);
	}
}

void enableSerialCommands()
{
	// We received a request to start sending commands from the host device,
	// so we'll enable all commands and respond that we are ready to receive them.
	commandHandler.setCallback(showPentagramStartCommand, showPentagramStart);
	commandHandler.setCallback(showPentagramEndCommand, showPentagramEnd);
	Serial.println(handshakeResponse);
}