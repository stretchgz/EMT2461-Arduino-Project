/*
  Author: Wai Tsang & William Wong
 
  Description: Arduino for EMT2461 project
 
  License: WTFPL (http://sam.zoy.org/wtfpl/) 
 
 */
long  Distance[2],    // distance per sensor
      duration[2];    // soundwave travel time for calculation

const int 
// Left Motor
motorLeftPin1 =     9,
motorLeftPin2 =     10,
// Right Motor
motorRightPin1 =    3,
motorRightPin2 =    11,
// H-Bridge enable pins
enableBridgeLeft =  7,
enableBridgeRight = 8,
// 2 SPDT buttons
btn1 = 5,
btn1 = 6;

unsigned short int  SonarSensorPins[2] = { 2, 4 };      // sensor pins

bool btn1Value, btn2Value;

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

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);

  // initialize both H-Bridge
  digitalWrite(enableBridgeLeft, HIGH);
  digitalWrite(enableBridgeRight, HIGH);   

}

void loop() {
  /*
    object detection:
    ObstacleDetection( Sensor#, On/Off )
   */
  ObstacleDetection(0,1);
  ObstacleDetection(1,1);
  /* ObstacleDetection - debug */
  Serial.print("Distance[0] Sensor is: \t");
  Serial.print( Distance[0]);
  Serial.println("cm");
  Serial.print("Distance[1] Sensor is: \t");
  Serial.print( Distance[1]);
  Serial.println("cm");
  /* debug ends */

  // read SPDT buttons state
  btn1Value = digitalRead(btn1);
  btn2Value = digitalRead(btn2);

  // Runs when Distance < 10cm or any SPDT button is touched
  if ( Distance[0] <= 10 || Distance[1] <= 10 || btn1Value == 1 || btn2Value == 1 ) // 10cm
  {
    /* 
      reverse 
    */
    analogWrite( motorLeftPin1, 0 );
    analogWrite( motorLeftPin2, 180 );
    analogWrite( motorRightPin1, 0 );
    analogWrite( motorRightPin2, 180 );
    /* debug */    Serial.println("Reversing robot for 2 sec...");
    
    // Stop Sensors
    ObstacleDetection(0,0);
    ObstacleDetection(1,0);
    // halt 2 sec
    delay(2000);
    // Restart Sensors
    ObstacleDetection(0,1);
    ObstacleDetection(1,1);
  }
  // Runs when 10cm < Distance < 35 cm
  else if ( (Distance[0] > 10 && Distance[0] < 35) || (Distance[1] > 10 && Distance[1] < 35) ) 
  {
    /*
      generate a number from zero to one
      ref: http://arduino.cc/en/Reference/random
    */
    if ( Distance[0] > Distance[1] ) {
      /* debug */      Serial.println("Turning Right!");
      analogWrite( motorLeftPin1, 160 );
      analogWrite( motorLeftPin2, 0 );
      analogWrite( motorRightPin1, 0 );
      analogWrite( motorRightPin2, 120 );
    }
    else 
    {
      /* debug */      Serial.println("Turing Left!");
      analogWrite( motorRightPin1, 160 );
      analogWrite( motorRightPin2, 0 );
      analogWrite( motorLeftPin1, 0 ); 
      analogWrite( motorLeftPin2, 120 );
    }
    // halt 0.5 sec
    delay(500);
    // mvoes forward
    RobotMovesForward();
  }
  else
  {
    /* debug */    Serial.println("Nothing is in my way. Moving at 70%!");
    RobotMovesForward();
  }
}

// robot moves forward at ~50% PWM
void RobotMovesForward() {
  analogWrite( motorLeftPin1, 125 );
  analogWrite( motorLeftPin2, 0 );
  analogWrite( motorRightPin1, 125);
  analogWrite( motorRightPin2, 0 );
}

long ObstacleDetection( int SensorPin, int SenorSwitch ) { 
  // only if parameter is set to one, sensors will do their jobs
  if (SenorSwitch == 1){
    pinMode(SonarSensorPins[SensorPin], OUTPUT);
    digitalWrite(SonarSensorPins[SensorPin], LOW);
    delayMicroseconds(50);
    digitalWrite(SonarSensorPins[SensorPin], HIGH);
    delayMicroseconds(50);
    digitalWrite(SonarSensorPins[SensorPin], LOW);
    pinMode(SonarSensorPins[SensorPin], INPUT);
    duration[SensorPin] = pulseIn(SonarSensorPins[SensorPin], HIGH);
    // convert distance to centimeter units
    // also return Distance[0] and Distance[1] correspondingly
    return Distance[SensorPin] = duration[SensorPin] / 29 / 2;
  } 
}
 