# Advanced RPI4 Weather Station 
This project  aims to build  an independent agricultural weather solar powered station for precision agricultural application 
The device is based on raspberry pi & Arduino with ultrasonic anemometer and resistive soil sensor and DHT22 for air temperature & humidity
and other add-ons available according to your application,the data and analytic information are sent to FarmOS that is either locally hosted or on hosting service (requires 4G usb dongle ).
, FarmOS helps you manage big sensor data easliy while monitring all farm sensors and reports in one platform 
while it can act as DaaS for other application
This Product is the first of Farmtopia IOF Line and it's opensourced to support GODAN mission for easy & open agriculutral data 
it can work both stationary and mobile and can be easy replicated at home as described here 
## Measured Data
Measured Data| How
------------ | -------------
Wind speed & frequency in 3-dimentional direction | By calculating Ultrasonic error
Air Temperature & humidity | Am2301 Sensor
GPS Location | USB GBS Dongle 
Soil Mositure | Resistive soil sensor

## What you will need
Raspberry Pi set : which is an RP computer with SD preloaded with raspberry OS , and a pinoir camera (optional )
6xUltrasonic Anemometer : placed in perpendicular directions facing each other (X.Y.Z) as a network with different enables or different triggers.
Dongles : USB Soil EC sensor, GPS Dongle (optionally/ input GPS coordinate manually) , 4G dongle (optionally)
Solar System : a basic 30W solar panel that Charges the Main Super ploymer battery via the MPPT solar charger which also powers the UPS battery pack via usb cable which is responsible for powering the raspberry pi which in turns communicates and powers the Arduino via the USB , this configuration aims to stablize RPI power supply
FarmOS : which is the farming open-source management system that will act as an interface to the system to view and analyzie sensors data  .

Number | Device
------------ | -------------
1 | Raspberry pi 4 , 8GB version 
1 | SD Card 128	
1 | Touch Screen	(Optinal)
1 | Raspberry Pinoir 2 Camera (Optinal)	
1 | Raspberry USB GPS Dongle (Optinal)	
1 | Arduino Mega 2560
1 | Arduino USB Cable
6 | JSNR04T Ultrasonics (Placed 40 Cm Apart)
1 | AM2301 tempuerature& humidity sensor
1 | ARDUINO SOIL MOISTURE SENSOR MODULE 
1 | Raspberry Pi 4 Battery Pack UPS
1 | Mini-USB to USB cable
1 | MPPT Solar Charger Controller 20A 12/24VDC with USB output
1 | 12V super polymer Li-ion Battery-6800 mah 
1 | Solar Panel 18V 30W 
1 | Weather Station Frame 3D printed or Stanlesteel enclosure 

3D Conecpt for the frame

## Repostory content
File Name | Descirbtion 
------------ | -------------
README.md | Project Introduction
Arduino_weather.ino | Main Weather Sensing Arudino Application 
DHT.cpp | DHT Driver & Class functionalites for Am2301
DHT.h |Header File for DHT Class & Function documentation 
Special_Debug_functions.ino | Unit Test Cases as a debug program 
Wind_auto.cpp | Weather measurement functions
Wind_auto.h |Header File for Wind Class & Function documentation 
aggregator.sh | RPI bash script to catch arduino serial and aggregate json package


## Pi Setup
### Software Dependencies   
-First Install RPI OS on 128GB SD

### Prerequisites
-most of this dependencies may be preinstalled however it's good idea to recheck them 
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install libffi-dev libssl-dev
sudo apt install python3-dev
sudo apt-get install -y python3 python3-pip
sudo apt-get install php5 -y
sudo apt install mariadb-server
sudo apt-get install apache2 -y
sudo apt-get install gpsd gpsd-clients python-gps
sudo apt-get install arduino
```
-Install Docker with CLI
```
sudo curl -sSL https://get.docker.com | sudo sh
sudo pip3 install docker-compose
sudo systemctl enable docker
```
-Install FarmOS Locally on Docker 
[FarmOS](https://github.com/farmOS) 
> is a web-based application for farm management, planning, and record keeping. It is developed by a community of farmers, developers, researchers, and organizations with the aim of providing a standard platform for agricultural data collection and management
We use FarmOS for quickly interfacing with sensors and analyzing their big data 
```
git clone https://github.com/farmOS/farmOS.git
cd farmOS
sudo docker build -t farmos .
sudo docker run -p 80:80 -v ${PWD}/.data/www:/var/www/html farmos
```
You should refer to this [guide](https://farmos.org/development/docker/) on FarmOS offical website for more details 

### Add weather station as a sensor on FarmOS
First make sure Sensor Module on FarmOS is enabled , you can enable and add module via the development branch 

### Install & Configure Arduino 
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


Install the following libraries with your Arduino Library Manager in Sketch > Include Library > Manage Libraries...
/


## Planned upgrades :

## License :
