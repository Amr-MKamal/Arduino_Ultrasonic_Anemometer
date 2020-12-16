#ifndef WINDAUTO_H
#define  WINDAUTO_H
#define commonTx 16
#include <Arduino.h>
#include "DHT.h"
// #define DEBUG
int readSerial();
void init_ultra(void);

/*
 * #define AM2301 21

class DHT {
 private:
  uint8_t data[6];
  uint8_t _pin, _type, _count;
  unsigned long _lastreadtime;
  boolean firstreading;

 public:
  DHT(uint8_t pin, uint8_t type, uint8_t count=6);
  void begin(void);
  float readTemperature(bool S=false);
  float convertCtoF(float);
  float convertFtoC(float);
  float computeHeatIndex(float tempFahrenheit, float percentHumidity);
  float readHumidity(void);
  boolean read(void);

};
 */
#endif // !JSNSR04T_H
