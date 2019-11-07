#ifndef TARGETS_H_
#define TARGETS_H_

#include <vector>

struct Point {
    int x;
    int y;
};

class Targets{
    private:
        void makeTargets(std::vector<Point> &targets);

    public:
        Targets(int cx, int cy, int numPoints, int radius);

    private:
        int cx;
        int cy;
        int numPoints;
        int radius;

    public:
        std::vector<Point> targets;
        void draw(Screen &screen);
        unsigned char contact(int x, int y);

};


#endif
