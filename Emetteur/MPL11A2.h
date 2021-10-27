#ifndef MPL11A2_H
#define MPL11A2_H

//Commandes
#define START_CONV_TEMP_PRESS 0x12
#define Read_Pressure_ADC_MSB 0x00

//Adresse I2C du composant
#define I2c_ADDR_MPL 0x60

//Adresse registres
#define ADDR_REG_A0_MSB 0x04
#define ADDR_REG_Padc_MSB 0x00

float calculPcomp(float a1, float b1, float b2, float c12, unsigned int Padc, unsigned int  Tadc );

float conversionPression(float Pcomp);

float calculTemperature (float Temp);

float checkSigned(float number); //fonction qui gère le bit de signe 

void Read_Pressure_Temp (float Tab_press_temp[]);

void ReadCoef(float coef[]);


#endif
