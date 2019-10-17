const int buttonPins[] = {6, 7, 8, 9};
const int ledPins[] = {2, 3, 4, 5};
const int ledCount = 4;
const int buttonCount = 4;
const int MAX_GOES = 10;

bool game_over = false;

int buttonCounter = 0, buttonState = 0;
int lastButtonState[] = {0, 0, 0, 0};
int computersTurn[MAX_GOES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int playersTurn[MAX_GOES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

long randomNum;


void setup() {
  int i;
  for(i=0; i<buttonCount; i++){
    pinMode(buttonPins[i], INPUT);
  }
  for(i=0; i<ledCount; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);
  randomSeed(analogRead(0));

  computer_init();
  delay(50);
  start_sequence(5);
  delay(500);
}


void loop() {
  int turn = 1;

  // GAME LOOP
  while(turn < MAX_GOES && !game_over){
    turn_off_leds();
    delay(500);
    computers_turn(turn);
    delay(300);
    players_turn(turn);
    delay(300);
    turn++;
  }

  if(game_over) {
    game_over_sequence(3, 200);
  } else if(!game_over){
    win_sequence(20);
  }
}


void players_turn(int turnCounter){
  int button, tc = 0;
  while(tc < turnCounter && !game_over){
    for(button=0; button<buttonCount; button++){
      buttonState = digitalRead(buttonPins[button]);
      
      if(buttonState != lastButtonState[button]){
        if(buttonState == HIGH){
          Serial.print("User Pressed Button: ");
          Serial.println(button);
          
          if(computersTurn[tc] != button){
            // FAIL
            game_over = true;
            break;
          } else {
            playersTurn[tc] = button;
            buttonCounter++; // Total button presses
            tc++; // Turn counter
          }
        }
        delay(50);
      }
      lastButtonState[button] = buttonState;
    }
    // Write state to LEDs
    for(button=0; button<buttonCount; button++){
      if(lastButtonState[button]){
        digitalWrite(ledPins[button], HIGH);
      } else {
        digitalWrite(ledPins[button], LOW);
       }
    }
  }
}


void turn_off_leds(){
  // Turn off all LEDs
  for(int j=0; j<ledCount; j++){
    digitalWrite(ledPins[j], LOW);
  }
}

void turn_on_leds(int t){
  // Turn off all LEDs
  for(int j=0; j<ledCount; j++){
    digitalWrite(ledPins[j], HIGH);
  }
  delay(t);
}

void computer_init(){
  Serial.println("Initialize Computer Sequence...");
  for(int i=0; i<MAX_GOES; i++){
    computersTurn[i] = int round(random(0, 4));
  } 
}


void computers_turn(int t){
  turn_off_leds();
  int i = 0;
  Serial.print("Computer Seq: ");
  while(i < t){
    delay(300);
    Serial.print(computersTurn[i]);
    digitalWrite(ledPins[computersTurn[i]], HIGH);
    delay(300);
    digitalWrite(ledPins[computersTurn[i]], LOW);
    i++;
  }
  Serial.println();
}

void start_sequence(int t){
  Serial.println("Start sequence...");
  int i = 0;
  int led;
  while(i < t){
    for(led=0; led<ledCount; led++){
      digitalWrite(ledPins[led], HIGH);
      
    }
    delay(60);
    for(led=0; led<ledCount; led++){
      digitalWrite(ledPins[led], LOW);
      
    }
    delay(60);
    i++;
  }
}

void game_over_sequence(int t, int l){
  Serial.println("YOU LOSE!");
  turn_on_leds(500);
  turn_off_leds();
  delay(200);
  int i = 0;
  int led;
  while(i < t){
    for(led=0; led<ledCount; led++){
      digitalWrite(ledPins[led], HIGH);
      delay(l);
      digitalWrite(ledPins[led], LOW);
      delay(l);
    }
    i++;
  }
  game_over = false;
  computer_init();
  delay(50);
  start_sequence(5);
  delay(500);
}

void win_sequence(int t){
  Serial.println("YOU WIN!");
  int i = 0;
  int led;
  while(i < t){
    for(led=0; led<ledCount; led++){
      digitalWrite(ledPins[led], HIGH);
    }
    delay(30);
    for(led=0; led<ledCount; led++){
      digitalWrite(ledPins[led], LOW);
    }
    delay(30);
    i++;
  }
  game_over = false;
  computer_init();
  delay(50);
  start_sequence(5);
  delay(500);
}
