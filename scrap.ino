setup(){ ... }
loop() {
	// get random pin for motor
	if ( direction = 0 ) {
		RandomMotorPin = 5; /*left motor*/ 
	}
	else {
		RandomMotorPin = 6; /*right motor*/ 
	}
	// fix car speed
	if( distance < 30 ) { // 30 cm
		ReverseCar( RandomMotorPin );
	}
	else if ( distance < 100 ) { // 100 cm
		SlowDown( RandomMotorPin );
	}
	else {
		ForwardCar();
	}
}

void SlowDown( int RandomMotorPin ) {
	analogWrite(LeftMotorPin, 150);
	analogWrite(RightMotorPin, 150);
	delay(600);
	analogWrite(RandomMotorPin, 255);
	delay(1200);
	ForwardCar();
}
void ReverseCar(int RandomMotorPin) {
	// reverse current flow on H-Bridge
	digitalWrite(hBridgePin1, HIGH);
	digitalWrite(hBridgePin2, LOW);
	delay(600);
	digitalWrite(hBridgePin2, HIGH);
	digitalWrite(hBridgePin1, LOW);
	analogWrite(RandomMotorPin,255);
	delay(1200);
	ForwardCar();
}

void ForwardCar() {
	digitalWrite(LeftMotorPin, HIGH);
	digitalWrite(RightMotorPin, HIGH);
}