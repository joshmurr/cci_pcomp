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
        void printLongQuat();
        void printAxis();
        void TESTAxisAngle();
        void axisAngleTEST();
        void normalise();

    private:
        static const double testQuat[];

    public:
        double x;
        double y;
        double z;
        double w;
        float q[4];
        float axis[4];

};

#endif
