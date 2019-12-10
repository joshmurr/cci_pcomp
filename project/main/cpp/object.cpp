#include "object.h"

Object::Object(){

}

Object::Object(std::vector<Vec3d> &points){
    referredPoints = &points;
}

void Object::draw(Screen &screen, SDL_Color col){
    screen.drawObject(this->points, col);
}

void Object::makeHeadset(){
    float size = 20.0;
    double spacing = (M_PI * 2.0) / 8.0;
    for(int i=0; i<8; i++){
        double x = size * cos(spacing * i);
        double y = size * sin(spacing * i);
        Vec3d p(x, y, 20.0);
        points.push_back(p);
    }
}

void Object::makeWall(Vec3d pos, float width, float height, float spacing){
    //float height = 200.0;
    //float width = 200.0;
    //float spacing = 20.0;
    float origin_x = -width/2;
    float origin_y = -height/2;
    for(float i=0.0; i<width; i+=spacing){
        for(float j=0.0; j<height; j+=spacing){
            Vec3d p(i+origin_x, origin_y, j);
            points.push_back(p);
        }
    }

}

void Object::makeSimpleRoom(float width, float spacing){
    float offset_x = width/2.0;
    float offset_y = width/2.0;
    for(float i=0.0; i<width; i+=spacing){
        Vec3d p_L(-offset_x, -offset_y+i, 0.0);
        Vec3d p_R(offset_x, -offset_y+i, 0.0);
        Vec3d p_T(-offset_x+i, -offset_y, 0.0);
        Vec3d p_B(-offset_x+i, offset_y, 0.0);
        points.push_back(p_L);
        points.push_back(p_R);
        points.push_back(p_T);
        points.push_back(p_B);
    }
}
