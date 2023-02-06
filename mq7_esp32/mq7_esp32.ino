#define mq7PIN 36
int sens_percent;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(mq7PIN);
  sens_percent = map(sensorValue, 0, 4094 , 0 , 100);
  // print out the value you read:
  Serial.println(sens_percent);
  delay(20);
}
