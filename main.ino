/*
    Author: Wai Tsang & William Wong

    Description: Arduino for EMT2461 project

    License: WTFPL (http://sam.zoy.org/wtfpl/) 

*/

long        Distance[2],        // distance per sensor
            duration;           // soundwave travel time for calculation

const int   ledPIN = 13;        // onboard LED pin

unsigned short int   i = 0,     // for loop counter, starts at zero
            RandomDirection,    // random direction
            randomMotorPin,     // a random motor pin
            hBridgePin1 = 12,
            hBridgePin2 = 13,
            motorPin1 = 3,
            motorPin2 = 11,
            SonarSensorPins[2] = { 7, 8 };      // Sensors are using pin#7 and 8


void setup() {
    // initialize serial communication:
    Serial.begin(9600);

    /*
        pinMode();
        ref: http://www.arduino.cc/playground/Interfacing/Processing
    */
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(hBridgePin1, OUTPUT);
    pinMode(hBridgePin2, OUTPUT);
    pinMode(ledPIN, OUTPUT);

    /*
        initialize random seed
        http://arduino.cc/en/Reference/RandomSeed
    */
    randomSeed(analogRead(0));
}

void loop() {
    // H-Bridge default setting (moving forward)
    digitalWrite( hBridgePin1, LOW );
    digitalWrite( hBridgePin2, HIGH );
    /************************************************************
        randomly generate a number from zero to one
            0 = left
            1 = right
        ref: http://arduino.cc/en/Reference/random
    */
    RandomDirection = random(2);
    
    /************************************************************
        generate a random for turing left/right randomly
        1        pin#5
        2        pin#6
    */
    if ( RandomDirection == 1 ) {
        randomMotorPin = motorPin1;
    }
    else {
        randomMotorPin = motorPin2;
    }

    /************************************************************
        Gets the distance value when sensors are picking up
        obstacles in their ways
        1 = left
        2 = right
    */
    ObstacleDetection(1);
    ObstacleDetection(2);


    /************************************************************
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

    if ( Distance[1] <= 100 || Distance[2] <= 100 ) // ~3 ft
    {
        // blink onboard LED every 100ms
        blinkBoardLED(1, 100); 
        // PWM: 60%
        analogWrite( motorPin1, 153 );
        analogWrite( motorPin2, 153 );
        // wait 800ms
        delay(800);
        // speed up a random motor
        analogWrite( randomMotorPin, 255 );
        // wait 600ms 
        delay(600);
        // mvoes forward
        ForwardCar(0);
    }
    else if ( Distance[1] <= 30 ||  Distance[2] <= 30 ) // ~1 ft
    {
        // blink LED every 250ms
        blinkBoardLED(1, 250); 
        /*
            reverse H-Bridge to move backward

            H-Bridge ref
            Function    PinA    PinB
            --------    ----    ----
            direction   12      13
            speed       3       11
            brake       9       8
        */
        ForwardCar(1);
        delay(800);
        // switch H-Bridge back to normal, robot moves forward
        ForwardCar(0);
    }
    else
    {
        // LED off
        blinkBoardLED(0, 0); 
        ForwardCar(0);
    }
}

// Controls robots to move forward or even backward
// using a parameter to switch H-Bridge
void ForwardCar( int reverseBridge ) {
    if ( reverseBridge == 1 ) {
        /*
            1. stop motors
            2. switch bridge
            3. motors moves again
        */
        analogWrite( motorPin1, 0 );
        analogWrite( motorPin2, 0 );
        digitalWrite( hBridgePin1, HIGH );
        digitalWrite( hBridgePin2, LOW );
    }
    else {
        digitalWrite( hBridgePin1, LOW );
        digitalWrite( hBridgePin2, HIGH );
    }
    // PWM: 80%
    analogWrite( motorPin1, 204 );
    analogWrite( motorPin2, 204 );
}

/*
   Lights up the onboard LED and blink (optional)

   fast blinking    = car is about to hit object
   slow blinking    = something is detected
   lights off       = nothing is detected
*/
void blinkBoardLED( int LED_Switch, int blinkDelayTime ) {
    if ( LED_Switch == 1 ) {
        digitalWrite(ledPIN, HIGH); // lights up
        delay(blinkDelayTime);
        digitalWrite(ledPIN, LOW); // lights out
        delay(blinkDelayTime);
    }
    else {
        digitalWrite(ledPIN, LOW); // lights out
    }
}

long ObstacleDetection( int SensorPin ) { 
    // following codes are for Sonar Sensor
    // taken from arduino example
    pinMode(SonarSensorPins[SensorPin], OUTPUT);
    digitalWrite(SonarSensorPins[SensorPin], LOW);
    delayMicroseconds(2);
    digitalWrite(SonarSensorPins[SensorPin], HIGH);
    delayMicroseconds(5);
    digitalWrite(SonarSensorPins[SensorPin], LOW);
    pinMode(SonarSensorPins[SensorPin], INPUT);
    duration = pulseIn(SonarSensorPins[SensorPin], HIGH);
    return Distance[SensorPin] = duration / 29 / 2; // convert distance to centimeters
}