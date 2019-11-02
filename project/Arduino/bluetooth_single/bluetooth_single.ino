// https://www.instructables.com/id/Arduino-AND-Bluetooth-HC-05-Connecting-easily/#step1
// This program shown how to control arduino from PC Via Bluetooth
// Connect ...
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx
//Written By Mohannad Rawashdeh
//for http://www.bluetoothPort.com/

// you will need arduino 1.0.1 or higher to run this sketch

#include <SoftwareSerial.h>// import the serial library

SoftwareSerial bluetoothPort(10, 11); // RX, TX
int blueLED = 5;
int greenLED = 4; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  bluetoothPort.begin(9600);
  bluetoothPort.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetoothPort.available()) {
    BluetoothData = bluetoothPort.read();
    if (BluetoothData == '1') { // if number 1 pressed ....
      digitalWrite(blueLED, 1);
      digitalWrite(greenLED, 1);
      bluetoothPort.println("LED ON! ");
    }
    if (BluetoothData == '0') { // if number 0 pressed ....
      digitalWrite(blueLED, 0);
      digitalWrite(greenLED, 0);
      bluetoothPort.println("LED Off! ");
    }
  }
  delay(100);// prepare for next data ...
}
