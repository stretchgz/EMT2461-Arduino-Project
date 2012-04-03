/*
 * Author: Wai Tsang
 *
 * Arduino for EMT2461 project
 *
 **/

long 		Distance, // => distance between car and object
			duration; // -> bounce back time when soundwave is hitting an object
const int 	pingPin = 7; // pin7 for sensor
short int 	i = 0,
			RandomDirection; // random direction

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
	RandomDirection = rand() % 2;

	// sensor picks up something, then fix motor speed
	if ( 80 <= Distance <= 300 ) // units are in centermeter
	{
		// SlowTheCar
		CarSpeed(1, RandomDirection);
	}
	else if ( Distance < 80 ) 
	{
		// StopTheCar
		CarSpeed(2, RandomDirection);
	}
	else
	{
		// starts motor when there is no object detected
		CarSpeed(3, RandomDirection);
	}
}

/* -------------------------------------

Other Functions to be called in the Main Loop

---------------------------------------- */

// control car speed
void CarSpeed(int speed, int RandomDirection){
	// 1 = 50%
	// 2 = 0%
	if ( speed = 1 )
	{
		analogWrite(5, 180);
		analogWrite(6, 180);
		// wait 800ms, then speed up both motor
		delay(800);
		analogWrite(5, 255);
	}
	else if ( speed = 2 )
	{
		analogWrite(6, 0);
		analogWrite(5, 0);
		// waits 800ms, then speed up both motor
		delay(800); 
		analogWrite(6, 255);
	}
	else
	{
		// always speed up both motor
		analogWrite(5, 255);
		analogWrite(6, 255);
	}
}

// reverse motor
void ReserveCar() {

}