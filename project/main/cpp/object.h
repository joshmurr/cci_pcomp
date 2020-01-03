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
        void draw(Screen &screen, const SDL_Color &col);
        void drawOrigin(Screen &screen);
        void update();
        void setVelocity(double v);
        //void setFollowMouse(bool t);
        void follow(const Vec3d &v);
        void rotateX(double theta);
        void rotateY(double theta);
        void rotateZ(double theta);
        void rotateYPR(double* q);
        void rotateAxisAngle(double* axis);
        void makeHeadset(Vec3d _origin);
        void resetHeadsetPosition(Vec3d _origin);
        void makeWall(Vec3d pos, double width, double height, double spacing);
        void makeSimpleRoom(Vec3d _origin, double width, double spacing);
        bool checkCollisions(Screen &screen, Serial &arduino, Object &obj, bool DEBUG);
        bool checkOriginCollision(Object &obj);
        void makeStarField(double width, double height);

        void moveUpAndDown(const Uint32 &ticks);


    private:

    public:
        std::vector<Vec3d> points;
        std::vector<Vec3d> axes;
        std::vector<Vec3d> *referredPoints;

    private:
        Vec3d origin;
        double velocity;
        //bool followMouse;
        double oldTheta;
        unsigned char dataArray[9];
        double gravity[3];
        double ypr[3];


};

#endif
