#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include "dht.h"

#define dht_pin A8 // Pin sensor is connected to pin A8
dht DHT;

#define trigPin A10
#define echoPin A9

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

char* secretCode = "235711";
int position = 0;
 
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte rowPins[rows] = {A0, A1, A2, A3};
byte colPins[cols] = {A4, A5, A6};
 
Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins,rows, cols);

int buz = 13;

int ma = 9; 
int mb = 8; 

int mc = 10; 
int md = 11; 

int pir1 = A11;
int pir2 = A12;

int temp = 0;
int hum = 0;

long duration, distance,Sensor;

int pump = 22;
int fan = 12;

void setup()

{
Serial.begin(9600); 
Serial1.begin(9600);       

pinMode(pir1, INPUT);
pinMode(pir2, INPUT);
  
pinMode(fan, OUTPUT);
pinMode(pump, OUTPUT);
  
pinMode(buz, OUTPUT);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
  
pinMode(ma, OUTPUT);
pinMode(mb, OUTPUT);

pinMode(mc, OUTPUT);
pinMode(md, OUTPUT);
      
lcd.begin(16,4);
lcd.setCursor(0,0);
lcd.print("Keypad Security  ");
lcd.setCursor(0,1);
lcd.print("System...        ");
delay(1000);
lcd.clear();
lcd.print("Enter Password");
}

void loop()
{
  
SonarSensor(trigPin, echoPin);
Sensor = distance; 

if(Sensor>=40){Sensor=40;}
Sensor = map(Sensor, 5, 40, 100, 0);
if(Sensor>100){Sensor=100;}


if(Sensor<30){digitalWrite(pump,HIGH);}
if(Sensor>80){digitalWrite(pump,LOW);} 
  
if ((digitalRead (pir1) == LOW)||(digitalRead (pir2) == LOW))
{
lcd.clear();
lcd.print("Door Open 1   ");
lcd.setCursor(0,0);
        
 digitalWrite(mc, HIGH); 
 digitalWrite(md, LOW);
 delay(2000);
 digitalWrite(mc, LOW); 
 digitalWrite(md, LOW);
 delay(3000);
 lcd.clear();
 lcd.print("Door Close 1   ");
 lcd.setCursor(0,0);
 digitalWrite(mc, LOW); 
 digitalWrite(md, HIGH);
 delay(2000);
 digitalWrite(mc, LOW); 
 digitalWrite(md, LOW);
 lcd.clear();
 lcd.print("Enter Password:");
 lcd.setCursor(0,1);  
}

DHT.read11(dht_pin);
temp = DHT.temperature;
hum = DHT.humidity;

lcd.setCursor(0,2);
lcd.print("T= ");
lcd.print(temp);
lcd.print("'c  ");

lcd.setCursor(9,2);
lcd.print("H= ");
lcd.print(hum);
lcd.print("%  ");

lcd.setCursor(0,3);
lcd.print("Water = ");
lcd.print(Sensor);
lcd.print("%  ");


if(temp>35){digitalWrite(fan,HIGH);}
if(temp<35){digitalWrite(fan,LOW);}

 
 char key = keypad.getKey();
  if (key == '*' || key == '#') 
  {position = 0;}
  
 if (key == secretCode[position])
 {position++;}
 if (position == 6){setLocked();}

lcd.setCursor(0,1);
lcd.print(key);
 
 Serial1.write(Sensor); 
 Serial1.write(temp); 
 delay(100); 
}


void setLocked()
{
lcd.clear();
lcd.print("Door Open 2   ");
lcd.setCursor(0,0);
        
 digitalWrite(ma, HIGH); 
 digitalWrite(mb, LOW);
 delay(2000);
 digitalWrite(ma, LOW); 
 digitalWrite(mb, LOW);
 delay(3000);
 lcd.clear();
 lcd.print("Door Close 2   ");
 lcd.setCursor(0,0);
 digitalWrite(ma, LOW); 
 digitalWrite(mb, HIGH);
 delay(2000);
 digitalWrite(ma, LOW); 
 digitalWrite(mb, LOW);
 lcd.clear();
 lcd.print("Enter Password:");
 lcd.setCursor(0,1);  
position = 0;
}


void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);//DISTANCE IN CM
distance = (duration/2) / 29.1;
}


