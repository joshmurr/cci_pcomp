int led1 = 5;           // the PWM pin the LED is attached to
int led2 = 6;
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

unsigned char rx[1];

int incoming = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) {
      delay(3);
      //Serial.readBytes(rx, sizeof(unsigned char));
      incoming = Serial.read();
    }
  }

  delay(30);

  //Serial.println((char)*rx);

  if(incoming){
    analogWrite(led1, 255);
    analogWrite(led2, 255);
  } else {
    analogWrite(led1, 15);
    analogWrite(led2, 15);
  }

  delay(30);
}
