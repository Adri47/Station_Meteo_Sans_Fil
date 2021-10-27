#include <Arduino.h>
#include "TEMT6000.h"

float ReadLux(int pin)
{
  float valueLum_bit  = 0;
  float valueLum_Volt = 0;
  float valueLum_Amp  = 0;
  float valueLum_Lux  = 0;

  valueLum_bit  = analogRead(pin);
  valueLum_Volt = valueLum_bit * 5 / 1024;           // Vmax = 5V ; bitmax = 1023 ; U = bit*5V/1024
  valueLum_Amp  = (valueLum_Volt / 10000) * 1000000; // I=U/R=u/10k
  valueLum_Lux  = valueLum_Amp * 2;                  //loi linéaire avec coef directeur de 2

  return valueLum_Lux;
}
