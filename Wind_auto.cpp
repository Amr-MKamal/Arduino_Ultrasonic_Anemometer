#include "Wind_auto.h"
// construction function for JSNR04T ultrasonic type
JSNR04T::JSNR04T(uint8_t pin, uint8_t RXpin, uint8_t type, uint8_t count , uint8_t max_range) {
  _EnPin = EnPin; //enable pin
  _RXpin = RXpin; //rx pin
  _max_range = max_range; //converted to set serial time out
 //  _selfwindspeed from self calbiration 
  _type = type; //mode modes are one enable with multiple returns on different rx's or different enables 10ms delay with different rx's
  _count = count; //ic
  firstreading = true;
}

//start the module
void JSNR04T::begin(void) {
  // set up the pins!
  pinMode(_EnPin, OUTPUT);
  SoftwareSerial windSerial(_RXpin, commonTx); // RX, TX is not needed as ultrasonic triggers itself
  digitalWrite(_EnPin, LOW); //enable the module
  _timeout=_max_range; //convert max range to timeout according to sound speed equation
  windSerial.begin(9600);
}
//change timeout setter ( to change maximum range (to change maximum measuered speed of wind)
void JSNR04T::resetTimeout(uint8_t timeout){_timeout=timeout;}
int JSNR04T::readJSNR04TSerial(void){
byte serialData[5];
byte serial_sum;
int discalc , d ;
while (windSerial.available()) {byte b = windSerial[id].read();}
windSerial.setTimeout(_timeout); //timeout should be 0.67 for the first wave with 3.33 serial delay
  if ( windSerial.readBytes(serialData, 4) > 0) {
    serial_sum=serialData[0]+serialData[1]+serialData[2];
    if(serialData[3]==serial_sum){
    discalc = ((serialData[1] * 256) + serialData[2]);
    discalc = (discalc * 1);  //distance is returned from sensor in mm 
    }else {discalc=-1;}
  }
return discalc;
}
//function to calculate wind speed in a round trip as self calibration 
int JSNR04T::get_selfwindspeed(void){
  //get averge of 10 reads 
}
int JSNR04T::get_selfecho(void){
  
}
//function to the echo from the facing sensor
int JSNR04T::get_echo(uint8_t id){
////enable x1 and x2
////
}
//encapsulation 
float get_temp_from_sensor(DHT _dht){ return _dht.readHumidity();}
float get_humidity_from_sensor(DHT _dht){ return _dht.readTemperature();}
  
int get_speedofsound(uint8_t id){
  
}
