void setup() {
  Serial.begin(9600);
}

void ask(String question, bool lastLine) {
  Serial.print(question);
  bool asking = true;
  while (asking) {
    if (Serial.available()) {
      String s = Serial.readString();
      if(lastLine) s[s.length() - 1] = '\0'; // Replace '\n' with '\0'
      else s[s.length() - 1] = ',';
      Serial.println(s);
      asking = false;
    }
  }
}

void loop() {
  ask("Roses are... ", 0);
  delay(100);
  ask("Violets are... ", 0);
  delay(100);
  ask("Sugar is... ", 0);
  delay(100);
  ask("And so are... ", 1);
  delay(100);
  Serial.println();
}
