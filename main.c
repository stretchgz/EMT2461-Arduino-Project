/*
 * Author: Wai Tsang
 *
 * Arduino for EMT2461 project
 *
 **/


// include some basic libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// declare other variables
int DistanceFinder, RandomMovementDirection;

// setup
void setup() {
	// multiple input
	// int pin[5];

	/* 
	pin[0] = left motor
	pin[1] = right motor
	pin[2] = sensor left
	pin[3] = sensor right
	pin[4] = optical encoder > motor left
	pin[5] = optical encoder > motor right
	*/

	// pin #7 is the output
	pinMode(7, OUTPUT);
}


// convert distance from sensor to centermeter
// taken from arduino examples
long DistanceConverter () {
	return microseconds / 29 / 2;
}


// generate a random number to make the robot turns left or right
// 0 = left
// 1 = right
int RandomDirection () {
	
	// initialize random seed
	srand ( time(NULL) );
	// generate a random number
	RandomMovementDirection = rand() % 1;

	// condition
	if ( RandomMovementDirection == 1 ) {
		// turn left, slow motor down or stop it
		// StopLeftMotor();
	}
	else {
		// turn right
		// StopRightMotor();
	} 
}

void SlowDown() {
	// use analog replaces didigtal write for speed console
	// analogWrite(pin[0],190);
	// analogWrite(pin[1],190);
}
void StopTheCar() {
	// cut the powa!
	// digitWrite(7,LOW);
}
// reverse motor
void ReverseMotor () {
	// if the car can stop, then it can slow down
}


// Main Loop
void loop() {
	// initialize motor
	// InitCar();

	// fix motor speed
	if ( 100 <= DistanceFinder <= 300 ) // units are in centermeter
	{
		// SlowDown();
	}
	else if ( 50 <= DistanceFinder < 100 ) 
	{
		// StopTheCar();
	}
	else
	{
		// wateva();
	}

}