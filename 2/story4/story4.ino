const int MAX_LENGTH = 256;
char response[MAX_LENGTH];
char previousResponse[MAX_LENGTH];
int responseInt;

bool newData = false;



void ask(String question) {
  static unsigned short int index = 0;
  const char EOL = '\n';
  char current_char;

  Serial.println(question);
  bool asking = true;
  while (asking) {
    while (Serial.available() > 0 && newData == false) {
      current_char = Serial.read();

      if (current_char != EOL) {
        response[index] = current_char;
        index++;
        if (index >= MAX_LENGTH) {
          index = MAX_LENGTH - 1;
        }
      } else {
        response[index] = '\0';
        index = 0;
        newData = true;
        asking = false;
      }
    }
  }
}

void printData() {
  if (newData) {
    Serial.println(response);
    newData = false;
  }
}

String parseResponse(int turn) {
  switch (turn) {
    case 0:
      return "Where would you like to go today? [shop, cinema, home] ";

      
    case 1:
      if (strcmp(response, "cinema")) {
        return "You are at the shop, what would you like to buy? [apple, orange, frisbee] "; // MAD bug which was flipping the answers for "shop" and "cinema"....
      }
      else if (strcmp(response, "shop")) {
        return "You are at the cinema, what would you like to watch? [avengers, simpsons, aliens]";
      }
      else if (strcmp(response, "home")) {
        return "You are at home. What do you want to do now? [sit, chill, sleep]";
      } else {
        return "You didn't answer the question...";
      }
      break;

      
    case 2:
      if (strcmp(previousResponse, "cinema")) {
        return "You're in the cinema";
      }
      else if (strcmp(previousResponse, "shop")) {
        return "You're in the shop";
      }
      else if (strcmp(previousResponse, "home")) {
        return "You're in the home";
      } else {
        return "You didn't answer the question...";
      }
      break;

    case 3:
      if (strcmp(previousResponse, "y")) {
        // Went to the park
        return "And so you went to the park and had a wonderful time, just you and the frisbee. The end.";
      } else if (strcmp(previousResponse, "n")) {
        // Didn't go to the park
        return "Well wtf are you gonna do with that frisbee? The end.";
      } else {
        return "Say something!";
      }
      break;

    default:
      return "Nothing.";
      break;
  }
}


void setup() {
  Serial.begin(9600);
  int turn = 0;
  Serial.println(turn);
  ask(parseResponse(turn));
  strncpy(previousResponse, response, sizeof(response));
  
  turn++;
  Serial.println(turn);
  Serial.println(previousResponse);
  ask(parseResponse(turn));
  strncpy(previousResponse, response, sizeof(response));
  
  turn++;
  Serial.print(turn);
  ask(parseResponse(turn));
  strncpy(previousResponse, response, sizeof(response));

  Serial.println();
}

void loop() {}
