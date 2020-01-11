// Code from:
// http://arduinolearning.com/learning/basics/arduino-ldr-example.php

int sensorValue;
int led = 13;

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  sensorValue = analogRead(0); // read analog input pin 0
  //daylight was 700 – so lets detect a reading under 300
  if (sensorValue < 300) // 300 seems perfect, although lets some light through a fingertip
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  delay(100); // wait 100ms for next reading
}
