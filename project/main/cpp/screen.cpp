/*
 * screen.cpp
 *
 *  Created on: 23 Jul 2019
 *      Author: joshmurr
 */

#include "screen.h"

Screen::Screen(){
    m_window = NULL;
    m_renderer = NULL;
    SCREEN_WIDTH = 800;
    SCREEN_HEIGHT = 600;
    RESOLUTION = 20;
    ANIMATING = false;
    ANIMATION_RATE = 60; // 50 mSeconds
    QUIT = false;
}

Screen::Screen(int width, int height, int res){
    m_window = NULL;
    m_renderer = NULL;
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    RESOLUTION = res;
    ANIMATING = false;
    ANIMATION_RATE = 50; // 50 mSeconds
    QUIT = false;
}


bool Screen::init() {
    // Init library, exit and log if failed
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init - SDL_Init: %s\n", SDL_GetError());
		return false;
	}

    // Try to create window, log and exit if failed
    if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &m_window, &m_renderer) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init - SDL_CreateWindowAndRenderer: %s\n", SDL_GetError());
        return false;
    }

    COLS = SCREEN_WIDTH/RESOLUTION;
    ROWS = SCREEN_HEIGHT/RESOLUTION;
    init_colors();
    return true;
}


void Screen::handleEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            QUIT = true;
        } else if (event.type == SDL_MOUSEMOTION){
            // Mouse Move
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            // Mouse DRAG
            if(event.motion.state & (SDL_BUTTON_LMASK | SDL_BUTTON_RMASK)){
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN){
            // Mouse CLICK
            mouseClickX = event.motion.x;
            mouseClickY = event.motion.y;
            
        } else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_SPACE){
                // SPACEBAR
                ANIMATING = false;
            } else if (event.key.keysym.sym == SDLK_c) {
                // c Button
            } else if (event.key.keysym.sym == SDLK_q){
                ANIMATING = false;
                QUIT = true;
            }
        }
    }
}

void Screen::clearScreen(){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void Screen::clearBlackScreen(){
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void Screen::init_colors(){
    WHITE       = makeColor(255, 255, 255);
    RED         = makeColor(255,   0,   0);
    ORANGE      = makeColor(255, 128,   0);
    YELLOW      = makeColor(255, 255,   0);
    LIGHT_GREEN = makeColor(128, 255,   0);
    GREEN       = makeColor(  0, 255,   0);
    TEAL        = makeColor(  0, 255, 128);
    CYAN        = makeColor(  0, 255, 255);
    LIGHT_BLUE  = makeColor(  0, 128, 255);
    BLUE        = makeColor(  0,   0, 255);
    MAGENTA     = makeColor(255,   0, 255);
    PINK        = makeColor(255,   0, 127);
    GREY        = makeColor(128, 128, 128);
    BLACK       = makeColor(  0,   0,   0);
}

void Screen::drawChequeredBackround(SDL_Color c1, SDL_Color c2, SDL_Color c3, SDL_Color c4){
    rect(0,0,SCREEN_WIDTH/2, SCREEN_HEIGHT/2, c1);
    rect(SCREEN_WIDTH/2, 0,SCREEN_WIDTH/2, SCREEN_HEIGHT/2, c2);
    rect(0,SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, c3);
    rect(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, c4);
}

void Screen::setAnimating(bool animating){
    ANIMATING = animating;
}

SDL_Color Screen::makeColor(Uint8 r, Uint8 g, Uint8 b){
    SDL_Color c = {r,g,b};
    return c;
}

void Screen::hideCursor(){
    SDL_ShowCursor(SDL_DISABLE);
}


void Screen::displayGrid(){
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // Draw row lines
    for(int i=0; i<ROWS; i++){
        SDL_RenderDrawLine(m_renderer, 0, RESOLUTION*i, SCREEN_WIDTH, RESOLUTION*i);
    }
    // Draw col lines
    for(int i=0; i<COLS; i++){
        SDL_RenderDrawLine(m_renderer, RESOLUTION*i, 0, RESOLUTION*i, SCREEN_HEIGHT);
    }
}

void Screen::circle(float x, float y, float r, int segs){
    float spacing = (PI*2)/segs;
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    float currentX = x+(cos(0) * r);
    float currentY = y+(sin(0) * r);
    for(int i=0; i<segs; i++){
        float nextX = x+(cos(spacing * i) * r);
        float nextY = y+(sin(spacing * i) * r);
        SDL_RenderDrawLine(m_renderer, currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;
    }
    SDL_RenderDrawLine(m_renderer, currentX, currentY, x+(cos(0) * r), y+(sin(0) * r));
}

void Screen::bresenham_draw_lines(int cx, int cy, int x, int y){
    SDL_RenderDrawLine(m_renderer, cx-x, cy-y, cx+x, cy-y);
    SDL_RenderDrawLine(m_renderer, cx-y, cy+x, cx+y, cy+x);
    SDL_RenderDrawLine(m_renderer, cx-y, cy-x, cx+y, cy-x);
    SDL_RenderDrawLine(m_renderer, cx-x, cy+y, cx+x, cy+y);
}

void Screen::bresenham_circle(int cx, int cy, int r, SDL_Color color){
    int x = 0, y = r;
    int d = 3 - 2*r;

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

    bresenham_draw_lines(cx, cy, x, y);
    while(y>=x){
        x++;
        if(d > 0){
            y--;
            d = d + 4*(x-y)+10;
        } else {
            d = d + 4*x + 6;
        }
        bresenham_draw_lines(cx, cy, x, y);
    }
}

double Screen::getRoseX(int i, float s, float p1, float p2){
    return sin(i*s*p1)*cos(i*s*p2);
}
double Screen::getRoseY(int i, float s, float p1, float p2){
    return sin(i*s*p1)*sin(i*s*p2);
}

void Screen::rose(float x, float y, float r, float segs, float p1, float p2){
    float spacing = (PI*2)/segs;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    float currentX = x + getRoseX(0, spacing, p1, p2)*r;
    float currentY = y + getRoseY(0, spacing, p1, p2)*r;

    for(int i=0; i<segs; i++){
        float nextX = x + getRoseX(i, spacing, p1, p2)*r;
        float nextY = y + getRoseY(i, spacing, p1, p2)*r;
        SDL_RenderDrawLine(m_renderer, currentX, currentY, nextX, nextY);
        currentX = nextX;
        currentY = nextY;
    }
    SDL_RenderDrawLine(m_renderer, currentX, currentY, x + getRoseX(0, spacing, p1, p2)*r, y+getRoseY(0, spacing, p1, p2)*r);
}

float Screen::getMouseX(){
    return mouseX;
}

float Screen::getMouseY(){
    return mouseY;
}

void Screen::draw3Dpoint(float x, float y, float z){
    float FOV = 200.0;

    float scale = FOV / (FOV + z);

    float x2d = (x*scale)+SCREEN_WIDTH/2;
    float y2d = (y*scale)+SCREEN_HEIGHT/2;

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(m_renderer, x2d-scale, y2d, x2d+scale, y2d);
    SDL_RenderDrawLine(m_renderer, x2d, y2d-scale, x2d, y2d+scale);
}

void Screen::starfield(std::vector<Star> &stars){
    float FOV = 200.0;
    float x3d=0.0, y3d=0.0, z3d=0.0;
    for(std::vector<Star>::iterator s=stars.begin(); s!=stars.end(); ++s){
        z3d = s->z;
        z3d -= 2.0;
        if(z3d < -FOV) z3d += SCREEN_WIDTH/2;
        s->z = z3d;

        x3d = s->x;
        y3d = s->y;
        
        float scale = FOV / (FOV + z3d);
        float x2d = (x3d*scale)+SCREEN_WIDTH/2;
        float y2d = (y3d*scale)+SCREEN_HEIGHT/2;

        int dColor = 255 - floor(z3d + 200);
        if(dColor < 1) dColor = 0;
        if(dColor > 254) dColor = 255;

        SDL_SetRenderDrawColor(m_renderer, dColor, dColor, dColor, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(m_renderer, x2d-scale, y2d, x2d+scale, y2d);
        SDL_RenderDrawLine(m_renderer, x2d, y2d-scale, x2d, y2d+scale);
    }

}

void Screen::writeInfo(){
    std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << '\n';
    std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << '\n';
    std::cout << "COLS: " << COLS << " ROWS: " << ROWS << '\n';
    std::cout <<"RESOLUTION: " << RESOLUTION << std::endl;
}


/*void Screen::clear() {
 *    memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
 *}
 */

void Screen::update() {
	SDL_RenderPresent(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 200, 255);
	SDL_RenderClear(m_renderer);
}

void Screen::rect(int x, int y, int w, int h, SDL_Color color){
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Screen::close() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

int Screen::getWidth(){
    return SCREEN_WIDTH;
}

int Screen::getHeight(){
    return SCREEN_HEIGHT;
}
