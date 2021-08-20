# Advanced RPI4 Weather Station 

Built upon an array of 6-ultrasonic’s facing each other in 3-dimentions as an
anenometer, A DHT22 for air temperature & humidity, soil sensor, and other add-ons available according to your application,the device is powered by solar energy to make it fully autonomous as it is built to act as a local very accurate weather station for precision agricultural application , the device relays it's data to FarmOS instance either on web or locally hosted on the RPI .
This Product is the first of Farmtopia IOF Line and it's opensourced to support GODAN mission for easy & open agriculutral data 
it can work both stationary and mobile and can be easy replicated at home as described here 
## Measured Data
Measured Data| How
------------ | -------------
Wind speed & frequency in 3-dimentional direction | By calculating Ultrasonic error
Temperature & humidity | Am2301 Sensor
Soil Mositure | Resistive soil sensor

## Needed Hardware
Number | Device
------------ | -------------
1 | Raspberry pi 4 , 8GB version 
1 | SD Card 128	
1 | Touch Screen	(Optinal)
1 | Raspberry pi Pinoir 2 Camera (Optinal)	
1 | Arduino Mega 2560
6 | JSNR04T Ultrasonics (Placed 40 Cm Apart)
1 | AM2301 tempuerature& humidity sensor
1 | Soil Sensor
1 | RPI Power Pack
1 | MPPT Solar Charger
1 | battery 
1 | 30 Watt Solar Cell
1 | 3D printed or Stanlesteel enclosure 

////

## Repostory content
//
## Pi Setup & dependencies 
Prerequisites
Configuring 
Prepare the software
Available Modules:
Running :
Why Weather Station as a library:
## Install & Configure Arduino 
## Functional Weather Library
//code documentation 
Name	Type	Description 
Wind_auto.c/h	Functional Class	Provides the needed classes and functions as an abstraction layer  (HAL/SAS) for the application
Arduino_weather.ino	Application file	Uses the objects and methods to run the weather sensing program and aggregate the data to the rpi as a log
Main_debug.	Debug & test functions	Various implementation of test cases to debug sensors/functions 

Return Type	Input Type	Name	Description
1	Construction 	(uint8_t EnPin, uint8_t RXpin, uint8_t type, uint16_t max_range)	JSNR04T	
2	void 	void 	begin	
3	void 	void 	virtual_trigger	
4	void 	uint8_t timeout	resetTimeout	
5	void 	void 	normalize	
6	int	void	readJSNR04TSerial	
7	uint16_t	void	get_selfecho	
8	int	void	get_selfwindspeed	
9	float	uint16_t x	transform_read	
#	Return Type	Input Type	Name	Description
1	Construction 	(uint8_t EnPin, uint8_t RXpin, uint8_t type, uint16_t max_range)	JSNR04T	Constructs a new object of type JSNR0RT that behaves as an instance of ultrasonic driver with EnPin for ground enable , RXpin for echo & type for operation type
2	void 	void 	begin	Enables (triggers) the ultrasonic then identifies & start a new serial communication with it.
3	void 	void 	virtual_trigger	Set the ground pin for the ultrasonic to low so it starts it’s normal operation
4	void 	uint8_t timeout	resetTimeout	Change the millisecond timeout of the ultrasonic measuring to change the range 
5	void 	void 	normalize	Remeasure distance between two ultrasonics in no wind condition to update Nowind_distance
6	int	void	readJSNR04TSerial	Refer to JSNR04T datasheet for operation mode , reads the serial echo output of the ultrasonic and transforms it int / nan in case of invalid reading 
7	uint16_t	void	get_selfecho	Resets timeout to change the range so the sensor only reads it’s echo 
8	int	void	get_selfwindspeed	
9	float	uint16_t x	transform_read	Transforms the measured distance with ultrasonic from mm to wind speed ( relative to sound speed)  
//code documentation end
# Extras 
## Installing FarmOS on Docker_PI=


Install the following libraries with your Arduino Library Manager in Sketch > Include Library > Manage Libraries...
/


## Planned upgrades :

## License :
