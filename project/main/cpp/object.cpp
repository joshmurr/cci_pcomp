#include "object.h"

Object::Object(){
    this->velocity = 0.0;
}

Object::Object(std::vector<Vec3d> &points){
    referredPoints = &points;
}

void Object::draw(Screen &screen, SDL_Color col){
    screen.drawObject(this->points, this->origin, col);
}

void Object::update(){
    if(this->velocity){
        this->origin = this->origin + Vec3d(0.0, 0.1, 0.0);
    }

}

void Object::followMouse(const Vec3d _mouse){
    //this.p = p_;
    //this.dir = location.sub(this.p.location);
    //this.d = this.dir.length();
    //this.dir.normalise();
    //this.force = this.G/(this.mass*this.d*this.d);
    //this.dir.mult(this.force);
    //return this.dir;
    
    Vec3d dir = this->origin - _mouse;
    dir.normalise();
    this->origin = this->origin + dir; 

}

void Object::setVelocity(float v){
    this->velocity = v;
}

void Object::makeHeadset(Vec3d _origin){
    this->origin = _origin;
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

void Object::makeSimpleRoom(Vec3d _origin, float width, float spacing){
    this->origin = _origin;
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

void Object::makeStarField(float width, float height){
    for(int i=0; i<100; i++){
        Vec3d s(
            rand()%(int)width - width/2,
            rand()%(int)height - height/2,
            rand()%200 - 100
        );
        points.push_back(s);
    }
}