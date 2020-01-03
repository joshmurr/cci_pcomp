#ifndef QUARTERNION_H_
#define QUARTERNION_H_

#include <math.h>
#include <cmath>
#include <stdint.h>
#include <iostream>
#include <list>

class Quarternion{
    private:
        double calculateMean(std::list<double> &list);

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
        void calculateQuatMean();

    private:
        static const double testQuat[];
        int avg_limit;
        std::list<double> w_avg;
        std::list<double> x_avg;
        std::list<double> y_avg;
        std::list<double> z_avg;

    public:
        double x;
        double y;
        double z;
        double w;
        double q[4];
        double axis[4];

        double w_AVG; 

};

#endif
