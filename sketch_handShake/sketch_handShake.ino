//author="Prateek"
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String readString;
/*
 * LDR A0
 * PIR 2
 * Motor 10
 * LED 11
 * Temp 4
 * Button 3
 */
const int ledPin=11;
const int motorPin=10;
const int pirPin = 6;
const int buttonPin = 3;
const int LDRPin = A0;
float light=9.0,motor=9.0;
long int lastTime=0;
boolean motionDetected=false;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(motorPin,OUTPUT);
  pinMode(LDRPin,INPUT);
  //pinMode(pirPin, INPUT);
  //digitalWrite(pirPin, LOW);
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  attachInterrupt(digitalPinToInterrupt(buttonPin),notify,FALLING);
  attachInterrupt(digitalPinToInterrupt(2),motion,CHANGE);
  dht.begin();
}

void loop()

{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float ldr=analogRead(LDRPin);

  if(millis()-lastTime>10*1000){
      //Serial.println((millis()-lastTime)/1000);
      motionDetected=false;
    }
  
  while (!Serial.available()) {} // wait for data from serial board
  while (Serial.available())
  
  {
    if (Serial.available() >0)
    {
      char c = Serial.read();
      readString += c; 
      if(readString=="Light")
      {       
        light=Serial.parseFloat();
      }
      else if(readString=="Motor")
      {       
        motor=Serial.parseFloat();
      }
    }
  }
  
  if (readString=="Temperature")
  {  
    Serial.println(t);
    readString="";
  }
  else if (readString=="TemperatureF")
  {  
    Serial.println(f);
    readString="";
  }
  else if (readString=="Humidity")
  {  
    Serial.println(h);
    readString="";
  }
  else if (readString=="LDR")
  {  
    Serial.println(ldr); //see what was received
    readString="";
  }  
  else if (readString=="Light")
  {  
      Serial.println("Intensity Set");
      light=map(light,0.0,9.0,0.0,255.0);
      analogWrite(ledPin,light);
      readString="";
  }
  else if (readString=="Motor")
  {  
      Serial.println("Motor Running");
      motor=map(motor,0.0,9.0,0.0,1023.0);
      analogWrite(motorPin,motor);
      readString="";
  }
 
  delay(500);
  // serial write section
  Serial.flush();
}

void notify()
{
  Serial.println("Button");
}
void motion()
{    
  //Serial.println("INside Motion");
    if(!motionDetected){
      Serial.println("Motion Detected");
      motionDetected=true;
      lastTime=millis();
    }
}
