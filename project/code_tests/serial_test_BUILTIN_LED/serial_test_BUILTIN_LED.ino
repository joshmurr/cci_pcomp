String readString;
char c;
int LED_TOGGLE = 0;
int i=0;
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // CHECK BUFFER FOR RECEIVED DATA *********** //
  while (Serial.available()){
    // Read everthing in buffer to clear it
    delay(3);
    c = Serial.read();
    readString += c;
  }

  if(readString[0] == 'o'){
    digitalWrite(LED_BUILTIN, 1);
  }
  if(readString[0] == 'x'){
    digitalWrite(LED_BUILTIN, 0);
  }

  // SEND 
  if (readString.length() > 0){
    //Serial.print("Data received: ");
    //Serial.print(readString);
    //Serial.println(" [Arduino Buffer Cleared]");
    readString = "";
  } 
  //****************************************** //
  //Serial.println(i);
  //i++;
  delay(10);
}
