![](https://github.com/Amr-MKamal/Arduino_Ultrasonic_Anenometer/blob/main/farmtopia-logo.png)
# Advanced RPI4 Weather Station 
This project aims to build an independent agricultural weather solar powered station for precision agricultural application 
The device is based on raspberry pi & Arduino with ultrasonic anemometer and resistive soil sensor and DHT22 for air temperature & humidity
and other add-ons available according to your application or specific weather needs, the data and analytic information are sent as JSON packages to FarmOS that is either locally hosted or on hosting service (requires 4G usb dongle), FarmOS helps you manage big sensor data easily while monitoring all farm sensors and reports in one platform, it can also act as DaaS for other application.
This Product is the first of Farmtopia IOF(Internet Of Farm) Line and it's opensourced to support GODAN mission for easy & open agricultural data 
it can work both stationary and mobile and can be easy replicated at home as described here
## Measured Data
Measured Data| How
------------ | -------------
Wind speed & frequency in 3-dimentional direction | By calculating Ultrasonic error
Air Temperature & humidity | Am2301 Sensor
GPS Location | USB GBS Dongle 
Soil Moisture | Resistive soil sensor
Optional Add-ons | / 
## What you will need
Raspberry Pi set : which is an RP computer with SD preloaded with raspberry OS , and a pinoir camera (optional)
6xUltrasonic Anemometer : placed in perpendicular directions facing each other (X.Y.Z) as a network with different enables or different triggers.
Dongles : GPS Dongle (Optional/you can input GPS coordinate manually) , 4G dongle (Optional) if there is no WiFi coverage
Solar System : a basic 30W solar panel that Charges the Main Super polymer battery via the MPPT solar charger which also powers the UPS battery pack via usb cable which is responsible for powering the raspberry pi which in turns communicates and powers the Arduino via the USB , this configuration aims to stabilize RPI power supply
FarmOS : which is the farming open-source management system that will act as an interface to the system to view and analyze sensors data.
Number | Device
------------ | -------------
1 | Raspberry pi 4 , 8GB version 
1 | SD Card 128	
1 | Arduino Mega 2560
1 | Arduino USB Cable
6 | JSNR04T Ultrasonics (Placed 40 Cm Apart)
1 | AM2301 temperature& humidity sensor
1 | ARDUINO SOIL MOISTURE SENSOR MODULE 
1 | Raspberry Pi 4 Battery Pack UPS
1 | Mini-USB to USB cable
1 | MPPT Solar Charger Controller 20A 12/24VDC with USB output
1 | 12V super polymer Li-ion Battery-6800 mah 
1 | Solar Panel 18V 30W 
1 | Weather Station Frame 3D printed or Stanlesteel enclosure 
### Extras/Optionals 
Number | Device
------------ | -------------
1 | Touch Screen	
1 | Raspberry Pinoir 2 Camera 
1 | Raspberry USB GPS Dongle 
1 | MLX9046 IR Sensor 
### 3D Concept for the frame
![3D Concept for the frame](https://github.com/Amr-MKamal/Arduino_Ultrasonic_Anenometer/blob/main/3D_Concept.jpeg)
## Repository content
File Name | Description 
------------ | -------------
README.md | Project Introduction
Arduino_weather.ino | Main Weather Sensing Arduino Application 
DHT.cpp | DHT Driver & Class functionalites for Am2301
DHT.h |Header File for DHT Class & Function documentation 
Special_Debug_functions.ino | Unit Test Cases as a debug program 
Wind_auto.cpp | Weather measurement functions
Wind_auto.h |Header File for Wind Class & Function documentation 
aggregator.sh | RPI bash script to catch Arduino serial and aggregate JSON package to farmos server

## Pi Setup
-First Install RPI OS(Full Version) on 128GB SD card, it's advised that the SD be as fast as possible to enhance the overall performance of Pi.
If you're using Headless pi , enable SSH on configuration file you can find it in the boot partition
### Prerequisites
-most of this dependencies may be preinstalled however it's good idea to recheck them:
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install libffi-dev libssl-dev
sudo apt install python3-dev
sudo apt-get install -y python3 python3-pip
sudo apt-get install php5 -y
sudo apt install php-gd php-xml php-xmlrpc
sudo apt install mariadb-server
sudo apt-get install apache2 -y
sudo apt-get install gpsd gpsd-clients python-gps
sudo apt-get install arduino
git clone https://github.com/tbird20d/grabserial
```
-Install Docker with CLI
```
sudo curl -sSL https://get.docker.com | sudo sh
sudo pip3 install docker-compose
sudo systemctl enable docker
```
-Install [FarmOS](https://github.com/farmOS) Locally on Docker 
> FarmOS is a web-based application for farm management, planning, and record keeping. It is developed by a community of farmers, developers, researchers, and organizations with the aim of providing a standard platform for agricultural data collection and management.

 We use FarmOS for quickly interfacing with sensors and analyzing their big data 
```
git clone https://github.com/farmOS/farmOS.git
cd farmOS
sudo docker build -t farmos .
sudo docker run -p 80:80 -v ${PWD}/.data/www:/var/www/html farmos
```
You should refer to this [guide](https://farmos.org/development/docker/) on FarmOS official website for more details 
### Configure FarmOS
you can refer to this online [guide](https://www.linode.com/docs/guides/install-farmos/) to help you configure FarmOS installation 
### Add weather station as a sensor on FarmOS
First make sure Sensor Module on FarmOS is enabled , you can enable and add module via the development branch (just really a super user on the local platform), if you're using a hosting service make sure to ask them to enable the sensors module.
### Install & Configure Arduino libraries 
Install the following libraries with your Arduino Library Manager in Sketch > Include Library > Manage Libraries...SoftwareSerial
## Functional Weather Library
### DHT.h/DHT.CPP
you can refer to Adafruit [DHT](https://github.com/adafruit/DHT-sensor-library) library for DHT doucmentation , however for some reason they don't read temperature & humidity together so we will be using dht.read function with data [] buffer in a new function called renew_temp_hu(DHT ,Float* ,Float*).
### Wind_auto.h/Wind_auto.cpp
built on two classes,	JSNR04T which is an interface class that provides an instance of JSNR04T ultrasonic chip in **Auto mode** , with the needed functions to use the device as wind measurement tool by using the divergence in reading ultrasonic measurements with self-corrected sound speed calculated from air temperature & humidity.
and wind class which preforms the mathematical logic on recorded data to output the needed weather details.
Function Name | Input | Return | Description 
------------ | -------------| -------------| -------------
JSNR04T(Constructor)|uint8_t EnPin, uint8_t RXpin, uint8_t type, uint16_t max_range)|void|Constructs a new object of type JSNR0RT that behaves as an instance of ultrasonic driver with EnPin for ground enable , RXpin for echo & type for operation type.
JSNR04T.begin|void|void|Enables (triggers) the ultrasonic then identifies & start a new serial communication with it.
JSNR04T.virtual_trigger|void|void|Set the ground pin for the ultrasonic to low so it starts it’s normal operation.
JSNR04T.resetTimeout|uint8_t timeout|void|Change the millisecond timeout of the ultrasonic measuring to change the range.
JSNR04T.normalize|void|void|Remeasure distance between two ultrasonics in no wind condition to update Nowind_distance.
JSNR04T.readJSNR04TSerial|void|int|reads the serial echo output of the ultrasonic and transforms it to int/nan in case of invalid reading.
JSNR04T.get_selfecho|void|uint16_t|Resets timeout to change the range so the sensor only reads it’s echo. 
JSNR04T.get_selfwindspeed|void|int| reads the time needed for an ultrasonic to read it's own echo(round trip) and transforms it to windspeed.
JSNR04T.transform_read|uint16_t x|float|	Transforms the measured distance with ultrasonic from mm to wind speed ( relative to sound speed).  
Wind(Constructor)|JSNR04T* ,JSNR04T* |void| Constructs an object of type wind which uses a pair of ultrasonic to measure the wind speed between them.
Wind.update|void|void|Update class values of wind speeds by taking a new read , also calculates the rate of change in windspeed.
Wind.get_avergewind|void|float|Calculates the average of 4 measurements between the ultrasonic pair according to working mode.
Wind.get_echofromahead|void|uint16_t|Reads the echo of the facing sensor.
renew_temp_hu|DHT ,float* temp ,float* hum|void|updates the value of temperature and humidity for a given DHT sensor
get_speedofsound|float Tc,float RH|float|estimates speed of sound in a given air temperature and humidity according to
set_windsensor|DHT|void|passes the pointer of the DHT to wind class 
get_echofromahead|JSNR04T u1 ,JSNR04T u2|int|an indpedandt function to also read the echo of the facing sensor( for testing ).
wind_cycle| Wind* WindX ,Wind* WindY ,Wind* WindZ|void|calculates and updates the windspeed and average (50 measurement average) wind speed of 3 wind objects representing the wind in 3D.
### Usage Examples :

define the needed pin values & configuration , construct the cycle objects according to pin configuration & sensors type , identify cycle variables

```
#define DHTPIN 53
#define mutual 0
#define soil_analog A0
#define soil_max 550
#define soil_min 10
#define Cycle_offset 10
#define DHTTYPE DHT21  
DHT dht(DHTPIN, DHTTYPE);
JSNR04T Ux1(45,10,mutual,2000) ,Ux2(37,13,mutual,2000),Uy1(47,50,mutual,2000),Uy2(31,10,mutual,2000) ,Uz1(41,12,mutual,2000),Uz2(39,11,mutual,2000);
Wind WindX(&Ux1,&Ux2), WindY(&Uy1,&Uy2) ,WindZ(&Uz1,&Uz2);
float CycTemp , CycHum , _CSS=340 , winspeed;
```
Call wind_cycle to update all values 
```
 wind_cycle(&WindX ,&WindY, &WindZ);
```
or just call Wind.update to update instantaneous speed of any dimension 
```
 Windx.update();
```
 print the values to serial port as JSON.
 > "parameter":"value",

```
Serial.print("\"Wind_Speed_x\": ");Serial.print("\"");Serial.print(WindX.avgwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Maximum_Speed_x\": ");Serial.print("\"");Serial.print(WindX.maxwind);Serial.print(" , ");
Serial.print("\"Minmimum_Speed_x\": ");Serial.print("\"");Serial.print(WindX.minwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_frequencyofchange_x\": ");Serial.print("\"");Serial.print(WindX.gust);Serial.print("\"");Serial.print(" , ");
```
use allmiss to adapt cycle delay to measurement errors as following

```
cycledelay=19000; // or as you preferred settings depending on power consumption 
allmiss=(WindX._selfmiss+WindY._selfmiss+WindZ._selfmiss)*selfecho_timeout;  // adobt self cycle delay into main delay 
allmiss+=(WindX._aheadmiss+WindY._aheadmiss+WindZ._aheadmiss)*headecho_timeout;
allmiss+= _tempmiss;
_tempmiss=0;
cycledelay-=allmiss;
delay(cycledelay);
```
use the special_debug_functions.ino to diagnose the application with stepped unit tests.

```
  if(dht.working) //doesn't update before 2 seconds
   delay(10);
 ultradis=Uz1.get_selfecho();
 Serial.print("ultrasonic z1 is ");Serial.println(ultradis);
 winspeed=Uz1.transform_read(ultradis);
 Serial.print("ultrasonic z1 windspeed  "); Serial.println(winspeed);
 ultradis=Uz2.get_selfecho();
 Serial.print("ultrasonic z2 is ");Serial.println(ultradis);
 winspeed=Uz2.transform_read(ultradis);
 Serial.print("average is");Serial.println(winspeed);
 delay(1000);
winspeed=WindZ.get_avergewind();
Serial.print("average wind is ");Serial.println(winspeed);
wind_cycle(&WindX ,&WindY, &WindZ);
allmiss=(WindX._selfmiss+WindY._selfmiss+WindZ._selfmiss)*selfecho_timeout;
allmiss+=(WindX._aheadmiss+WindY._aheadmiss+WindZ._aheadmiss)*headecho_timeout;
allmiss+= _tempmiss;
//build the diagnostic or unit test according to your needs
```
###Timing 
the cron job activates the script every 10 minutes , the script Use grabserial to catch arduino serial for 30 seconds and restarts the count when it catches the JSON packet bracket and quit when the close bracket is seen while it takes the arduino 10 seconds (100 sample average) to record new readings, the cycle limit can be adopted by reducing the sampling rate.
script usage ( replace !public_key & !private_key with your sensor configuration
  ```
python3 /home/pi/grabserial/grabserial -d /dev/ttyACM0 -b 9600  -o /home/pi/serialtest.json  -e  30 -m "^{.*" -q "}"
curl -H "Content-Type: application/json" -X POST -d "@/home/pi/serialtest.json"  https://farmtopia.farmos.net/farm/sensor/listener/!public_key?private_key=!private_key --verbose
 ```
## Farmtopia Disclaimer :
This opensource project and all of it's components are the sole responsibility of it's developer, and although Farmtopia uses similar devices to build the commercial version of this weather station it doesn't necessarily use the same sourcecode or logic or hardware components nor it's responsible for the validity or the application of this opensource project . 
## License : [](https://github.com/Amr-MKamal/Arduino_Ultrasonic_Anenometer/blob/main/LICENSE) MIT License 
## Planned upgrades :
- [x] Project Pilot
- [ ] Replace Arduino Mega with MKR1310
- [ ] Use FireBase as a backup for sensors data
- [ ] Implement Evapotranspiration module
