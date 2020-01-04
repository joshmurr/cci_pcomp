#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <math.h>
#include "serial.h"
#include "screen.h"
#include "vec3d.h"
#include "targets.h"
#include "object.h"
#include "quarternion.h"

using namespace std;


int main(int argc, char *argv[]) {
    Serial arduino(argc, argv);
    Screen screen(600, 400, 10);
    Uint32 ticks;

    if (argc==1) {
        exit(EXIT_SUCCESS);
    }

    if(!screen.init()){
        cout << "Error initializing SDL..." << endl;
        exit(EXIT_SUCCESS);
    }

    bool running = false;
    char trigger = 'r';
    int interval = 0;

    int width = screen.getWidth();
    int height = screen.getHeight();

    screen.setAnimating(true);
    ticks = SDL_GetTicks();

    running = arduino.setup(argc, argv);

    //screen.hideCursor();
    
    // MAKE RING
    Object headset;
    Vec3d headsetOrigin = Vec3d(width/2.0, height/2.0, 10.0); 
    headset.makeHeadset(headsetOrigin);
    // MAKE ROOM
    Object room;
    room.makeSimpleRoom(Vec3d(width/2, height/2, 0.0), 200, 20);
    // MAKE SUN
    Object sun;
    Vec3d sunOrigin = Vec3d(100.0, 100.0, 0.0); 
    sun.makeSun(sunOrigin);

    //MAKE TARGET (to follow)
    Vec3d targetLoc = Vec3d(200.0, 200.0, 0.0); 
    screen.setTarget(targetLoc);

    Quarternion quat;

    double lookingAtSunVal = 0.0;

    if(!arduino.DEBUG){
        // Trigger MPU:
        arduino.serialport_writechar(trigger);
        usleep(100000);
        cout << "Waiting for response from MPU" << endl;
        //arduino.serialport_read_until('\n');
        //cout << "End of setup." << endl;
    }

    cout << "Running..." << endl;
    while(running  && !screen.QUIT){
        if(!arduino.DEBUG && ticks - interval > 10000) {
            cout << "Re-sending trigger" << endl;
            arduino.serialport_writechar(trigger);
            interval = ticks;
        }
        screen.handleEvents();
        screen.clearBlackScreen();

        if(screen.RESET_POS){
            headset.resetHeadsetPosition(headsetOrigin);
            screen.RESET_POS = false;
        }

        headset.draw(screen, screen.YELLOW);
        headset.drawOrigin(screen);
        room.draw(screen, screen.RED);
        sun.draw(screen, screen.YELLOW);
        screen.draw3Dpoint(screen.getTargetVec());
        headset.follow(screen.getTargetVec());
        //headset.follow(screen.getMouseVec());

        if(!arduino.DEBUG){
            arduino.serialport_read_teapot();
            //cout << arduino.buf << endl;
            if(arduino.synced){
                quat.parseTeapotPacket(arduino.teapot);
                quat.toAxisAngle();
                //quat.printLongQuat();
                //quat.axisAngleTEST();
                headset.rotateAxisAngle(quat.axis);    
            }
        }

        //if(headset.checkCollisions(screen, arduino, room, arduino.DEBUG)) cout << "Collision!" << std::endl;
        lookingAtSunVal = headset.lookingAtSun(sunOrigin);
        if(lookingAtSunVal > -0.95 && lookingAtSunVal < -1.05) cout << "Looking at sun" << endl;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
