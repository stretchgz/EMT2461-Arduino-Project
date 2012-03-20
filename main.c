/*
 * Author: Wai Tsang
 *
 * Arduino for EMT2461 project
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// declare other variables
int Direction;
long Distance, duration;
const int pingPin = 11;

// setup
void setup() {
	// initialize serial communication:
  Serial.begin(9600);
	// multiple input
	// int pin[5];
	for(int i = 0; i<5; i++) {
		pin[i];
	}
	/* 
	pin[0] = left motor
	pin[1] = right motor
	pin[2] = sensor left
	pin[3] = sensor right
	pin[4] = optical encoder > motor left
	pin[5] = optical encoder > motor right
	*/

	// output pin
	pinMode(7, OUTPUT);
}

// convert distance from sensor to centermeter
// taken from arduino examples
long microsecondsToCentimeters (long microseconds) {
	return microseconds / 29 / 2;
}

// Main Loop
void loop() {
	// get distance
	pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  Distance = microsecondsToCentimeters(duration);



	// initialize motor
	CarSpeed(3);

	// initialize random seed
	srand ( time(NULL) );

	// generate a random number for choosing random direction
	// 0 = left	/ 1 = right
	Direction = rand() % 1;

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
		// moves car forward
		CarSpeed(3, Direction);
	}

}


// control car speed
void CarSpeed(int speed, int direction){
	// 1 = 50%
	// 2 = 0%
	if (speed = 1) {
		analogWrite(pin[direction], 180);
		// digitalWrite(7, LOW);
	}
	else if (speed = 2) {
		analogWrite(pin[direction], 0);
		// digitalWrite(7, LOW);
	}
	else {
		analogWrite(7, 255);
		// digitalWrite(7, HIGH);
	}
}