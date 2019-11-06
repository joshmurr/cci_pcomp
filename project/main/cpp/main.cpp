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

    screen.setAnimating(true);
    ticks = SDL_GetTicks();

    running = arduino.setup(argc, argv);

    SDL_Color RED = screen.makeColor(255, 0, 0);
    SDL_Color GREEN = screen.makeColor(0, 255, 0);
    SDL_Color BLUE = screen.makeColor(0, 0, 255);

    screen.hideCursor();

    while(running && !screen.QUIT){
        screen.handleEvents();
        screen.clearScreen();

        string input;
        int num;
        arduino.serialport_read_int_until('\n', data);

        /*
         *if(data%64==0){
         *    send_buf[0] = 'b';
         *    arduino.serialport_write(send_buf);
         *    cout << "BLUE toggle" << endl;
         *}
         *if(data%89==0) {
         *    send_buf[0] = 'g';
         *    arduino.serialport_write(send_buf);
         *    cout << "GREEN toggle" << endl;
         *}
         *if(data%37==0) {
         *    send_buf[0] = 'r';
         *    arduino.serialport_write(send_buf);
         *    cout << "RED toggle" << endl;
         *}
         */

        if(screen.getMouseX() < screen.getWidth() / 2){
            screen.bresenham_circle(screen.getMouseX(), screen.getMouseY(), 10, RED);
        } else {
            screen.bresenham_circle(screen.getMouseX(), screen.getMouseY(), 10, BLUE);
        }

        if(screen.ANIMATING && (SDL_GetTicks() - ticks) > screen.ANIMATION_RATE){
            ticks = SDL_GetTicks();
        }

        usleep(10000);
    }

    screen.close();

    exit(EXIT_SUCCESS);    
} 
    
