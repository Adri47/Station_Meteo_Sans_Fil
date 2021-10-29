#include "TEMT6000.h"
#include "MPL11A2.h"
#include "DHT11.h"


#include <Wire.h>

#define PIN_TEMT6000 A0

float valueLum_Lux_TEMT6000 = 0;

float coef[4];// a0 b1 b2 c12
float Tab_press_temp[2]; //Padc et Tadc
float Pcomp;
float Pressure_MPL11A2;
float Temperature_MPL11A2;

float humidity_DHT11;
float temperature_DHT11;

int count;
void setup() {
 
  Serial.begin(9600);  // Initialisation Terminal Série
  Wire.begin();        // Initialisation I2C
  
  ReadCoef(coef);
  count=0;
}

void loop() {
  
  valueLum_Lux_TEMT6000 = ReadLux(PIN_TEMT6000);
  
  Read_Pressure_Temp(Tab_press_temp);
  
  Pcomp = calculPcomp(coef[0], coef[1], coef[2], coef[3], Tab_press_temp[0], Tab_press_temp[1]);
  Pressure_MPL11A2 = conversionPression(Pcomp);
  Temperature_MPL11A2 = calculTemperature(Tab_press_temp[1]);

  readCom(PIN_DHT, &humidity_DHT11, &temperature_DHT11);
  
  
  //Serial.println("Valeur en LUX TEMT6000 : ");
  //Serial.print("<");
  Serial.print(valueLum_Lux_TEMT6000);
  Serial.print(":");
  //Serial.println("Pression MPL11A2: ");
  Serial.print(Pressure_MPL11A2);
  Serial.print(":");
  //Serial.println("Temp MPL11A2:");
  Serial.print(Temperature_MPL11A2, DEC);
  Serial.print(":");

  //Serial.println("Humidity DHT11 (%): ");
  Serial.print(humidity_DHT11, DEC);
  Serial.print(":");
  //Serial.println("Temperature DHT11 (C): ");
  Serial.print(temperature_DHT11, DEC);
  Serial.print("\n");
  delay(20);
  
}
