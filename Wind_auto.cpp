#include "Wind_auto.h"

///get no wind distance
// construction function for JSNR04T ultrasonic object
DHT _lastdht(53, DHT21);
extern float  CycTemp , CycHum ,_CSS ;
float _Cs ;
uint8_t _tempmiss=0;
JSNR04T::JSNR04T(uint8_t EnPin, uint8_t RXpin, uint8_t type, uint16_t max_range) {
  _EnPin = EnPin; //enable pin for ground
  _RXpin = RXpin; //rx pin
  _max_range = max_range; //converted to set serial time out
 //  _selfwindspeed from self calbiration
  _type = type; //mode modes are one enable with multiple returns on different rx's or different enables 10ms delay with different rx's
  working = true;
}
//start the module
void JSNR04T::begin(void) {
  //volatile static SoftwareSerial thi(_RXpin,5); // RX, TX is not needed as ultrasonic triggers itself
  free(windSerial);
  virtual_trigger();
  windSerial=new SoftwareSerial (_RXpin,5);
//  windSerial=&thi;'
  windSerial->begin(9600);
}
void JSNR04T::virtual_trigger(void) {
  // set up the pins!
  pinMode(_EnPin, OUTPUT);
  digitalWrite(_EnPin, LOW); //enable the module
}
void JSNR04T::disable(void){
  // set up the pins!
  pinMode(_EnPin, OUTPUT);
  digitalWrite(_EnPin, HIGH); //disable the module

}
void JSNR04T::normalize(void){
resetTimeout(selfecho_timeout);
begin();
nowind_distance=readJSNR04TSerial();
}
//change timeout setter ( to change maximum range (to change maximum measuered speed of wind)
void JSNR04T::resetTimeout(uint8_t timeout){
  _timeout=timeout;}

int JSNR04T::readJSNR04TSerial(void){
byte serialData[5];
byte serial_sum;
int discalc , d ;
while (windSerial->available()) {byte b = windSerial->read();}
windSerial->setTimeout(_timeout); //timeout should be 0.67 for the first wave with 3.33 serial delay
  if ( windSerial->readBytes(serialData, 4) > 0) {
    serial_sum=serialData[0]+serialData[1]+serialData[2];
    if(serialData[3]==serial_sum){
    discalc = ((serialData[1] * 256) + serialData[2]);
    discalc = (discalc * 2);  //distance is returned from sensor in mm
    }else {discalc=NAN;}
  }
 // if(discalc<2){discalc=NAN;}
//if(isnan(discalc)){return 10;}else return discalc*2;
//disable();

return discalc ;

}
uint16_t JSNR04T::get_selfecho(void){
//  if(!working){return NAN};
  uint16_t val;
  resetTimeout(selfecho_timeout);
  begin();
  val= readJSNR04TSerial();
  //disable();
  return val;
 // if(val){return val;}else{return NAN;}
}

//function to calculate wind speed in a round trip as self calibration
/*int JSNR04T::get_selfwindspeed(void){
  int sound_duration=get_speedofsound()/nowind_distance; //should get nowwind distance from self calibration
  int wind_gust=0, windspeed ,avg=0;
  for(int i=0 ; i<10 ;i++){
    windspeed=(readJSNR04TSerial()-nowind_distance)*sound_duration;
    if(windspeed!=0){
      wind_gust++;
      avg+=windspeed;}
  }
  avg/=wind_gust;
return avg;
}*/
float JSNR04T::transform_read(uint16_t x){
  float delta= 340 * ((float)x/(float)nowind_distance);
  return 340-delta;
}


Wind::Wind(JSNR04T* _u1 ,JSNR04T* _u2){
oldwind=0 ;
_Ud1=_u1;
_Ud2=_u2;
_selfmiss=0;
_aheadmiss=0;
gust=0;
}
float Wind::get_avergewind (void){
  int we ,ws=NAN ,wavg;
  float welf,wself1,wself2;
  //we=get_echofromahead(); while(isnan(we)){we=get_echofromahead();_aheadmiss++;} //error hard handling
  //ws=get_echofromahead();while(isnan(ws)){ws=get_echofromahead();_aheadmiss++;}
  //wavg=(we+ws)/2;
  if(_Ud1->working)
  { wself1=_Ud1->get_selfecho();
  while(isnan(wself1)){wself1=_Ud1->get_selfecho();_selfmiss++;}}
  else {wself1=NAN;}
if(_Ud2->working){
  wself2=_Ud2->get_selfecho();while(isnan(wself2)){wself2=_Ud2->get_selfecho();_selfmiss++;}}
 else {wself2=NAN;}
 // _Ud2->disable();
  if(isnan(wself1)){wself1=0;}else{wself1=_Ud1->transform_read(wself1);}
   if(isnan(wself2)){wself2=0;}else{wself2=_Ud2->transform_read(wself2);}

  welf=(float)(wself1-wself2)/2;
    if(!wself1){ welf=wself2;}
  if(!wself2){ welf=wself1;}
   return  welf;
}
void Wind::update(void){
    float windc,windm,windmin;
   if(newwind<0){windc=-1*newwind;}else{windc=newwind;}
  if(minwind<0){windmin=-1*minwind;}else{windmin=minwind;}
  if(maxwind<0){windm=-1*maxwind;}else{windm=maxwind;}
  newwind=get_avergewind();
  if(newwind!=oldwind){
  if(windc<windmin){minwind=newwind;}
  if(windc>windm){maxwind=newwind;}
    oldwind=newwind;
    avgwind+=oldwind;
    gust++;
    }
}
uint16_t Wind::get_echofromahead(void){
  _Ud1->disable();
  _Ud2->virtual_trigger();
  _Ud1->begin();
  _Ud1->resetTimeout(30); // set the appropiate timeout for the firs readt ( lower then self echo around 4.5-5.5 ms and the next 6)
  delay(10);_Ud2->disable();
  return  _Ud1->readJSNR04TSerial();
}
void wind_cycle(Wind* WindX ,Wind* WindY ,Wind* WindZ ){
  WindX->oldwind=0;
  WindY->oldwind=0;
  WindZ->oldwind=0;
  WindX->avgwind=0;
  WindX->gust=0;
  WindY->avgwind=0;
  WindY->gust=0;
  WindZ->avgwind=0;
  WindZ->gust=0;
  for(int i=0 ; i<50 ; i++){
  _CSS=get_speedofsound(CycTemp,CycHum);
   renew_temp_hu(_lastdht,&CycTemp,&CycHum);
  WindX->update();
  WindY->update();
  WindZ->update();
  delay(180);
  }
WindX->avgwind/=WindX->gust;
WindY->avgwind/=WindY->gust;
WindZ->avgwind/=WindZ->gust;

}
//encapsulation
void set_windsensor(DHT _dht){ //move to debug
    _lastdht=_dht;}
float get_temp_from_sensor(DHT _dht){
    float temp= _dht.readTemperature();
   while (isnan(temp)){temp= _dht.readTemperature();_tempmiss++;delay(270);}
    return temp; //it takes 250 ms to capture one read , and it takes 20 ms to load the read
  }

float get_humidity_from_sensor(DHT _dht){



//  return NAN;
     float temp1= _dht.readHumidity();
    while (isnan(temp1)||(temp1==0)){temp1= _dht.readHumidity();_tempmiss++;delay(270);}
     return temp1;
     }
void renew_temp_hu(DHT _dht,float *temp ,float *hum){
      float h ,t ;
 // while((!_dht.read()) && (_tempmiss<_maximum trials) ){
 //*hum=NAN ;*temp=NAN;_tempmiss++; }
 
  if (_dht.read()) {
      h = _dht.data[0];
      h *= 256;
      h += _dht.data[1];
      h /= 10;
      *hum=h;
      t = _dht.data[2] & 0x7F;
      t *= 256;
      t += _dht.data[3];
      t /= 10;
      if (_dht.data[2] & 0x80) {t *= -1;}
      *temp=t;
      
  } else {*hum=NAN ;*temp=NAN;_tempmiss++;}
  
}
//trigger both ultrasonics , read rx of the first , the values exist in sensor last read
int get_echofromahead (JSNR04T* _u1 ,JSNR04T* _u2){
  _u1->begin();
  _u1->resetTimeout(headecho_timeout); // set the appropiate timeout for the firs readt ( lower then self echo around 4.5-5.5 ms and the next 6)
  _u2->virtual_trigger();
  return  _u1->readJSNR04TSerial();
}
float get_speedofsound(float Tc,float RH){
  //equation from : Effects of environment on accuracy of ultrasonic sensor operates in millimetre range ,Kirtan Gopal Panda, Deepak Agrawal, Arcade Nshimiyimana, Ashraf Hossain (Science Direct)
  double Ef ,Ec ,cs;
  if ( Tc==RH ) { _Cs=340;return 340 ;}
  else{Ec=pow(10,(0.032*(Tc-(0.004*Tc*Tc))));
  Ef=(9.604*pow(10,-6)*RH*Ec)+1;
  cs=(331.296 +0.606*Tc)*Ef;
  _Cs=cs;
  if(_Cs) {return 340;}
  return _Cs ;}
}


////receive serial commands from rpi python ( postponed as a service layer for wind_nonauto
/*
import serial

ser = serial.Serial('/dev/ttyACM0',9600)
s = [0]
while True:
  read_serial=ser.readline()
  s[0] = str(int (ser.readline(),16))
  print s[0]
  print read_serial
  //use some kind of update log
 * /
 */
