#include "datapacket.h"

Datapacket::Datapacket(){
    this->packet[0] = '$';
    this->packet[1] = 0x02;
    this->packet[2] = 0; // Lights Value
    this->packet[3] = 0; // Collision
    this->packet[4] = 0; // Byte1
    this->packet[5] = 0; // Byte2
    this->packet[6] = 0;
    this->packet[7] = 0;
    this->packet[8] = 0;
    this->packet[9] = 0;
    this->packet[10] = 0x00;
    this->packet[11] = 0x00;
    this->packet[12] = '\r';
    this->packet[13] = '\n';
}

void Datapacket::lightsOn(int val){
    this->lights = true;
    this->lightsVal = val;
    this->packet[2] = val;
}

void Datapacket::lightsOff(){
    this->lights = false;
    this->lightsVal = 10;
    this->packet[2] = 10;
}

void Datapacket::setByte(int which, uint8_t byte){
    if(which == 1) this->byte1 = byte;
    if(which == 2) this->byte2 = byte;
}

void Datapacket::setCollision(bool c){
    this->collision = c;
    this->packet[3] = 'C'; // C means turn all motors on
}

void Datapacket::setCollision(bool c, uint8_t b1, uint8_t b2){
    this->collision = c;
    this->packet[3] = 'c'; // c means check the next two bytes for which motors
    this->packet[4] = b1;
    this->packet[5] = b2;
}
