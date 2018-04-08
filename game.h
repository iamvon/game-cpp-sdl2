#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "object.h"
#include "entity.h"

#define WIDTH 550
#define HEIGHT 1000
#define FONT_SIZE 28
#define FPS 70
#define IMG_SIZE 300
const double SCALE = 0.5;
#define SHIP_SIZE IMG_SIZE*SCALE
#define SHIP_SPEED 190
#define BACKGROUND_SPEED 400
#define ASTEROID_SIZE 250

class Game {
public:
  Game();
  ~Game();
  void loop();
  void update();
  void input();
  void render();
  void draw(Object obj);
  void drawSpin(Object obj, int angle);
  void drawMsg(const char* msg, int x, int y, int r, int g, int b);
  int xBg_1, yBg_1, xBg_2, yBg_2;
  int xA_1, yA_1;
  int kmCounter, angle, aScale;
  int hp;
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int count;
  int frameCount, timerFPS, lastFrame;
  int mouseX, mouseY;
  int x, y;
  Object ship, bg1, bg2, asteroid1, health;
  Entity gem;
  int gem_1;
};

#endif //GAME_H
