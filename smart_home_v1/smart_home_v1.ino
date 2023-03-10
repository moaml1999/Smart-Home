#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLO9Kwy7wx"
#define BLYNK_DEVICE_NAME "Smart Home"

#include <BlynkSimpleEsp32.h>
#include "DHT.h"


// relay 
#define led_1 22
#define led_2 1
#define led_3 18
#define led_4 5

// flame 
#define flame_pin 17
int flame_sens;

// MQ7
#define mq7PIN 36
int MQ7_percent;

// DHT 
#define DHTTYPE DHT11
uint8_t DHTPin = 23; 

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE); 

float Temperature;
float Humidity;

// LDR
#define LDR_PIN 39 
int LDR_percent;
int val_LDR;

// Buzzer
#define buzzer_PIN 19

// blynk 
char auth[] = "C-TJypKMq1RGAirLIrOwCg1HoF3gxRMb";
char ssid[] = "iPhone";
char pass[] = "100200800900";

BlynkTimer timer;

BLYNK_WRITE(V4)
{
  int val = param.asInt(); // Get value as integer
  digitalWrite(led_1, !val);
}
BLYNK_WRITE(V5)
{
  val_LDR = param.asInt(); // Get value as integer

  } 
    
  
BLYNK_WRITE(V6)
{
  int val = param.asInt(); // Get value as integer
  digitalWrite(led_3, !val);
}
BLYNK_WRITE(V7)
{
  int val = param.asInt(); // Get value as integer
  digitalWrite(led_4, !val);
}




void sendtext()
{
  Blynk.virtualWrite(V0, Temperature); 
  Blynk.virtualWrite(V1, Humidity); 
  Blynk.virtualWrite(V2, MQ7_percent); 
  Blynk.virtualWrite(V3, LDR_percent);
  Blynk.virtualWrite(V8, flame_sens);
}

void setup()
{
  Serial.begin(115200);

  // relay setup
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);

  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
  digitalWrite(led_4, HIGH);

  // flame setup
  pinMode(flame_pin, INPUT);

  // dht setup
  pinMode(DHTPin, INPUT);
  dht.begin();

  // buzzer setup
  pinMode(buzzer_PIN, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendtext);
}


void loop()
{
  // DHT 
  DHT_11();

  // LDR 
  LDR();

  // MQ7
  MQ7();

  // Gas alert
  alert();

  // flame 
  flame();
  
  Blynk.run();
  timer.run();
}
void flame(){
  flame_sens = digitalRead(flame_pin);
    
}
void DHT_11(){
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  }

void MQ7(){
  // read the input on analog pin 0:
  int MQ7_val = analogRead(mq7PIN);
  MQ7_percent = map(MQ7_val, 0, 4094 , 0 , 100);
  }

 void LDR(){
  int ldr_val = analogRead(LDR_PIN);
  LDR_percent = map(ldr_val, 0, 4094, 0, 100);
  if (LDR_percent < 10){
    digitalWrite(led_2, LOW);
  }
  else{
    if (val_LDR == 0){
    digitalWrite(led_2, HIGH);}
    else
    {
      digitalWrite(led_2, LOW);
      }
  } 
 }

 void alert(){
  if (MQ7_percent > 40 or flame_sens == 1 ){
    digitalWrite(buzzer_PIN, HIGH);
  }
  else{
    digitalWrite(buzzer_PIN, LOW);
  }
  }
