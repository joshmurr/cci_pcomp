int LEDS[5] = {8, 9, 10, 11, 12};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], HIGH);
    delay(300);
    digitalWrite(LEDS[i], LOW);
    delay(300);
  }
}
