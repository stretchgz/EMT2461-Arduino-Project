/*
	Author: Wai Tsang & William Wong

	Description: Arduino for EMT2461 project

	License: WTFPL (http://sam.zoy.org/wtfpl/)



_____/\\\\\\\\\____________________________/\\\______________________________________________________        
 ___/\\\\\\\\\\\\\_________________________\/\\\______________________________________________________       
  __/\\\/////////\\\________________________\/\\\___________________/\\\_______________________________      
   _\/\\\_______\/\\\___/\\/\\\\\\\__________\/\\\____/\\\____/\\\__\///____/\\/\\\\\\________/\\\\\____     
    _\/\\\\\\\\\\\\\\\__\/\\\/////\\\____/\\\\\\\\\___\/\\\___\/\\\___/\\\__\/\\\////\\\_____/\\\///\\\__    
     _\/\\\/////////\\\__\/\\\___\///____/\\\////\\\___\/\\\___\/\\\__\/\\\__\/\\\__\//\\\___/\\\__\//\\\_   
      _\/\\\_______\/\\\__\/\\\__________\/\\\__\/\\\___\/\\\___\/\\\__\/\\\__\/\\\___\/\\\__\//\\\__/\\\__  
       _\/\\\_______\/\\\__\/\\\__________\//\\\\\\\/\\__\//\\\\\\\\\___\/\\\__\/\\\___\/\\\___\///\\\\\/___ 
        _\///________\///___\///____________\///////\//____\/////////____\///___\///____\///______\/////_____


*/

long 		Distance, // => distance between car and object
			duration; // -> bounce back time when soundwave is hitting an object
const int 	pingPin = 7, // pin7 for sensor
			ledPIN = 13; // onboard LED pin
short int 	i = 0,
			RandomDirection; // random direction


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
	srand ( time(NULL) );
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
	choose a random direction by rolling a dice:
		0 = turn left
		1 = turn right
	
	this will make the robot more advanced instead of
	keep turning in one direction whenever hit an object
	*/
	RandomDirection = rand() % 2;

	
	/*
	when sensor picks up something, fix motor speed & direction

	An obstacle is:
		3 ft away from robot, slow down (about 40% speed) and make a turn
		1 ft away from robot, stop immediately, then make a turn
		3+ ft away from robot, move forward at full speed

	Controlling Speed by passing parameters into function:
	We give the code a simple number 1, 2 and 3.
		At 1, car moves at slow speed
		At 2, car stop
		At 3, car moves at full speed
	*/
	if ( Distance <= 90 ) // ~3 ft
	{
		// CarSpeed(speed, direction);
		CarSpeed(1, RandomDirection);
	}
	else if ( Distance < 30 ) // ~1 ft
	{
		CarSpeed(2, RandomDirection);
	}
	else
	{
		CarSpeed(3, RandomDirection);
	}
}

/* -------------------------------------

Other Functions to be called in the Main Loop

---------------------------------------- */

// Control car speed
void CarSpeed(int speed, int RandomDirection){
	
	/*
		grabs the parameters from function
		set 1 to pin#5
		set 2 to pin#6
	*/
	int RandomDirection;
	if ( RandomDirection = 1 ) 
	{
		randomMotorPin = 5;
	}
	else if
	{
		randomMotorPin = 6;
	}

	/*
		Control Car
	*/
	if ( speed = 1 )
	{
		blink(ledPIN, 5, 500); // blink onboard LED 5x in 500 ms

		// set both motor at slower speed
		analogWrite(5, 180);
		analogWrite(6, 180);
		// wait 800ms
		delay(800);
		// a random motor will speed up
		analogWrite(randomMotorPin, 255);

		// about 600ms, 
		delay(600);
		// call function: move forward
		MoveCarForward();
	}
	else if ( speed = 2 )
	{
		blink(ledPIN, 10, 500); // blink LED 10x in 500 ms

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
		// full speed manually
		analogWrite(5, 255);
		analogWrite(6, 255);
	}
}

// Reverse motor
void ReserveCar() {
	/*	use H-Bridge for moving forward/backward
		simply pass voltage to:
			pin1
			pin2
			pin3
			pin4
		need 4 pins for 2 motors
	*/
	digitalWrite( hBridgePin1, HIGH );
	digitalWrite( hBridgePin2, LOW);

	/***********************************

		warning	: h-bridge pins havent decided yet...

	***********************************/
}

// Making this a function for easier control...
void MoveCarForward() {
	analogWrite(5, 255);
	analogWrite(6, 255);
}

/*
   Blink onboard LED when picks up an object from sensor
*/
void blink(int whatPin, int howManyTimes, int milliSecs) {
	for ( i = 0; i < howManyTimes; i++) {
		digitalWrite(whatPin, HIGH);
		delay(milliSecs/2);
		digitalWrite(whatPin, LOW);
		delay(milliSecs/2);
	}
}

// convert distance from sensor to centermeter
// taken from arduino examples
long microsecondsToCentimeters (long microseconds) {
	return microseconds / 29 / 2;
}

