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
#include "datapacket.h"

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
    Vec3d headsetOrigin = Vec3d(width/2.0, height/2.0, 20.0); 
    headset.makeHeadset(headsetOrigin);
    // MAKE ROOM
    Object room;
    room.makeSimpleRoom(Vec3d(width/2, height/2, -20.0), 200, 20);
    // MAKE SUN
    Object sun;
    Vec3d sunOrigin = Vec3d(width-100.0, 100.0, 30.0); 
    sun.makeSun(sunOrigin);

    //MAKE TARGET (to follow)
    Vec3d targetLoc = Vec3d(1 + width/2, 1 + height/2, 30); 
    screen.setTarget(targetLoc);

    // OFFSET FOR RESETTING HEADSET
    Vec3d targetOffset;
    // ------------------------------------------------------------------ //

    Quarternion quat;

    bool lookingAtSun = false;
    double lookingAtSunVal = 0.0;

    // DATA PACKET TO SEND TO ARDUINO ----------------------------------- //
    Datapacket data(arduino);
    data.setSynced(false);
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
    cout << endl;

    cout << "--- KEYBOARD CONTROLS ---\n";
    cout << "q - Quit\n";
    cout << "o - View headset origin\n";
    cout << "r - Rest headset position\n";
    cout << "t - Send trigger char to Arduino if not connecting\n";
    cout << "m - Toggle ALL motors on collision, or only colliding motors\n";
    cout << "d - Print data packet being sent to Arduino to console\n";
    cout << endl;

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

        targetLoc = screen.getTargetVec();
        targetOffset = targetLoc + Vec3d(1, 1, 0);

        if(screen.RESET_POS){
            headset.resetHeadsetPosition(targetLoc);
            screen.RESET_POS = false;
        }

        headset.draw(screen, screen.YELLOW);
        room.draw(screen, screen.RED);
        sun.draw(screen, screen.YELLOW);
        screen.draw3Dpoint(targetLoc, screen.GREY);
        headset.follow(targetOffset);
        //headset.follow(screen.getMouseVec());

        if(screen.DRAW_ORIGINS) headset.drawOrigin(screen);
        
        lookingAtSunVal = headset.lookingAtSun(sunOrigin);
        if(lookingAtSunVal < -0.7 && lookingAtSunVal > -1.3){
            double dVal = lookingAtSunVal + 1.3;
            dVal *= 1.67;
            dVal = 1.0 - dVal + 0.5;
            dVal *= dVal;
            if(dVal > 1.0) dVal = 1.0;
            if(dVal < 0) dVal = 0;
            int val = dVal * 255;

            data.lightsOn(val);
            lookingAtSun = true;
        } else {
            data.lightsOff();
            lookingAtSun = false;
        }

        if(!arduino.DEBUG){
            int n = arduino.serialport_read_teapot();
            //cout << n << endl;
            if(arduino.synced){
                data.setSynced(true);
                //cout << "SYNCED" << endl;
                quat.parseTeapotPacket(arduino.teapot);
                quat.toAxisAngle();
                //quat.printLongQuat();
                //quat.axisAngleTEST();
                headset.rotateAxisAngle(quat.axis);    
            }
        }

        uint16_t coll = headset.checkCollisions(screen, arduino, room, arduino.DEBUG, screen.ALL_MOTORS);
        uint8_t byte2 = coll;
        uint8_t byte1 = coll >> 8;

        if(!arduino.DEBUG){
            if(coll) data.setCollision(true, byte1, byte2);
            else data.setCollision(false);

            if(screen.PRINT_DATA_PACKET) data.printPacket();

            data.sendPacket();
        }
        
        // See bits to shift:
        //std::bitset<8> b1(byte1);
        //std::bitset<8> b2(byte2);
        //cout << "B1: " << b1 << '\n';
        //cout << "B2: " << b2 << endl;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
