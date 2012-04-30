## Read Me

This is my EMT (System Interface) project using [Arduino](http://www.arduino.cc/) [Uno Board](http://arduino.cc/en/Main/arduinoBoardUno).

The robotic car will move forward in a straight line and
to avoid obstacles by using Sonar/Infrared/Laser Sensor.

Additionally, we might use `Optical Encoders` to balance both motors' speed.


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


## Change Log

### April 30, 2012

* REMOVE: ForwardCar() function
* CHANGE: revise most codes from functions into `loop()`
* CHANGE: revise variables declaration

### April 18, 2012

* ADD: sensor detection function and return `Distance` back in an array
* CHANGE: Reduce PWM in all analogWrite()
* CHANGE: uses motor pin variables instead of pin numbers
* REMOVE: Optiocal Encoders are nolonger in the project
* REMOVE: `CarSpeed()` and `ReverseCar()` are now integrated into the loop()


### April 13, 2012

* update coding for H-Bridge

### April 12, 2012

* add License

## License   

### Everything:

* [WTFPL](http://sam.zoy.org/wtfpl/)
