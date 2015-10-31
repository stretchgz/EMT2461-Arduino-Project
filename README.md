## Read Me

This is my EMT (System Interface) project using [Arduino](http://www.arduino.cc/) [Uno Board](http://arduino.cc/en/Main/arduinoBoardUno).

The robotic car will move forward in a straight line and
to avoid obstacles by using Sonar/Infrared/Laser Sensor.

## Parts

Component Name      |   Quantity
---------------     |   ---------  
Arduino Uno         |   1
BreadBoard          |   1-2
Batteries           |   2-4
DC Motor(2)         |   2
Toy wheels          |   4
Sonar Sensor        |   2
H-Bridge            |   1-2

Component Details:

* H-Bridge: TEXAS INSTRUMENTS [L293DNE](http://www.jameco.com/webapp/wcs/stores/servlet/Product_10001_10001_1341966_-1)

## Change Log

### May 13, 2012
* REVISE: optimize SPDT button codes

### May 8, 2012

* Added: 2 touch sensors (any SPDT button will do)
* Removed: random direction and random number generator
* Improved: moving forward codes to a function
* Improved: robot will move right when picks up object from left sensor, vise versa for the other motor

### May 7, 2012

* Add H-Bridge details to README.md
* update the order of IF statements

### April 30, 2012

* Removed: ForwardCar() function
* Improved: revise most codes from functions into `loop()`
* Improved: revise variables declaration

### April 18, 2012

* Added: sensor detection function and return `Distance` back in an array
* Improved: Reduce PWM in all analogWrite()
* Improved: uses motor pin variables instead of pin numbers
* Removed: Optical Encoders are now removed from this project
* Removed: `CarSpeed()` and `ReverseCar()` are now integrated into the loop()

### April 13, 2012

* Added: H-Bridge control

### April 12, 2012

* Added: License

## License   

* [MIT](http://opensource.org/licenses/MIT)
