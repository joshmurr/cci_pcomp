#include "object.h"

Object::Object(){
    this->velocity = 0.0;
    this->dataArray[0] = 0x00; //0b00000000
    this->dataArray[1] = 0x80; //0b10000000
    this->dataArray[2] = 0x40; //0b01000000
    this->dataArray[3] = 0x20; //0b00100000
    this->dataArray[4] = 0x10; //0b00010000
    this->dataArray[5] = 0x08; //0b00001000
    this->dataArray[6] = 0x04; //0b00000100
    this->dataArray[7] = 0x02; //0b00000010
    this->dataArray[8] = 0x01; //0b00000001
}

Object::Object(std::vector<Vec3d> &points){
    referredPoints = &points;
}

void Object::draw(Screen &screen, const SDL_Color &col){
    screen.drawObject(this->points, this->origin, col);
}

void Object::update(){
    //if(this->velocity){
        //this->origin = this->origin + Vec3d(0.0, 0.1, 0.0);
    //}
}

void Object::rotateX(double theta){
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    for(std::vector<Vec3d>::iterator p=this->points.begin(); p!=this->points.end(); ++p){
        p->y = cosTheta*p->y - sinTheta*p->z;
        p->z = sinTheta*p->y + cosTheta*p->z;
    }
}

void Object::rotateY(double theta){
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    for(std::vector<Vec3d>::iterator p=this->points.begin(); p!=this->points.end(); ++p){
        p->x = cosTheta*p->x + sinTheta*p->z;
        p->z = cosTheta*p->z - sinTheta*p->x;
    }
}

void Object::rotateZ(double theta){
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    for(std::vector<Vec3d>::iterator p=this->points.begin(); p!=this->points.end(); ++p){
        p->x = cosTheta*p->x - sinTheta*p->y;
        p->y = sinTheta*p->x + cosTheta*p->y;
    }
}

void Object::rotateAxisAngle(double* axis){
    double theta = axis[0];
    double ax    = -axis[1];
    double ay    = axis[2];
    double az    = axis[3];

    if(isnan(theta) || isnan(ax) || isnan(ay) || isnan(az)) {
        std::cout<< "Found NaN" << std::endl;    
        return;
    }
    
    double cosT = cos(theta);
    double sinT = sin(theta);
    double t = 1.0 - cosT;

    double ax2 = ax*ax;
    double ay2 = ay*ay;
    double az2 = az*az;
    
    // Normalize Axis Components
    double mag = sqrt(ax2+ay2+az2);

    if(mag == 0) std::cout << "Magnitude is 0: ERROR!" << std::endl;
    else { 
        ax /= mag;
        ay /= mag;
        az /= mag;
    }

    //std::cout << ax + ay + az << std::endl;

    for(std::vector<Vec3d>::iterator p=this->points.begin(); p!=this->points.end(); ++p){
        // Store as temps:
        double tx = p->x;
        double ty = p->y;
        double tz = p->z;

        p->x = (cosT+ax2*t)*tx + (ax*ay*t-(az*sinT))*ty + (ax*az*t+(ay*sinT))*tz;
        p->y = (ay*ax*t+az*sinT)*tx + (cosT+ay2*t)*ty + (ay*az*t-(ax*sinT))*tz;
        p->z = (az*ax*t-(ay*sinT))*tx + (az*ay*t+(ax*sinT))*ty + (cosT+az2*t)*tz;
    }
}

void Object::follow(const Vec3d &v){
    Vec3d dir = this->origin - v;
    dir.normalise();
    this->origin = this->origin + dir; 
}

void Object::moveUpAndDown(const Uint32 &ticks){
    Vec3d ud(0.0, 0.0, 20.0*sin(ticks*0.01));
    this->origin = this->origin + ud; 
}

void Object::setVelocity(float v){
    this->velocity = v;
}

void Object::makeHeadset(Vec3d _origin){
    this->origin = _origin;
    float size = 20.0;
    int i=0;
    int num=8;
    double spacing = (M_PI * 2.0) / (float)num;
    //Main Ring
    for(; i<num; i++){
        double x = size * cos(spacing * i);
        double y = size * sin(spacing * i);
        Vec3d p(x, y, 0.0);
        points.push_back(p);
    }
    // Mid Ring
    size = 12.0;
    num = 6;
    spacing = (M_PI * 2.0) / (float)num;
    for(i=0; i<num; i++){
        double x = size * cos(spacing * i);
        double y = size * sin(spacing * i);
        Vec3d p(x, y, -4.0);
        points.push_back(p);
    }
    // Top
    Vec3d p(0.0, 0.0, -10.0);
    points.push_back(p);
    
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
        for(float z=0.0; z<width/2.0; z+=spacing){
            Vec3d p_L(-offset_x, offset_y-i, z);
            Vec3d p_R(offset_x, -offset_y+i, z);
            Vec3d p_T(-offset_x+i, -offset_y, z);
            Vec3d p_B(offset_x-i, offset_y, z);
            points.push_back(p_L);
            points.push_back(p_R);
            points.push_back(p_T);
            points.push_back(p_B);
        }
    }
}

bool Object::checkOriginCollision(Object &obj){
    double dist = this->origin.dist(obj.origin);
    if(dist < 10.0) return true;
    return false;
}

bool Object::checkCollisions(Screen &screen, Serial &arduino, Object &obj, bool DEBUG){
    unsigned char byte1 = 0x00, byte2 = 0x00;
    for(std::vector<Vec3d>::iterator p=this->points.begin(); p!=this->points.end(); ++p){
        for(std::vector<Vec3d>::iterator q=obj.points.begin(); q!=obj.points.end(); ++q){
            Vec3d pUpdate = *p + this->origin;
            Vec3d qUpdate = *q + obj.origin;
            double dist = pUpdate.dist(qUpdate);
            if(dist < 25.0) {
                screen.draw3Dline(pUpdate, qUpdate);
                // VIBRATE MOTORS
                int collision = p-points.begin();
                if(collision < 8) byte1 = byte1 + this->dataArray[p-points.begin()];
                else byte2 = byte2 + this->dataArray[p-points.begin()];
            }
        }
    }
    if(!DEBUG){
        arduino.serialport_writechar(byte1);
        arduino.serialport_writechar(byte2);
        byte1 = 0x00;
        byte2 = 0x00;
    }
    return false;
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
