#ifndef MESSAGE_H
#define MESSAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Message {
public:
    void drawMsg(const char* msg, int x, int y, int r, int g, int b);
    void drawMsgLarge(const char* msg, int x, int y, int r, int g, int b);
private:
    SDL_Renderer* ren;
    const char* msg; 
    int x, y, r, g, b;
};

#endif //MESSAGE_H
