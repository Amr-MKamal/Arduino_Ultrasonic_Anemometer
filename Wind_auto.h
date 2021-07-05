

#ifndef WINDAUTO_H
#define WINDAUTO_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#define commonTx 16
#define selfecho_timeout 99
#define headecho_timeout 49
#define nowind_distancex1 456
#define nowind_distancex2 438
#define nowind_distancey1 442
#define nowind_distancey2 430
#define nowind_distancez1 430
#define nowind_distancez2 460
// #define DEBUG

class JSNR04T{
 private:
 // uint8_t data[6];
  uint8_t _EnPin,_RXpin, _max_range, _type;
  uint16_t _lastread;
  unsigned long _lastreadtime;
 public:
 uint16_t nowind_distance ;
 uint8_t _timeout ;
 boolean working;
  volatile SoftwareSerial *windSerial; // RX, TX is not needed as ultrasonic triggers itself
  JSNR04T(uint8_t EnPin, uint8_t RXpin, uint8_t type, uint16_t max_range);
  void begin(void);
  void virtual_trigger(void);
  void disable(void);
  void resetTimeout(uint8_t timeout);
  void normalize(void);
  int readJSNR04TSerial(void);
  uint16_t get_selfecho(void);
  int get_selfwindspeed(void);
  float transform_read(uint16_t x);

};
class Wind{
 private:
 JSNR04T *_Ud1 ;
 JSNR04T *_Ud2 ;
 public:
  uint8_t gust, _selfmiss, _aheadmiss;
  float newwind ,oldwind ,avgwind ,minwind, maxwind ;
  Wind(JSNR04T* ,JSNR04T* );
  void update(void);
  float get_avergewind (void);
  uint16_t get_echofromahead(void);
};
float get_temp_from_sensor(DHT _dht);
float get_humidity_from_sensor(DHT _dht);
void renew_temp_hu(DHT _dht,float *temp ,float *hum);
float get_speedofsound(float Tc,float RH);
void set_windsensor(DHT _dht);
int get_echofromahead (JSNR04T _u1 ,JSNR04T _u2);
void wind_cycle(Wind* WindX ,Wind* WindY ,Wind* WindZ );
#endif // !WINDAUTO_H
