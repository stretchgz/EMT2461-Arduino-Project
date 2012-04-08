/*
	Author: Wai Tsang & William Wong

	Description: Arduino for EMT2461 project

	License: WTFPL (http://sam.zoy.org/wtfpl/) 

	Notes:
	1. Robot will not move at full speed for accurate detection of objects.

*/

long 		Distance, 			// distance between car and object
			duration; 			// bounce back time when soundwave is hitting an object
const int 	pingPin = 7, 		// pin7 for sensor
			ledPIN = 13; 		// onboard LED pin
short int 	i = 0,				// for loop counter, starts at zero
			RandomDirection,	// random direction
			randomMotorPin,
			hBridgePin1,
			hBridgePin2;


void setup() {
	// initialize serial communication:
	Serial.begin(9600);

	/*	pinMode();
		ref: http://www.arduino.cc/playground/Interfacing/Processing

		we are using pin#5 and #6 for motors
		sensor are declared in the loop
	*/
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(ledPIN, OUTPUT);

	/* 	initialize random seed
		
		going to use a random number to decide direction 
		when the car is turning
	*/
	randomSeed(analogRead(0));
}

// Main Loop
void loop() {
	// following codes are for Sonar Sensor
	// taken from arduino example
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);
	pinMode(pingPin, INPUT);
	duration = pulseIn(pingPin, HIGH);
	Distance = microsecondsToCentimeters(duration); // convert distance to centimeters

	/*
		randomly generate a number from zero to one
			0 = left
			1 = right
		ref: http://arduino.cc/en/Reference/random
	*/
	RandomDirection = random(2);
	
	/*
	When sensors pick up something, change motor speed & direction

	When an obstacle is:
		1 ft away from robot, stop immediately, then make a turn
		3 ft away from robot, slow down to 50-60% and make a turn
		3+ ft away from robot, move forward

	Controlling Speed by passing parameters into function:
	We give the code a simple number 1, 2 and 3.
		At 1, car moves at slow speed
		At 2, car stop
		At 3, car moves at full speed
	*/

	if ( Distance <= 30 ) // ~1 ft
	{
		// CarSpeed(speed, direction);
		blinkBoardLED(1, 100); // blink onboard LED every 100ms
		CarSpeed(1, RandomDirection);
	}
	else if ( Distance < 100 ) // ~3 ft
	{
		blinkBoardLED(1, 250); // blink LED every 250ms
		CarSpeed(2, RandomDirection);
	}
	else
	{
		blinkBoardLED(0, 0); // LED off
		ForwardCar(0);
	}
}

/* -------------------------------------

Other Functions to be called in the Main Loop

---------------------------------------- */

// Control car speed
void CarSpeed( int ControlSpeed, int RandomDirection) {
	
	/*
		grabs the parameters from function
		set 1 to pin#5
		set 2 to pin#6
	*/
	if ( RandomDirection = 1 ) 
	{
		randomMotorPin = 5;
	}
	else
	{
		randomMotorPin = 6;
	}

	/*
		Control Car
	*/
	if ( ControlSpeed = 1 )
	{
		// reduce power on both motor pins
		analogWrite(5, 180);
		analogWrite(6, 180);
		// wait 800ms
		delay(800);
		// speed up a random motor pin
		analogWrite(randomMotorPin, 255);
		// wait 600ms 
		delay(600);
		// mvoes forward
		ForwardCar(0);
	}
	else if ( ControlSpeed = 2 )
	{
		// stop both motor
		analogWrite(6, 0);
		analogWrite(5, 0);
		// wait 800ms
		delay(800); 
		// call function: move backward
		ReserveCar();
	}
	else
	{
		ForwardCar(0);
	}
}

// Reverse motor utilizes H-Bridge
void ReserveCar() {
	/*
		H-Bridge 4 pins
			1   2
			3   4
		From 	To	
		1 		4 	= forward
		2 		3 	= reverse
	*/
	digitalWrite( hBridgePin1, HIGH );
	digitalWrite( hBridgePin2, LOW );

	/***********************************

		warning	: h-bridge pins havent decided yet...

	***********************************/

}

// Moves car forward
void ForwardCar( int ReverseCurrent ) {
	analogWrite(5, 255);
	analogWrite(6, 255);
}

/*
   Light up the LED and blink
   fast blinking 	= car is about to hit object
   slow blinking  	= something is detected
   no light 		= nothing is detected
*/
void blinkBoardLED( int LED_Switch, int blinkDelayTime ) {
	if ( LED_Switch = 1 ) {
		digitalWrite(ledPIN, HIGH); // lights up
		delay(blinkDelayTime);
		digitalWrite(ledPIN, LOW); // lights out
		delay(blinkDelayTime);
	}
	else {
		digitalWrite(ledPIN, LOW); // lights out, just in case it won't turn off
	}
}

// convert distance from sensor to centermeter
// taken from arduino examples
long microsecondsToCentimeters (long microseconds) {
	return microseconds / 29 / 2;
}

