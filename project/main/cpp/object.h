#ifndef OBJECT_H_
#define OBJECT_H_

#define _USE_MATH_CONSTANTS

#include <vector>
#include <cmath>
#include "screen.h"
#include "vec3d.h"

class Object{
    public:
        Object(); // Blank Object
        Object(std::vector<Vec3d> &points); // Predefined points
        void draw(Screen &screen, SDL_Color col);
        void update();
        void setVelocity(float v);
        void setFollowMouse(bool t);
        void makeHeadset();
        void makeWall(Vec3d pos, float width, float height, float spacing);
        void makeSimpleRoom(float width, float spacing);
        void makeStarField(float width, float height);

    private:

    public:
        std::vector<Vec3d> points;
        std::vector<Vec3d> *referredPoints;

    private:
        Vec3d origin;
        float velocity;
        bool followMouse;

};

#endif
