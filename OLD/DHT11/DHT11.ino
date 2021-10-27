#define PIN_DHT 4
#define DHTLIB_ERROR_CHECKSUM -1

int humidity=0;
int temperature=0;

//fonction permettant de commencer la com avec le capteur
void startCom(int pin)
{
  pinMode(pin, OUTPUT);   //pin 4 configurée en OUTPUT (en mode écriture)
  digitalWrite(pin, LOW); //pin 4 niveau bas
  delay(18);              //niveau bas durant 18 ms (cf. datasheet)
  digitalWrite(pin, HIGH);//pin 4 niveau haut
  delayMicroseconds(40);  //niveau haut durant 40 ms (cf. datasheet
  pinMode(pin, INPUT);    //pin 4 en INPUT (en mode réception)
}

//fonction qui compare l'état d'un PIN afin de relever une erreur 
void Wait_pin_etat(int pin, bool etat)
{
 unsigned int timeOUT = 10000;
 while(digitalRead(pin) == etat)  //si la pin reste à l'état rentrée dans la fct on décrémente le timeOUT
    if (timeOUT-- == 0) Serial.println("ERROR_TIMEOUT"); //si le timeOUT vaut 0 alors on affiche "ERROR_TIMEOUT"
}

//fonction qui lit ce qui est envoyée par le capteur DHT
int readCom(int pin)
{
  uint8_t octet[5];  //tableau de 5 cases de 8 bits
  uint8_t cpt = 7;   //compteur
  uint8_t index = 0; //nuùéro de l'octet

  //on vide le buffer
  for (int i=0; i< 5; i++) {
     octet[i] = 0;
  }

  //on démarre la com avec le capteur
  startCom(pin);
  //on vérifie que le capteur nous envoie un état bas (cf. datasheet)
  Wait_pin_etat(4,0);
  //après un état bas, on vérifie que le capteur nous envoie un état haut(cf. datasheet)
  Wait_pin_etat(4,1);

  //On lit les 40 bits envoyés par le capteur (0b0 = 5V entre 26 et 28µs / 0b1 = 5V pendant 70µs )
  for (int i=0; i<40; i++) //i = 40 car 40 bits
  {
    Wait_pin_etat(4,0); //attente du niveau bas pour début de com (cf. datasheet)

    unsigned long t = micros(); //temps en µs de l'intant t0

    Wait_pin_etat(4,1); //attente du niveau haut pour connaitre la valeur du bit 

    if ((micros() - t) > 40) { //dection de 1 ou 0 (si >40µs => 1 sinon 0)
      octet[index] = octet[index] | (1 << cpt); //stockage du bit reçu dans l'octet (Attention MSB reçu en 1er, cpt initialisé à 7)
    }
    if (cpt == 0)  
    {
      cpt = 7;    
      index++;     
    }
    else cpt--;
  }
  
  humidity    = octet[0]; //valeur entière de l'humidité
  temperature = octet[2]; //valeur entière de la température

  uint8_t sum = octet[0] + octet[2];  

  if (octet[4] != sum) return DHTLIB_ERROR_CHECKSUM;
  return 0;
}
void setup() {
   
 Serial.begin(9600);
}

void loop() {

 
 readCom(PIN_DHT);
 Serial.print("Humidity (%): ");
 Serial.println((float)humidity, 2);

 Serial.print("Temperature (C): ");
 Serial.println((float)temperature, 2);
 delay(200);
 

  


}

