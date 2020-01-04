#ifndef DATAPACKET_H_
#define DATAPACKET_H_

#include "serial.h"

class Datapacket{
    public:
        Datapacket(Serial &arduino);
        void lightsOn(int val);
        void lightsOff();
        void setByte(int which, uint8_t byte);
        void setCollision(bool c);
        void setCollision(bool c, uint8_t b1, uint8_t b2);
        void sendPacket();
        void printPacket();

    private:

    public:

    private:
        Serial *arduino;
        uint8_t packet[14];
        bool lights;
        int lightsVal;
        bool vibrate;
        bool collision;
        uint8_t byte1;
        uint8_t byte2;

};
#endif

