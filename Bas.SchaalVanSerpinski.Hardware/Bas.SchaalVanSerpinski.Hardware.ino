
int ledPins[] = { 3, 5, 6, 9, 10 };

// The setup() function runs once each time the micro-controller starts
void setup()
{
	for (size_t i = 0; i < sizeof(ledPins)/sizeof(int); i++)
	{
		pinMode(ledPins[i], OUTPUT);
	}
}

// Add the main program code into the continuous loop() function
void loop()
{
	for (size_t i = 0; i < sizeof(ledPins)/sizeof(int); i++)
	{
		for (int fadeValue = 0; fadeValue <= 255; fadeValue++)
		{
			analogWrite(ledPins[i], fadeValue);
			delay(1);
		}
	}
}
