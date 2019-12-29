#include "quarternion.h"

const double Quarternion::testQuat[] = {0.7071068, 0, 0, 0.7071068};

Quarternion::Quarternion(){
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1.0; 
}

Quarternion::Quarternion(double _x, double _y, double _z, double _w){
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->w = _w; 
}

void Quarternion::toAxisAngle(){
    // [0] == Theta
    // [1] == ax
    // [2] == ay
    // [3] == az
      
    // If the Quaternion is [0,0,0.7071068,0.7071068]. You will get the Axis-Angle is [0,0,1] and degrees is 90. You could consider it rotated 90 degrees on Z axis.
    // https://stackoverflow.com/questions/52584715/how-can-i-convert-a-quaternion-to-an-angle
    
    //static double axis[4] = {0.0,0.0,0.0,0.0};

    if(!this->x && !this->y && !this->z && !this->w) {
        //return axis;
    } else {
        this->axis[0] = acos(this->w)*2.0; // Theta
        this->axis[1] = this->x / sin(acos(this->w));
        this->axis[2] = this->y / sin(acos(this->w));
        this->axis[3] = this->z / sin(acos(this->w));

        //return axis;
    }
}

void Quarternion::TESTAxisAngle(){
    this->axis[0] = acos(this->testQuat[0])*2.0; // Theta
    this->axis[1] = testQuat[1] / sin(acos(this->testQuat[0]));
    this->axis[2] = testQuat[2] / sin(acos(this->testQuat[0]));
    this->axis[3] = testQuat[3] / sin(acos(this->testQuat[0]));
}

void Quarternion::parseTeapotPacket(uint8_t* teapot){
    // This is taken from Jeff Rowbergs MPUTeapot Processing sketch
    //
    // q[0] == w
    // q[1] == x
    // q[2] == y
    // q[3] == z
    
    this->q[0] = ((teapot[2] << 8) | teapot[3]) / 16384.0;
    this->q[1] = ((teapot[4] << 8) | teapot[5]) / 16384.0;
    this->q[2] = ((teapot[6] << 8) | teapot[7]) / 16384.0;
    this->q[3] = ((teapot[8] << 8) | teapot[9]) / 16384.0;
    for (int i = 0; i < 4; i++) if (q[i] >= 2) q[i] = -4 + q[i];

    this->w = q[0];
    this->x = q[1];
    this->y = q[2];
    this->z = q[3];
}

void Quarternion::printQuat() { 
    std::cout << "w: " << this->w << " x: " << this->x << " y: " << this->y << " z: " << this->z << std::endl;
}

void Quarternion::printAxis() { 
    std::cout << "Theta: " << this->axis[0] << " ax: " << this->axis[1] << " ay: " << this->axis[2] << " az: " << this->axis[3] << std::endl;
}
