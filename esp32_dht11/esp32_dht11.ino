#include "DHT.h"

#define DHTTYPE DHT11
// DHT Sensor
uint8_t DHTPin = 23; 

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE); 

float Temperature;
float Humidity;


void setup()
{
  Serial.begin(9600);
  pinMode(DHTPin, INPUT);
  dht.begin();
  
  }

void loop()
{

   Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
 
  Serial.print(Humidity, 1);
  Serial.print("\t\t");
  Serial.print(Temperature, 1);
  Serial.println(" ");
}
