#include <vector>
#include "vec3d.h"

Vec3d::Vec3d(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vec3d::Vec3d(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

Vec3d Vec3d::operator+ (const Vec3d &v){
   return Vec3d(v.x + this->x, v.y + this->y, v.z + this->z); 
}

Vec3d Vec3d::operator- (const Vec3d &v){
   return Vec3d(v.x - this->x, v.y - this->y, v.z - this->z); 
}

Vec3d Vec3d::operator* (const Vec3d &v){
   return Vec3d(v.x * this->x, v.y * this->y, v.z * this->z); 
}

Vec3d Vec3d::operator/ (const Vec3d &v){
   return Vec3d(v.x / this->x, v.y / this->y, v.z / this->z); 
}

Vec3d Vec3d::abs(){
   return Vec3d(std::abs(this->x), std::abs(this->y), std::abs(this->z)); 
}

double Vec3d::dot (const Vec3d &v){
   return (v.x * this->x + v.y * this->y + v.z * this->z); 
}

double Vec3d::length(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

void Vec3d::normalise(){
    double len = this->length();
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

double Vec3d::dist(const Vec3d &v){
    return sqrt(pow((this->x-v.x), 2.0)+pow((this->y-v.y),2.0)+pow((this->z-v.z),2.0));
}
