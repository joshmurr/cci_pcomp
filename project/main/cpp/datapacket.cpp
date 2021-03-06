#include "datapacket.h"

Datapacket::Datapacket(Serial &arduino){
    this->arduino = &arduino;
    this->packet[0] = '$';
    this->packet[1] = 0x02;
    this->packet[2] = 0; // Lights Value
    this->packet[3] = 0; // Collision
    this->packet[4] = 0; // Byte1
    this->packet[5] = 0; // Byte2
    this->packet[6] = 0;
    this->packet[7] = 0;
    this->packet[8] = 0;
    this->packet[9] = 0; // Sync Status
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

void Datapacket::setSynced(bool sync){
    this->synced = sync;
    if(sync)this->packet[9] = 1;
    else this->packet[9] = 0;
}

void Datapacket::setByte(int which, uint8_t byte){
    if(which == 1) this->byte1 = byte;
    if(which == 2) this->byte2 = byte;
}

void Datapacket::setCollision(bool c){
    this->collision = c;
    if(c) {
        this->packet[3] = 'C'; // C means turn all motors on
        this->packet[4] = 0xFF;
        this->packet[5] = 0xFF;
    } else {
        this->packet[3] = 0; // C means turn all motors on
        this->packet[4] = 0x00;
        this->packet[5] = 0x00;
    }
}

void Datapacket::setCollision(bool c, uint8_t b1, uint8_t b2){
    this->collision = c;
    this->packet[3] = 'c'; // c means check the next two bytes for which motors
    this->packet[4] = b1;
    this->packet[5] = b2;
}

void Datapacket::sendPacket(){
    this->arduino->serialport_write_teapot(this->packet);
}

void Datapacket::printPacket(){
    for(int i=2; i<10; i++){
        int c = this->packet[i];
        if(c) std::cout << c << ' ';
        else std::cout << '_';
    }
    std::cout << std::endl;
}
