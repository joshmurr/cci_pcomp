/*
 * screen.h
 *
 *  Created on: 23 Jul 2019
 *      Author: joshmurr
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
//#include "colors.h"

#define PI 3.14159265359

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

public:
	Screen();
    Screen(int width, int height, int res);
    bool QUIT;
    bool ANIMATING;
    int ANIMATION_RATE;
	bool init();
	void update();
    void clearScreen();
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

    int getWidth();
    int getHeight();

    float getMouseX();
    float getMouseY();

public:

};

#endif /* SCREEN_H_ */
