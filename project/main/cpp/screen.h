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
    double x;
    double y;
    double z;
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
    Vec3d mouseVec;
    Vec3d targetVec;
    int mouseClickX, mouseClickY;

    double getRoseX(int, double, double, double);
    double getRoseY(int, double, double, double);

    void bresenham_draw_lines(int cx, int cy, int x, int y);
    void init_colors();

public:
	Screen();
    Screen(int width, int height, int res);
    bool QUIT;
    bool ANIMATING;
    bool RESET_POS;
    bool SEND_TRIGGER;
    bool ALL_MOTORS;
    bool DRAW_ORIGINS;
    bool PRINT_DATA_PACKET;
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
    void drawLine(const Vec3d &v1, const Vec3d &v2, const SDL_Color col);
    void rect(int x, int y, int w, int h, SDL_Color color);
    void circle(double x, double y, double r, int segs);
    void rose(double x, double y, double r, double segs, double p1, double p2);
    void bresenham_circle(int cx, int cy, int r, SDL_Color color);
    
    // 3D Stuff:
    void draw3Dpoint(const Vec3d &v, const SDL_Color col);
    void drawObject(std::vector<Vec3d> &obj, const Vec3d &_origin, const SDL_Color &col);
    void draw3Dline(const Vec3d &v1, const Vec3d &v2, const SDL_Color col);
    void starfield(std::vector<Star> &stars);

    int getWidth();
    int getHeight();

    double getMouseX();
    double getMouseY();
    Vec3d getMouseVec();
    Vec3d getTargetVec();

    void setTarget(Vec3d loc);
    void printTarget();

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

