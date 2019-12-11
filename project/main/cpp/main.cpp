#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <math.h>
#include "serial.h"
#include "screen.h"
#include "vec3d.h"
#include "targets.h"
#include "object.h"

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

    int data;
    bool running = false;

    int width = screen.getWidth();
    int height = screen.getHeight();

    unsigned char dataArray[9];

    dataArray[0] = 0x00; //0b00000000
    dataArray[1] = 0x80; //0b10000000
    dataArray[2] = 0x40; //0b01000000
    dataArray[3] = 0x20; //0b00100000
    dataArray[4] = 0x10; //0b00010000
    dataArray[5] = 0x08; //0b00001000
    dataArray[6] = 0x04; //0b00000100
    dataArray[7] = 0x02; //0b00000010
    dataArray[8] = 0x01; //0b00000001

    screen.setAnimating(true);
    ticks = SDL_GetTicks();

    running = arduino.setup(argc, argv);

    screen.hideCursor();
    
    // MAKE RING
    Object headset;
    headset.makeHeadset(Vec3d(100.0, 100.0, 0.0));
    // MAKE ROOM
    Object room;
    room.makeSimpleRoom(Vec3d(width/2, height/2, 0.0), 200, 20);

    Targets targets(width/2, height/2, 8, 150);


    while(running && !arduino.DEBUG && !screen.QUIT){
        screen.handleEvents();
        screen.clearBlackScreen();

        if(arduino.serialport_read_int_until('\n', data)){
            //cout << data << endl;
        }

        headset.draw(screen, screen.YELLOW);
        room.draw(screen, screen.RED);
        headset.follow(Vec3d(screen.getMouseX(), screen.getMouseY(), 0.0));
        headset.update();

        if(headset.checkCollisions(screen, arduino, room)) cout << "Collision!" << std::endl;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }


    while(running && arduino.DEBUG && !screen.QUIT){
        screen.handleEvents();
        screen.clearBlackScreen();

        headset.draw(screen, screen.YELLOW);
        room.draw(screen, screen.RED);
        headset.follow(Vec3d(screen.getMouseX(), screen.getMouseY(), 0.0));
        headset.update();

        if(headset.checkCollisions(screen, arduino, room)) cout << "Collision!" << std::endl;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
