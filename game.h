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
#define FPS 60
#define IMG_SIZE_W 369
#define IMG_SIZE_H 388
const double SCALE = 0.4;
#define SHIP_SIZE_W IMG_SIZE_W*SCALE
#define SHIP_SIZE_H IMG_SIZE_H*SCALE
#define SHIP_SPEED 190
#define BACKGROUND_SPEED 400
#define ASTEROID_SIZE 145
#define HEALTH_SIZE  30
#define SHIP_SPEED_MOVE  8

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
  bool conllison (int x, int y, int &xA_1, int &yA_1);
  int xBg_1, yBg_1, xBg_2, yBg_2;
  int xA_1, yA_1;
  int kmCounter, angle, aScale;
  int hp;
  bool checkLeft, checkRight;
  int aWidth, aHeight;
  int healthAmount;
  int error;
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int count;
  int frameCount, timerFPS, lastFrame;
  int mouseX, mouseY;
  int x, y;
  Object ship, bg1, bg2, asteroid1, health[5];
  Object ship1,ship2,ship3,ship4,ship5,ship6,ship7,ship8;
  Entity gem;
  int gem_1;
};

#endif //GAME_H
