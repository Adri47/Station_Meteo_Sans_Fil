#ifndef DTH11_H
#define DTH11_H

#define PIN_DHT 4
#define DHTLIB_ERROR_CHECKSUM -1

void startCom(int pin);

void Wait_pin_etat(int pin, bool etat);

int readCom(int pin, float *humidity, float *temperature);

#endif
