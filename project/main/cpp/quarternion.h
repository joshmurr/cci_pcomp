#ifndef QUARTERNION_H_
#define QUARTERNION_H_

#include <math.h>
#include <cmath>

class Quarternion{
    private:

    public:
        Quarternion();
        Quarternion(double _x, double _y, double _z, double _w);
        double* quatToAxisAngle();

    private:

    public:
        double x;
        double y;
        double z;
        double w;

};

#endif
