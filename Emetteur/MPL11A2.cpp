#include <Arduino.h>
#include "MPL11A2.h"
#include <Wire.h>

float calculPcomp(float a1, float b1, float b2, float c12, unsigned int Padc, unsigned int  Tadc ){
  
  return a1 + (b1 + c12 * Tadc)*Padc + b2*Tadc;
  }

float conversionPression(float Pcomp){
  
  return Pcomp*(0.06353861)+50;
}

float calculTemperature (float Temp){
  
  return (Temp - 498) / (-5.35) + 25;
}

//fonction qui gère le bit de signe 
float checkSigned(float number){
  if (number > 32767) {  //si bit de signe à 1 (> 0b10 0000 0000 00000 = 0d32767)
    number = number - 65536; //+1 et inversion de tout les bits(compléments à 2)
  }
  return number;
}

//Fonction lecture et conversion du registre pour récupérer Tadc et Padc
void Read_Pressure_Temp (float Tab_press_temp[]){
  unsigned int reg[4];

    Wire.beginTransmission(I2c_ADDR_MPL); //demande de transmission au capteur en adresse 0x60
    Wire.write(START_CONV_TEMP_PRESS);    //Commencer la conversion
    Wire.write(ADDR_REG_Padc_MSB);
    Wire.endTransmission();               //fin de la transmission
    delay(100);
    
    Wire.beginTransmission(I2c_ADDR_MPL);//nouvelle transmission
    Wire.write(ADDR_REG_Padc_MSB);       //demande envoi donnée dès le reg 0x00
    Wire.endTransmission();              //fin de transmission
    Wire.requestFrom(I2c_ADDR_MPL, 4);   //envoie d'un octet sur le composant à l'adrese 0x60

    if (Wire.available() == 4){          //si 4 octets sont disponibles alors on lance la lecture sur le ligne i2C
      reg[0] = Wire.read();              //stockage Padc MSB
      reg[1] = Wire.read();              //stockage Padc LSB
      reg[2] = Wire.read();              //stockage Tadc MSB
      reg[3] = Wire.read();              //stockage Tadc LSB

    }

  Tab_press_temp[0] = (reg[0] << 8 | reg[1]) >> 6; 
  Tab_press_temp[1] = (reg[2] << 8 | reg[3]) >> 6; 
  
}

//Fonction lecture et conversion du registre pour récupérer les coefficients
void ReadCoef(float coef[]){

  unsigned int reg[8];

  for (int i = 0 ; i < 8 ; i++){          //On vient lire les registre 0x04 à 0x0B qui correspondent aux valeurs des coef
    Wire.beginTransmission(I2c_ADDR_MPL); //demande de transmission au capteur en adresse 0x60
    Wire.write(ADDR_REG_A0_MSB + i);      //lecture des différents registres
    Wire.endTransmission();               //fin de la transmission
    Wire.requestFrom(I2c_ADDR_MPL, 1);    //envoie d'un octet sur le composant à l'adrese 0x60

    if (Wire.available() == 1){           //si un octet est disponible alors on lance la lecture sur le ligne i2C
      reg[i] = Wire.read();              //stockage des coef
    }
  }

  //concaténation du MSB et LSB (décallage du MSB de 8 bits et ajout d'un ou logique pour concaténer le LSB)
  coef[0] = (reg[0] <<8) | reg[1]; 
  coef[1] = (reg[2] <<8) | reg[3];
  coef[2] = (reg[4] <<8) | reg[5];
  coef[3] = ((reg[6] <<8) | reg[7]) >> 2 ; //suppresion des 2 derniers bits non utilisés (cf. datasheet)

  //prise en compte du bit de signe (MSB)
  coef[0] = checkSigned(coef[0]);
  coef[1] = checkSigned(coef[1]);
  coef[2] = checkSigned(coef[2]);
  coef[3] = checkSigned(coef[3]);
  
  //Conversion bit mantisse vers variable floats
  coef[0] = coef[0]/8;       //3 bits fractionnaires  : 2^3  = 8
  coef[1] = coef[1]/8192;    //13 bits fractionnaires : 2^13 = 8192
  coef[2] = coef[2]/16384;   //14 bits fractionnaires : 2^14 = 8192
  coef[3] = coef[3]/4194304; //22 bits fractionnaires : 2^22 = 4194304
}

