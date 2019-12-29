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

    int width = screen.getWidth();
    int height = screen.getHeight();

    screen.setAnimating(true);
    ticks = SDL_GetTicks();

    running = arduino.setup(argc, argv);

    screen.hideCursor();
    
    // MAKE RING
    Object headset;
    headset.makeHeadset(Vec3d(width/2.0, height/2.0, 50.0));
    // MAKE ROOM
    Object room;
    room.makeSimpleRoom(Vec3d(width/2, height/2, 0.0), 200, 20);

    Quarternion quat;

    while(running  && !screen.QUIT){
        screen.handleEvents();
        screen.clearBlackScreen();

        if(arduino.serialport_read_teapot()){
            //cout << arduino.teapot << endl;
            quat.parseTeapotPacket(arduino.teapot);
        }
        
        quat.print();

        headset.draw(screen, screen.YELLOW);
        room.draw(screen, screen.RED);
        headset.follow(screen.getMouseVec());

        //headset.moveUpAndDown(ticks);
        headset.update();

        if(headset.checkCollisions(screen, arduino, room, arduino.DEBUG)) cout << "Collision!" << std::endl;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
