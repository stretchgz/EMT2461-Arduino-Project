/*
    Author: Wai Tsang & William Wong
 
 Description: Arduino for EMT2461 project
 
 License: WTFPL (http://sam.zoy.org/wtfpl/) 
 
 */

long Distance[2],        // distance per sensor
duration[2];           // soundwave travel time for calculation

const int motorRightPin1 = 3,
motorRightPin2 = 11,
motorLeftPin1 = 9,
motorLeftPin2 = 10,
enableBridgeLeft = 7,
enableBridgeRight = 8;

unsigned short int  RandomDirection,    // random direction
i = 0,              // for loop counter
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

    /*
    returns
       Distance[0]
       Distance[1]
    */
  ObstacleDetection(0);
  ObstacleDetection(1);
  /* debug */
  Serial.print("Distance[0] Sensor is: \t");
  Serial.print( Distance[0]);
  Serial.println("cm");
  Serial.print("Distance[1] Sensor is: \t");
  Serial.print( Distance[1]);
  Serial.println("cm");
  /* debug ends */


  if ( Distance[0] <= 30 ||  Distance[1] <= 30 ) // ~1 ft
  {
    /* 
     reverse 
     */
    analogWrite( motorLeftPin1, 0 );
    analogWrite( motorLeftPin2, 153 );
    analogWrite( motorRightPin1, 0 );
    analogWrite( motorRightPin2, 153 );
    /* debug */    Serial.println("Reversing robot for 3sec...");
    delay(3000);
    /* 
     forward 
     */
    analogWrite( motorLeftPin1, 153 );
    analogWrite( motorLeftPin2, 0 );
    analogWrite( motorRightPin1, 153 );
    analogWrite( motorRightPin2, 0 );
    /* debug */    Serial.println(">>> Forward Again <<<");
  }
  else if ( Distance[0] < 100 || Distance[1] < 100 ) // ~3 ft
  {
    /*
         generate a number from zero to one
     ref: http://arduino.cc/en/Reference/random
     */
    RandomDirection = random(2);
    Serial.print("------------------------- \n Random number is: ");
    Serial.println(RandomDirection);
    Serial.print("------------------------- \n");

    if ( RandomDirection == 0 ) {
      /* debug */      Serial.println("Turning Right!");
      analogWrite( motorLeftPin1, 230 );
      analogWrite( motorRightPin1, 0 );
    }
    else {
      /* debug */      Serial.println("Turing Left!");
      analogWrite( motorRightPin1, 230 );
      analogWrite( motorLeftPin1, 0 );
    }
    analogWrite( motorLeftPin2, 0 );
    analogWrite( motorRightPin2, 0 );
    delay(1000);
    // mvoes forward
    analogWrite( motorLeftPin1, 153 );
    analogWrite( motorRightPin1, 153 );
  }
  else
  {
    /* debug */    Serial.println("Nothing is in my way. Moving at 70%!");
    analogWrite( motorLeftPin1, 180 );
    analogWrite( motorLeftPin2, 0 );
    analogWrite( motorRightPin1, 180 );
    analogWrite( motorRightPin2, 0 );
  }

}

long ObstacleDetection( int SensorPin ) { 
  /*
        following codes are for Sonar Sensor
   taken from arduino example
   */
  pinMode(SonarSensorPins[SensorPin], OUTPUT);
  digitalWrite(SonarSensorPins[SensorPin], LOW);
  delayMicroseconds(2);
  digitalWrite(SonarSensorPins[SensorPin], HIGH);
  delayMicroseconds(5);
  digitalWrite(SonarSensorPins[SensorPin], LOW);
  pinMode(SonarSensorPins[SensorPin], INPUT);
  duration[SensorPin] = pulseIn(SonarSensorPins[SensorPin], HIGH);
  // convert distance to centimeter units
  return Distance[SensorPin] = duration[SensorPin] / 29 / 2; 
}
