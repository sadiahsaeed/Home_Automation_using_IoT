#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "dht.h"

#define dht_dpin D1 //no ; here. Set equal to channel sensor is on
dht DHT;


// WiFi network info.
char ssid[] = "Wi-Tribe-LTE";
char wifiPassword[] = "rose,lia.";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "0fb827d0-9a48-11e8-bc50-7d9a127b867b";
char password[] = "15bce3f7d8285ea826a011d557f6d0d24cde24cd";
char clientID[] = "967baad0-9a48-11e8-bb66-a9aa61b93b98";

int pir = 4;
int F_S = A0;


void setup() {
  pinMode(pir, INPUT);
  pinMode(F_S, INPUT);
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  }

void loop() {
Cayenne.loop();
DHT.read11(dht_dpin);
float h = DHT.humidity;
float t = DHT.temperature;

Cayenne.virtualWrite(1,t,TYPE_TEMPERATURE,UNIT_FAHRENHEIT);
Cayenne.virtualWrite(2,h,TYPE_RELATIVE_HUMIDITY,UNIT_PERCENT);

if(digitalRead (pir) == HIGH){Cayenne.virtualWrite(3,1);}
if(digitalRead (pir) == LOW){Cayenne.virtualWrite(3,0);}

if(digitalRead (F_S) == HIGH){Cayenne.virtualWrite(4,1);}
if(digitalRead (F_S) == LOW){Cayenne.virtualWrite(4,0);}

}

