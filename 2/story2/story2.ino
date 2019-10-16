void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void ask_name() {
  Serial.println("What's your name?");
  bool asking = true;
  while (asking) {
    if (Serial.available()) {
      Serial.print("Hello ");
      String s = Serial.readString();
      s[s.length() - 1] = '!'; // Replace '\n' with '!'
      Serial.println(s);
      asking = false;
    }
  }
}

void ask_age() {
  Serial.println("How old are you?");
  bool asking = true;
  while (asking) {
    if (Serial.available()) {
      String a = Serial.readString();
      a[a.length() - 1] = '.';
      Serial.println(a + ".. Seems pretty old to me.");
      asking = false;
    }
  }
}

void ask_location() {
  Serial.println("Where do you live?");
  bool asking = true;
  while (asking) {
    if (Serial.available()) {
      String l = Serial.readString();
      l[l.length() - 1] = '.';
      Serial.println(l + " Nice. Let's stop talking now.");
      asking = false;
    }
  }
}

void yes_no() {
  Serial.println("Answer yes or no (y/n):");
  bool asking = true;
  while (asking) {
    if (Serial.available()) {
      String answer = Serial.readString();
      char a = (char)answer[0];
      if (a == 'y') {
        Serial.println("That's a yes, because you answered: " + a);
      } else if (a == 'n') {
        Serial.println("Why not? You answered: " + a);
      } else {
        Serial.println("Try again.");
        yes_no();
      }
      asking = false;
    }
  }
}

void loop() {
  //yes_no();
  //delay(100);
  ask_name();
  delay(100);
  ask_age();
  delay(100);
  ask_location();
  delay(100);
  Serial.println();
}
