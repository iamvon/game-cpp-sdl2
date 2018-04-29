#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "object.h"
#include "entity.h"

#define WIDTH 580
#define HEIGHT 960
#define FONT_SIZE 28
#define FPS 50
#define IMG_SIZE_W 512
#define IMG_SIZE_H 512
const double SCALE = 0.35;
#define SHIP_SIZE_W IMG_SIZE_W*SCALE
#define SHIP_SIZE_H IMG_SIZE_H*SCALE
#define SHIP_SPEED 190
#define BACKGROUND_SPEED 400
#define ASTEROID_SIZE 350
#define HEALTH_SIZE  30
#define SHIP_SPEED_MOVE  12

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
  void resetAsteroid(double &xA_1, double &yA_1, int &aScale, double &step);
  bool collision (double x, double y, double xA_1, double yA_1);
  bool repairCollision(double x, double y, double xBuff, double yBuff);
  bool shootingCollision(double xFire, double yFire, double fireWidth, double fireHeight, double xA_1, double yA_1);
  double xBg_1, yBg_1, xBg_2, yBg_2;
  double xA_1, yA_1, step, xRe, yRe, xA_1Last, yA_1Last;
  int kmCounter, angle, aScale;
  bool checkLeft, checkRight, checkPos, loser, play;
  int aWidth, aHeight, reWidth, reHeight; 
  int healthAmount, fireAmount, countShooting; 
  bool checkCollision, checkRepair, shooting, checkShooting;
  int aError, error, countCollision, countShootingConllision;
  int goal;
  double xFire[27], yFire[27], fireWidth[27], fireHeight[27], fireScale;
  string explosionPath; 
 
  private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  int mouseX, mouseY;
  int ship_1, explosion_1, blue_1, fire_1[27];
  double x, y, xLast, yLast;
  Object bg1, bg2, asteroid1, health[5], repair, bulletCur;
  Object gameover, start;
  Object fire[27];
  Entity blue, kk; 
  Entity explosion;
  Entity ship, hh;
};

#endif //GAME_H
