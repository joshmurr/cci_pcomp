/*
 * screen.h
 *
 *  Created on: 23 Jul 2019
 *      Author: joshmurr
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "vec3d.h"
//#include "colors.h"

#define PI 3.14159265359

struct Star {
    float x;
    float y;
    float z;
};

class Screen {
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

    int COLS, ROWS;

    int RESOLUTION;
    int mouseX, mouseY;
    int mouseClickX, mouseClickY;

    double getRoseX(int, float, float, float);
    double getRoseY(int, float, float, float);

    void bresenham_draw_lines(int cx, int cy, int x, int y);
    void init_colors();

public:
	Screen();
    Screen(int width, int height, int res);
    bool QUIT;
    bool ANIMATING;
    int ANIMATION_RATE;
	bool init();
	void update();
    void clearScreen();
    void clearBlackScreen();
    void drawChequeredBackround(SDL_Color c1, SDL_Color c2, SDL_Color c3, SDL_Color c4);
    SDL_Color makeColor(Uint8 r, Uint8 g, Uint8 b);
    void hideCursor();
    void setAnimating(bool);
	void handleEvents();
    void displayGrid();
	void close();
    void writeInfo();
    void rect(int x, int y, int w, int h, SDL_Color color);
    void circle(float x, float y, float r, int segs);
    void rose(float x, float y, float r, float segs, float p1, float p2);
    void bresenham_circle(int cx, int cy, int r, SDL_Color color);
    
    // 3D Stuff:
    void draw3Dpoint(float x, float y, float z);
    void drawObject(std::vector<Vec3d> &obj, SDL_Color col);
    void starfield(std::vector<Star> &stars);

    int getWidth();
    int getHeight();

    float getMouseX();
    float getMouseY();

public:
    SDL_Color WHITE      ; 
    SDL_Color RED        ;
    SDL_Color ORANGE     ;
    SDL_Color YELLOW     ;
    SDL_Color LIGHT_GREEN;
    SDL_Color GREEN      ;
    SDL_Color TEAL       ;
    SDL_Color CYAN       ;
    SDL_Color LIGHT_BLUE ;
    SDL_Color BLUE       ;
    SDL_Color MAGENTA    ;
    SDL_Color PINK       ;
    SDL_Color GREY       ;
    SDL_Color BLACK      ;
};

#endif /* SCREEN_H_ */

