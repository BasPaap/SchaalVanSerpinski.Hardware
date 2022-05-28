#include "SerialCommandReader.h"

Bas::SerialCommandReader::SerialCommandReader() : numCharsInBuffer{ 0 }
{
	clearBuffer();
	clearLastCommand();
}

void Bas::SerialCommandReader::update()
{
	if (Serial.available())
	{
		if (numCharsInBuffer >= maxCommandSize)
		{
			clearBuffer();
		}

		readBuffer[numCharsInBuffer] = Serial.read();
		numCharsInBuffer++;

		if (readBuffer[numCharsInBuffer - 1] == '\n')
		{
			readBuffer[numCharsInBuffer - 1] = '\0';

			// complete command found.
			clearLastCommand();
			strcpy(lastCommand, readBuffer);
			clearBuffer();
		}
	}
}

bool Bas::SerialCommandReader::isCommandAvailable()
{
	return strlen(lastCommand) > 0;
}

void Bas::SerialCommandReader::getLastCommand(char* command, int size)
{
	strncpy(command, lastCommand, size);
	//clearLastCommand();
}

void Bas::SerialCommandReader::clearBuffer()
{
	numCharsInBuffer = 0;
	for (size_t i = 0; i < maxCommandSize; i++)
	{
		readBuffer[i] = '\0';
	}
}

void Bas::SerialCommandReader::clearLastCommand()
{
	lastCommand[0] = '\0';
}