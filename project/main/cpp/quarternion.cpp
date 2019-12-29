#include "quarternion.h"

Quarternion::Quarternion(){
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 0.0; 
}

Quarternion::Quarternion(double _x, double _y, double _z, double _w){
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->w = _w; 
}

double* Quarternion::quatToAxisAngle(){
    // [0] == Theta
    // [1] == ax
    // [2] == ay
    // [3] == az
      
    // If the Quaternion is [0,0,0.7071068,0.7071068]. You will get the Axis-Angle is [0,0,1] and degrees is 90. You could consider it rotated 90 degrees on Z axis.
    // https://stackoverflow.com/questions/52584715/how-can-i-convert-a-quaternion-to-an-angle
    
    static double axis[4] = {0.0,0.0,0.0,0.0};

    if(!this->x && !this->y && !this->z && !this->w) {
        return axis;
    } else {
        axis[0] = acos(this->w)*2.0; // Theta
        axis[1] = this->x / sin(acos(this->w));
        axis[2] = this->y / sin(acos(this->w));
        axis[3] = this->z / sin(acos(this->w));

        return axis;
    }
}
