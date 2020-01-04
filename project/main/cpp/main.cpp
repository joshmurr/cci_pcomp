#define _USE_MATH_CONSTANTS

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
    
    // MAKE OBJECTS ----------------------------------------------------- //
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
    // ------------------------------------------------------------------ //

    Quarternion quat;

    bool lookingAtSun = false;
    double lookingAtSunVal = 0.0;

    // DATA PACKETS TO SEND TO ARDUINO ---------------------------------- //
    uint8_t lightsOn[8] = {'l', 'v', 0, 0, 0, 0, 0, 0};
    uint8_t lightsOff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    // ------------------------------------------------------------------ //

    if(!arduino.DEBUG){
        // Trigger MPU:
        cout << "Triggering MPU..." << endl;
        arduino.serialport_writechar(trigger);
        usleep(100000);
        cout << "Waiting for response from MPU" << endl;
        //arduino.serialport_read_until('\n');
        //cout << "End of setup." << endl;
    }

    cout << "Running..." << endl;
    while(running  && !screen.QUIT){
        // CHECK INTERVALS AND RESEND TRIGGER TO MPU IF NEEDED -------------- //
        if(!arduino.DEBUG && ticks - interval > 5000 && !arduino.synced) {
            cout << "Not yet synced, re-sending trigger..." << endl;
            arduino.serialport_writechar(trigger);
            interval = ticks;
        }
        if(!arduino.DEBUG && ticks - interval > 100000 && !arduino.synced) {
            cout << "Long interval, re-sending trigger..." << endl;
            arduino.serialport_writechar(trigger);
            interval = ticks;
        }
        if(screen.SEND_TRIGGER){
            cout << "User re-sending trigger..." << endl;
            arduino.serialport_writechar(trigger);
            screen.SEND_TRIGGER = false;
        }
        // ------------------------------------------------------------------ //
        
        screen.handleEvents();
        screen.clearBlackScreen();

        if(screen.RESET_POS){
            headset.resetHeadsetPosition(headsetOrigin);
            screen.RESET_POS = false;
        }

        targetLoc = screen.getTargetVec();

        headset.draw(screen, screen.YELLOW);
        headset.drawOrigin(screen);
        room.draw(screen, screen.RED);
        sun.draw(screen, screen.YELLOW);
        screen.draw3Dpoint(targetLoc);
        headset.follow(targetLoc);
        //headset.follow(screen.getMouseVec());
        
        lookingAtSunVal = headset.lookingAtSun(sunOrigin);
        if(lookingAtSunVal < -0.7 && lookingAtSunVal > -1.3){
            double dVal = lookingAtSunVal + 1.3;
            dVal *= 1.67;
            dVal = 1.0 - dVal + 0.5;
            dVal *= dVal;
            if(dVal > 1.0) dVal = 1.0;
            if(dVal < 0) dVal = 0;
            int val = dVal * 255;
            cout << val << endl;
            lightsOn[2] = val;
            lookingAtSun = true;
        } else {
            lightsOn[3] = 0;
            lookingAtSun = false;
        }

        if(!arduino.DEBUG){
            int n = arduino.serialport_read_teapot();
            //cout << n << endl;
            if(arduino.synced){
                //cout << "SYNCED" << endl;
                quat.parseTeapotPacket(arduino.teapot);
                quat.toAxisAngle();
                //quat.printLongQuat();
                //quat.axisAngleTEST();
                headset.rotateAxisAngle(quat.axis);    
            }
        }

        //bool collision = headset.checkCollisions(screen, arduino, room, arduino.DEBUG);
        //if(lookingAtSun) arduino.serialport_writechar(0xFF);

        if(lookingAtSun) arduino.serialport_write_teapot(lightsOn);
        else if(!lookingAtSun) arduino.serialport_write_teapot(lightsOff);

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
