#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
String readString;

void setup()
{
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  dht.begin();
}

void loop()

{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  while (!Serial.available()) {} // wait for data to arrive
  // serial read section
  while (Serial.available())
  
  {
    if (Serial.available() >0)
    {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }
  }

  if (readString=="Temperature")
  {  
    Serial.println(t); //see what was received
    readString="";
  }
  else if (readString=="TemperatureF")
  {  
    Serial.println(f); //see what was received
    readString="";
  }
  else if (readString=="Humidity")
  {  
    Serial.println(h); //see what was received
    readString="";
  }
  
  delay(500);
  // serial write section
  Serial.flush();
}
