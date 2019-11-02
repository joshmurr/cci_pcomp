String readString;
char c;
void setup()
{
    pinMode(0, INPUT_PULLUP);// only needed for  JY-MCUY v1.06?
    Serial.begin(9600);
    Serial.println("OK then, you first, say something.....");
    Serial.println("Go on, type something in the space above");
    Serial.println(" and hit Send or Enter,");
    Serial.println("then I will repeat it!");
    Serial.println("");
}

void loop() {
    while (Serial.available()) 
  {
    delay(3);  
    c = Serial.read();
    readString += c; 
  }// end while
  if (readString.length() >0) 
  {  
    Serial.write(c);  
   readString="";  
  } // end if
}
