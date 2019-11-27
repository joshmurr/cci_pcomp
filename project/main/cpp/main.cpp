#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <math.h>
#include "serial.h"
#include "screen.h"
#include "targets.h"

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
    string send_string;
    char send_buf[256];
    int rc,n;
    bool init_done = false;
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

    Targets targets(width/2, height/2, 8, 150);

    // CIRCLE ANIMATION
    int r = 150;
    float theta = 0.0;
    int x, y;
    // 2nd CIRCLE ANIMATION
    float theta2 = 3.142;
    int x2, y2;

    while(running && !screen.QUIT){
        screen.handleEvents();
        screen.clearScreen();
        //screen.drawChequeredBackround(screen.RED, screen.GREEN, screen.BLUE, screen.YELLOW);
        targets.draw(screen);

        string input;
        int num;
        if(arduino.serialport_read_int_until('\n', data)){
            //cout << data << endl;
        }

        x = r*cos(theta) + width/2;
        y = r*sin(theta) + height/2;
        x2 = r*cos(theta2) + width/2;
        y2 = r*sin(theta2) + height/2;

        unsigned char whichTarget = targets.contact(x, y);
        unsigned char whichTarget2 = targets.contact(x2, y2);
        unsigned char prevTarget;
        unsigned char prevTarget2;
        arduino.serialport_writechar(dataArray[whichTarget] + dataArray[whichTarget2]);
        //if(prevTarget != whichTarget && !prevTarget) cout << "1: " << (int)whichTarget << endl;
        //if(prevTarget2 != whichTarget2 && !prevTarget2) cout << "2: " << (int)whichTarget2 << endl;

        prevTarget = whichTarget;
        prevTarget2 = whichTarget2;

        screen.bresenham_circle(x, y, 10, screen.PINK);
        screen.bresenham_circle(x2, y2, 10, screen.LIGHT_BLUE);
/*
 *        if(x<width/2 && y<height/2){
 *            // TOP LEFT
 *            screen.bresenham_circle(x, y, 10, screen.ORANGE);
 *            send_buf[0] = 'o';
 *            arduino.serialport_write(send_buf);
 *        } else if(x>width/2 && y<height/2) {
 *            // TOP RIGHT
 *            screen.bresenham_circle(x, y, 10, screen.LIGHT_BLUE);
 *            send_buf[0] = 'x';
 *            arduino.serialport_write(send_buf);
 *
 *        }else if(x<width/2 && y>height/2) {
 *            // BOTTOM LEFT
 *            screen.bresenham_circle(x, y, 10, screen.LIGHT_GREEN);
 *            send_buf[0] = 'x';
 *            arduino.serialport_write(send_buf);
 *
 *        } else {
 *            // BOTTOM RIGHT
 *            screen.bresenham_circle(x, y, 10, screen.PINK);
 *            send_buf[0] = 'o';
 *            arduino.serialport_write(send_buf);
 *        }    
 */

        theta += 0.006;
        theta2 -= 0.008;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        screen.update();

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
