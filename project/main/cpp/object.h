#ifndef OBJECT_H_
#define OBJECT_H_

#define _USE_MATH_CONSTANTS

#include <vector>
#include <cmath>
#include "screen.h"
#include "serial.h"
#include "vec3d.h"

class Object{
    public:
        Object(); // Blank Object
        Object(std::vector<Vec3d> &points); // Predefined points
        void draw(Screen &screen, SDL_Color col);
        void update();
        void setVelocity(float v);
        //void setFollowMouse(bool t);
        void follow(const Vec3d &v);
        void makeHeadset(Vec3d _origin);
        void makeWall(Vec3d pos, float width, float height, float spacing);
        void makeSimpleRoom(Vec3d _origin, float width, float spacing);
        bool checkCollisions(Screen &screen, Serial &arduino, Object &obj);
        bool checkOriginCollision(Object &obj);
        void makeStarField(float width, float height);

    private:

    public:
        std::vector<Vec3d> points;
        std::vector<Vec3d> *referredPoints;

    private:
        Vec3d origin;
        float velocity;
        //bool followMouse;
        unsigned char dataArray[9];


};

#endif
