
uint8_t teapotPacket[14];
int serialCount = 0;                 // current packet byte position
int synced = 0;
int interval = 0;

char str[8];

void setup() {
  Serial.begin(115200);

}

void loop() {
  str[0] = teapotPacket[2];
  str[1] = teapotPacket[3];
  str[2] = teapotPacket[4];
  str[3] = teapotPacket[5];
  str[4] = teapotPacket[6];
  str[5] = teapotPacket[7];
  str[6] = teapotPacket[8];
  str[7] = teapotPacket[9];

  Serial.println(str);
}

void serialEvent(){
  interval = millis();
    while (Serial.available() > 0) {
        uint8_t ch = Serial.read();

        if (synced == 0 && ch != '$') return;   // initial synchronization - also used to resync/realign if needed
        synced = 1;
        Serial.println((char)ch);

        if ((serialCount == 1 && ch != 2)
            || (serialCount == 12 && ch != '\r')
            || (serialCount == 13 && ch != '\n'))  {
            serialCount = 0;
            synced = 0;
            return;
        }

        if (serialCount > 0 || ch == '$') {
            teapotPacket[serialCount++] = ch;
            if (serialCount == 14) {
                serialCount = 0; // restart packet byte position
               
                
            }
        }
    }
}
