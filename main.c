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


// car will move left or right randomly
int RandomDirection () {
	
	// initialize random seed
	
	// RandomMovementDirection = 0 -> left
	// RandomMovementDirection = 1 -> right
	srand ( time(NULL) );
	// generate a random number
	RandomMovementDirection = rand() % 1;
	
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
	// reduce powa!
	//
}
void StopTheCar() {
	// cut the powa!
	// digitWrite(7,LOW);
}
// reverse motor
void ReverseMotor () {
	// if the car can stop, then it can slow down
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

