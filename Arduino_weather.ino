//
//#include <SoftwareSerial.h>
//#include <Arduino.h>
//#include "DHT.h"
//#include "Wind_auto.h"
//#define DHTPIN 53
//#define mutual 0
//#define soil_analog 0
//#define soil_max 550
//#define soil_min 10
//SoftwareSerial mySerial(2, 3); // RX, TX is not needed as ultrasonic triggers itself
//#define DHTTYPE DHT21   // DHT 21 (AM2301) // Connect pin 1 (on the left) of the sensor to +5V // NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1 // to 3.3V instead of 5V! // Connect pin 2 of the sensor to whatever your DHTPIN is
//// Connect pin 4 (on the right) of the sensor to GROUN // Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor // Initialize DHT sensor for normal 16mhz Arduino
//#define Cycle_offset 10
//extern uint8_t _tempmiss ;
//DHT dht(DHTPIN, DHTTYPE);
//JSNR04T Ux1(43,10,mutual,2000) ,Ux2(39,11,mutual,2000) ,Uy1(41,12,mutual,2000),Uy2(37,13,mutual,2000),Uz1(45,2,mutual,2000),Uz2(47,2,mutual,2000) ;
//Wind WindX(&Ux1,&Ux2), WindY(&Uy1,&Uy2) ,WindZ(&Uz1,&Uz2);
//float CycTemp , CycHum ;
//uint16_t soilM ;
//uint8_t allmiss;
//void setup() {
//  Serial.begin(9600);
//  set_windsensor(dht);
//  // set_soil(min_value,max_value) moved for debug
//}
//
//void loop() {
//  CycTemp=get_temp_from_sensor(dht);
//  CycHum=get_humidity_from_sensor(dht);
//  (void)get_speedofsound(CycTemp,CycHum);
//  soilM= analogRead(soil_analog);
//  soilM = map(soilM,soil_max,soil_min,0,1000);
//  wind_cycle(&WindX ,&WindY, &WindZ);
//  allmiss=(WindX._selfmiss+WindY._selfmiss+WindZ._selfmiss)*selfecho_timeout;
//  allmiss+=(WindX._aheadmiss+WindY._aheadmiss+WindZ._aheadmiss)*headecho_timeout;
//  allmiss+= _tempmiss;
////write debugging tools
////// if global windZ=global_windY=global_windX; it's static wind
////// repeat the loop and measure difference between readings
//  Serial.print("Temp:");Serial.println(CycTemp);
//  Serial.print("Humidity:");Serial.println(CycHum);
//  Serial.print("Soil_Mositure ");Serial.println(soilM);
//  Serial.print("Wind_Speed ");Serial.print(WindX.avgwind);Serial.print(" X,");Serial.print(WindY.avgwind);Serial.print(" Y,");Serial.print(WindZ.avgwind);Serial.print(" Z");
//  Serial.print("Wind_frequency ");Serial.print(WindX.gust);Serial.print(" X/10,");Serial.print(WindY.gust);Serial.print(" Y/10,");Serial.print(WindZ.gust);Serial.print(" Z/10");
//  Serial.print("Minmimum Wind_Speed ");Serial.print(WindX.minwind);Serial.print(" X,");Serial.print(WindY.minwind);Serial.print(" Y,");Serial.print(WindZ.minwind);Serial.print(" Z");
//  Serial.print("Maximum Wind_Speed ");Serial.print(WindX.maxwind);Serial.print(" X,");Serial.print(WindY.maxwind);Serial.print(" Y,");Serial.print(WindZ.maxwind);Serial.print(" Z");
//  Serial.print("Cycle Overshoot");Serial.print(allmiss);
//  delay(Cycle_offset-allmiss);
//
//?
//}
