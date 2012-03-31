/*
 * Author: Wai Tsang
 *
 * Arduino for EMT2461 project
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// declare variables
long Distance, duration;
const int pingPin = 7; // pin7 for sensor
short int i=0, Direction;

// setup
void setup() {
	// initialize serial communication:
	Serial.begin(9600);

	/* 
		pinMode() ref: http://www.arduino.cc/playground/Interfacing/Processing

		we are using pin#5 and #6 for motors
		sensor are declared in the loop
	*/
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	// initialize random seed
	srand ( time(NULL) );
}

// convert distance from sensor to centermeter
// taken from arduino examples
long microsecondsToCentimeters (long microseconds) {
	return microseconds / 29 / 2;
}

// Main Loop
void loop() {
	// get distance
	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);

	// The same pin is used to read the signal from the PING))): a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(pingPin, INPUT);
	duration = pulseIn(pingPin, HIGH);
	Distance = microsecondsToCentimeters(duration);


	// generate a random number for choosing random direction
	// 0 = left
	// 1 = right
	Direction = rand() % 2;

	// sensor picks up something, then fix motor speed
	if ( 100 <= Distance <= 300 ) // units are in centermeter
	{
		// SlowTheCar
		CarSpeed(1, Direction);
	}
	else if ( 50 <= Distance < 100 ) 
	{
		// StopTheCar
		CarSpeed(2, Direction);
	}
	else
	{
		// starts motor when there is no object detected
		CarSpeed(3, Direction);
	}
}

/* -------------------------------------

Other Functions to be called in the Main Loop

---------------------------------------- */

// control car speed
void CarSpeed(int speed, int direction){
	// 1 = 50%
	// 2 = 0%
	if ( speed = 1 )
	{
		digitalWrite(5, LOW);
		digitalWrite(6, HIGH);
		// wait 1sec, then speed up both motor
		delay(1000);
		digitalWrite(5, HIGH);
	}
	else if ( speed = 2 )
	{
		digitalWrite(6, LOW);
		digitalWrite(5, LOW);
		// waits 1sec, then speed up both motor
		delay(1000); 
		digitalWrite(6, HIGH);
	}
	else
	{
		// always speed up both motor
		digitalWrite(5, HIGH);
		digitalWrite(6, HIGH);
	}
}