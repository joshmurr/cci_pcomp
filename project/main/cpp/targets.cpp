#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>
#include <cmath>
#include "screen.h"
#include "targets.h"

Targets::Targets(int _cx, int _cy, int _numPoints, int _radius){
    cx = _cx;
    cy = _cy;
    numPoints = _numPoints;
    radius = _radius;

    makeTargets(targets);
}
void Targets::makeTargets(std::vector<Point> &targets){
    float theta = (2*M_PI)/numPoints;
    for(int i=0; i<numPoints; i++){
        Point p;
        p.x = (int)(radius * cos(i*theta))+cx;
        p.y = (int)(radius * sin(i*theta))+cy;
        targets.push_back(p);
    }
}

void Targets::draw(Screen &screen){
    for(std::vector<Point>::iterator it = targets.begin(); it!=targets.end(); ++it){
        screen.bresenham_circle(it->x, it->y, 10, screen.BLACK);
    }

}

unsigned char Targets::contact(int x, int y){
    float r_squared = radius*radius;
    for(std::vector<Point>::iterator it = targets.begin(); it!=targets.end(); ++it){
        float d_squared = (it->x - x)*(it->x - x) + (it->y - y)*(it->y - y);
        if(d_squared < radius) return it - targets.begin() + 1;
    }
    return 0;
}
