#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#include "Wind_auto.h"
#define DHTPIN 53
#define mutual 0
#define soil_analog A0
#define soil_max 550
#define soil_min 10
#define Cycle_offset 10
#define DHTTYPE DHT21   // DHT 21 (AM2301) // Connect pin 1 (on the left) of the sensor to +5V // NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1 // to 3.3V instead of 5V! // Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND // Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor // Initialize DHT sensor for normal 16mhz Arduino
extern uint8_t _tempmiss ;
DHT dht(DHTPIN, DHTTYPE);
JSNR04T Ux1(45,10,mutual,2000) ,Ux2(37,13,mutual,2000),Uy1(47,50,mutual,2000),Uy2(31,10,mutual,2000) ,Uz1(41,12,mutual,2000),Uz2(39,11,mutual,2000);
Wind WindX(&Ux1,&Ux2), WindY(&Uy1,&Uy2) ,WindZ(&Uz1,&Uz2);
float CycTemp , CycHum , _CSS=340 , winspeed;
int soilM;
uint16_t allmiss,cycledelay=19000;
void setup() {
  Serial.begin(9600);
  set_windsensor(dht);
  dht.begin();
  Set_nowinddistance();
}

void loop() {
wind_cycle(&WindX ,&WindY, &WindZ);
allmiss=(WindX._selfmiss+WindY._selfmiss+WindZ._selfmiss)*selfecho_timeout;  // adobt self cycle delay into main delay 
allmiss+=(WindX._aheadmiss+WindY._aheadmiss+WindZ._aheadmiss)*headecho_timeout;
allmiss+= _tempmiss;
_tempmiss=0;
  soilM= analogRead(soil_analog);
  soilM = map(soilM,1000,0,0,1000);
  //Build JSON Package 
build_json_package();
  cycledelay-=allmiss;
//WindX.avgwind=0;  //optional reset this averge if you want each cycle averge to be unique 
delay(cycledelay);
}
void build_json_package(void) {
Serial.print(" {");
Serial.print("{ \"Temp\":");Serial.print("\"");Serial.println(CycTemp);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Humidity\":");Serial.print("\"");Serial.println(CycHum);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Soil_Mositure\":");Serial.print("\"");Serial.println(soilM);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_Speed_x\": ");Serial.print("\"");Serial.print(WindX.avgwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_Speed_y\": ");Serial.print("\"");Serial.print(WindY.avgwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_Speed_z\":");Serial.print("\"");Serial.print(WindZ.avgwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Maximum_Speed_x\": ");Serial.print("\"");Serial.print(WindX.maxwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Maximum_Speed_y\": ");Serial.print("\"");Serial.print(WindY.maxwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Maximum_Speed_z\": ");Serial.print("\"");Serial.print(WindZ.maxwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Minmimum_Speed_x\": ");Serial.print("\"");Serial.print(WindX.minwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Minmimum_Speed_y\": ");Serial.print("\"");Serial.print(WindY.minwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Minmimum_Speed_z\" :");Serial.print("\"");Serial.print(WindZ.minwind);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_frequencyofchange_x\": ");Serial.print("\"");Serial.print(WindX.gust);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_frequencyofchange_y\" :");Serial.print("\"");Serial.print(WindY.gust);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Wind_frequencyofchange_z \":");Serial.print("\"");Serial.print(WindZ.gust);Serial.print("\"");Serial.print(" , ");
Serial.print("\"Cycle Overshoot\":");Serial.print("\"");Serial.print(allmiss);Serial.print("\"");
Serial.println(" }");
}
void Set_nowinddistance(){
    Ux1.nowind_distance=nowind_distancex1;
    Ux2.nowind_distance=nowind_distancex2;
    Uy1.nowind_distance=nowind_distancey1;
    Uy2.nowind_distance=nowind_distancey2;
    Uz1.nowind_distance=nowind_distancez1;
    Uz2.nowind_distance=nowind_distancez2;
}
