//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8; // YELLOW WIRE to pin 12
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12; // GREEN WIRE - to pin 11
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11; // BLUE WIRE - to pin 14
unsigned char rx_1[1];
unsigned char rx_2[1];

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  if(Serial.available()){
    //int i=0;
    while (Serial.available()) {
      delay(3);
      Serial.readBytes(rx_1, sizeof(unsigned char));
      Serial.readBytes(rx_2, sizeof(unsigned char));
      //rx_buf[i] = c;
      //i++;
    }
    //rx_buf[i] = '\0';
    //rx = atoi(rx_buf);
  }
  //Serial.println((int)rx_byte[0]);

  //rx_char[0] = 0b01000000;
  
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, *rx_1);
  shiftOut(dataPin, clockPin, *rx_2);
  digitalWrite(latchPin, 1);
  delay(10);

  //blinkAll_2Bytes(1, 1000);
}

// This method sends bits to the shift register:

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

// https://www.arduino.cc/en/Tutorial/ShftOut23

//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  // Clear both registers with 0's
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    // Write all 1's to both registers
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    // Clear both registers with 0's
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}
