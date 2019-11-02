// https://www.instructables.com/id/Arduino-AND-Bluetooth-HC-05-Connecting-easily/#step1
// This program shown how to control arduino from PC Via Bluetooth
// Connect ...
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx
//Written By Mohannad Rawashdeh
//for http://www.genotronex.com/

// you will need arduino 1.0.1 or higher to run this sketch

#include <SoftwareSerial.h>// import the serial library
#include <Wire.h>  // Wire library - used for I2C communication


SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin = 13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  // BLUETOOTH
  Genotronex.begin(9600);

  // ACCELEROMETER
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(10);
  
  //Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin, OUTPUT);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //BluetoothData = Genotronex.read();
  /*Genotronex.print("GyX = "); Genotronex.print(GyX);
  Genotronex.print(" | GyY = "); Genotronex.print(GyY);
  Genotronex.print(" | GyZ = "); Genotronex.println(GyZ);*/
  Genotronex.print(GyX);
  Genotronex.print('\t');
  Genotronex.print(GyY);
  Genotronex.print('\t');
  Genotronex.print(GyZ);
  Genotronex.print('\n');
  
  delay(100);// prepare for next data ...
}
