#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLO9Kwy7wx"
#define BLYNK_DEVICE_NAME "Smart Home"

#include <BlynkSimpleEsp32.h>

char auth[] = "C-TJypKMq1RGAirLIrOwCg1HoF3gxRMb";
char ssid[] = "Makers";
char pass[] = "12345678m";

#define led 22

BLYNK_WRITE(V0)
{   
  int val = param.asInt(); // Get value as integer
digitalWrite(led, val);
}


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
pinMode(led, OUTPUT);
}


void loop()
{
  
  Blynk.run();
}
