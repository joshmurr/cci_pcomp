#ifndef QUARTERNION_H_
#define QUARTERNION_H_

#include <math.h>
#include <cmath>
#include <stdint.h>
#include <iostream>

class Quarternion{
    private:

    public:
        Quarternion();
        Quarternion(double _x, double _y, double _z, double _w);
        //double* quatToAxisAngle();
        void toAxisAngle();
        void parseTeapotPacket(uint8_t* teapot);
        void printQuat();
        void printAxis();

    private:

    public:
        double x;
        double y;
        double z;
        double w;
        double q[4];
        double axis[4];

};

#endif
