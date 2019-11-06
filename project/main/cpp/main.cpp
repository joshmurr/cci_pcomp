#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <math.h>
#include "serial.h"
#include "screen.h"

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

    screen.setAnimating(true);
    ticks = SDL_GetTicks();

    running = arduino.setup(argc, argv);

    screen.hideCursor();

    SDL_Color WHITE       = screen.makeColor(255, 255, 255);
    SDL_Color RED         = screen.makeColor(255,   0,   0);
    SDL_Color ORANGE      = screen.makeColor(255, 128,   0);
    SDL_Color YELLOW      = screen.makeColor(255, 255,   0);
    SDL_Color LIGHT_GREEN = screen.makeColor(128, 255,   0);
    SDL_Color GREEN       = screen.makeColor(  0, 255,   0);
    SDL_Color TEAL        = screen.makeColor(  0, 255, 128);
    SDL_Color CYAN        = screen.makeColor(  0, 255, 255);
    SDL_Color LIGHT_BLUE  = screen.makeColor(  0, 128, 255);
    SDL_Color BLUE        = screen.makeColor(  0,   0, 255);
    SDL_Color MAGENTA     = screen.makeColor(255,   0, 255);
    SDL_Color PINK        = screen.makeColor(255,   0, 127);
    SDL_Color GREY        = screen.makeColor(128, 128, 128);

    // CIRCLE ANIMATION
    int r = 150;
    float theta = 0.0;
    int x, y;

    while(running && !screen.QUIT){
        screen.handleEvents();
        //screen.clearScreen();
        screen.drawChequeredBackround(RED, GREEN, BLUE, YELLOW);

        string input;
        int num;
        arduino.serialport_read_int_until('\n', data);

        x = r*cos(theta) + width/2;
        y = r*sin(theta) + height/2;

        if(x<width/2 && y<height/2){
            // TOP LEFT
            screen.bresenham_circle(x, y, 10, ORANGE);
            send_buf[0] = 'o';
            arduino.serialport_write(send_buf);
        } else if(x>width/2 && y<height/2) {
            // TOP RIGHT
            screen.bresenham_circle(x, y, 10, LIGHT_BLUE);
            send_buf[0] = 'x';
            arduino.serialport_write(send_buf);

        }else if(x<width/2 && y>height/2) {
            // BOTTOM LEFT
            screen.bresenham_circle(x, y, 10, LIGHT_GREEN);
            send_buf[0] = 'x';
            arduino.serialport_write(send_buf);

        } else {
            // BOTTOM RIGHT
            screen.bresenham_circle(x, y, 10, PINK);
            send_buf[0] = 'o';
            arduino.serialport_write(send_buf);
        }    

        theta += 0.05;

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
