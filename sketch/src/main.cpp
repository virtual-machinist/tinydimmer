#include <Arduino.h>

const int minPwm = 16;
const int maxPwm = 255;
const int endClamp = 240;

extern int mapToPwm(int rawAnalogValue);

void setup()
{
	pinMode(0, INPUT);
	pinMode(1, OUTPUT);
}

void loop()
{
	int enabled = digitalRead(0);
	if (enabled == HIGH) {
		int potentiometerValue = analogRead(1);
		analogWrite(1, mapToPwm(potentiometerValue));
	} else {
		analogWrite(1, 0);
	}
	// poll 10 times a second
	delay(100);
}

int mapToPwm(int rawAnalogValue)
{
	// 10-bit DAC returns a value in 0..1023 range, but we need 8-bits for PWM
	int pwmValue = int(rawAnalogValue * 0.25);
	// but LEDs have erratic starting if PWM duty cycle is too low
	if (pwmValue < minPwm)
	{
		return minPwm;
	}
	// disable PWM if the value is very close to maximum
	else if (pwmValue > endClamp)
	{
		return maxPwm;
	}
	else
	{
		return pwmValue;
	}
}
