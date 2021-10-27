float ReadLux(int pin)
{
  float valueLum_bit  = 0;
  float valueLum_Volt = 0;
  float valueLum_Amp  = 0;
  float valueLum_Lux  = 0;

  valueLum_bit  = analogRead(pinLum);
  valueLum_Volt = valueLum_bit * 5 / 1024;           // Vmax = 5V ; bitmax = 1023 ; U = bit*5V/1024
  valueLum_Amp  = (valueLum_Volt / 10000) * 1000000; // I=U/R=u/10k
  valueLum_Lux  = valueLum_Amp * 2;                  //loi linéaire avec coef directeur de 2

  return valueLum_Lux;
}

void setup() {
  Serial.begin(9600);
  
}


void loop() {

  
  Serial.print("Valeur en Volt : ");
  Serial.print( valueLum_Volt);
  Serial.print("  ");

  Serial.print("Valeur en µA : ");
  Serial.print( valueLum_Amp);
  Serial.print("  ");
  
  Serial.print("Valeur en LUX : ");
  Serial.println(valueLum_Lux);
  delay(100);
}
