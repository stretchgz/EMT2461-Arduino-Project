/*
 * Author: Wai Tsang
 * Main code for EMT2461 project
 * More info plz read ReadMe.md
 **/


// include some basic libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// declare other variables
int DistanceFinder, RandomMovementDirection;

// setup
void setup() {
	// pin #7 is the output
	pinMode(7, OUTPUT);
}


// convert distance from sensor to centermeter
long DistanceConverter () {
	return microseconds / 29 / 2;
}


// reverse motor
void ReverseMotor () {
// RandomMovementDirection = 0 -> left
// RandomMovementDirection = 1 -> right

	// initialize random seed
	srand ( time(NULL) );
	// generate a random number
	RandomMovementDirection = rand() % 1;
}
// car will move left or right randomly
void RandomDirection () {
	if ( RandomMovementDirection == 1 ) {
		// turn left
		// StopLeftMotor();
	}
	else {
		// turn right
		// StopRightMotor();
	} 
}

void MotorSlowDown() {
	//
	//
}
void StopTheCar() {
	// stop the car immediately
	// digitWrite(7,LOW);
}


/**
	* Main Loop
	* Note: following codes or functions are temporary, will be fixed next time
	*
	*/
void loop() {
	// initialize motor
	// InitCar();

	// fix motor speed
	if ( 100 <= DistanceFinder <= 300 ) // units are in centermeter
	{
		// MotorSlowDown();
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

