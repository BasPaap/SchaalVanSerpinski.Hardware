#include "CommandHandler.h"

Bas::CommandHandler::CommandHandler() : numCallbacks{ 0 }
{
}

void Bas::CommandHandler::setCallback(const char* command, CallbackPointer callback)
{
	for (size_t i = 0; i < this->numCallbacks; i++)
	{
		if (strcmp(this->commands[i], command) == 0)
		{
			// There was already a callback for this command, so we'll replace it instead of creating a new one.
			this->callbacks[i] = callback;
			return;
		}
	}

	// If the command was not yet associated with a callback, add the new callback and command.
	if (this->numCallbacks < maxCallbacks)
	{
		this->commands[numCallbacks] = command;
		this->callbacks[numCallbacks] = callback;
		this->numCallbacks++;
	}
}

void Bas::CommandHandler::update()
{
	this->serialCommandReader.update();
	if (this->serialCommandReader.isCommandAvailable())
	{
		char command[maxCommandSize];
		this->serialCommandReader.getLastCommand(command, maxCommandSize);

		Serial.print(millis());
		Serial.print(" Received command ");
		Serial.print(command);
		Serial.print(" ");
		Serial.print(this->numCallbacks);
		Serial.println(".");

		for (size_t i = 0; i < this->numCallbacks; i++)
		{
			if (strcmp(this->commands[i], command) == 0)
			{
				if (this->callbacks[i] != NULL)
				{
					this->callbacks[i]();
				}

				this->serialCommandReader.clearLastCommand();
			}
		}
	}
}