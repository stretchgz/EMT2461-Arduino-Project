/*
    Author: Wai Tsang & William Wong

    Description: Arduino for EMT2461 project

    License: WTFPL (http://sam.zoy.org/wtfpl/) 

*/

long        Distance[2],        // distance per sensor
            duration[2];           // soundwave travel time for calculation

const int   motorRightPin1 = 3,
            motorRightPin2 = 11,
            motorLeftPin1 = 9,
            motorLeftPin2 = 10,
            enableBridgeLeft = 7,
            enableBridgeRight = 8;

unsigned short int  RandomDirection,    // random direction
                    randomMotorPin,     // a random motor pin
                    SonarSensorPins[2] = { 2, 4 };      // sensor pins


void setup() {
    // initialize serial communication
    Serial.begin(9600);

    /*
        pinMode();
        ref: http://www.arduino.cc/playground/Interfacing/Processing
    */
    pinMode(motorLeftPin1, OUTPUT);
    pinMode(motorLeftPin2, OUTPUT);
    pinMode(motorRightPin1, OUTPUT);
    pinMode(motorRightPin2, OUTPUT);
    pinMode(enableBridgeLeft, OUTPUT);
    pinMode(enableBridgeRight, OUTPUT);


    // initialize both H-Bridge
    digitalWrite(enableBridgeLeft, HIGH);
    digitalWrite(enableBridgeRight, HIGH);   
    /*
        initialize random seed
        http://arduino.cc/en/Reference/RandomSeed
    */
    randomSeed(analogRead(0));
}

void loop() {

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
        randomMotorPin = motorLeftPin1;
    }
    else {
        randomMotorPin = motorRightPin1;
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

        // PWM: 60%
        analogWrite( motorLeftPin1, 153 );
        analogWrite( motorLeftPin2, 0 );
        analogWrite( motorRightPin1, 153 );
        analogWrite( motorRightPin2, 0 );
        // wait 800ms
        delay(800);
        // speed up a random motor
        analogWrite( randomMotorPin, 255 );
        // wait 600ms 
        delay(600);
        // mvoes forward
        analogWrite( motorLeftPin1, 153 );
        analogWrite( motorLeftPin2, 0 );
        analogWrite( motorRightPin1, 153 );
        analogWrite( motorRightPin2, 0 );
    }
    else if ( Distance[1] <= 30 ||  Distance[2] <= 30 ) // ~1 ft
    {
        /* reverse */
        analogWrite( motorLeftPin1, 0 );
        analogWrite( motorLeftPin2, 153 );
        analogWrite( motorRightPin1, 0 );
        analogWrite( motorRightPin2, 153 );
        delay(1000);
        /* forward */
        analogWrite( motorLeftPin1, 153 );
        analogWrite( motorLeftPin2, 0 );
        analogWrite( motorRightPin1, 153 );
        analogWrite( motorRightPin2, 0 );
    }
    else
    {
        analogWrite( motorLeftPin1, 200 );
        analogWrite( motorLeftPin2, 0 );
        analogWrite( motorRightPin1, 200 );
        analogWrite( motorRightPin2, 0 );
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
    duration[SensorPin] = pulseIn(SonarSensorPins[SensorPin], HIGH);
    return Distance[SensorPin] = duration[SensorPin] / 29 / 2; // convert distance to centimeters
}
