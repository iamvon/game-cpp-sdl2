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
#define BACKGROUND_SPEED 350
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
  bool collision (double x, double y, double xA_1, double yA_1);
  bool repairCollision(double x, double y, double xBuff, double yBuff);
  double xBg_1, yBg_1, xBg_2, yBg_2;
  double xA_1, yA_1, step, xRe, yRe;
  int kmCounter, angle, aScale;
  bool checkLeft, checkRight, checkPos, loser, play;
  int aWidth, aHeight, reWidth, reHeight; 
  int healthAmount; 
  bool checkCollision, checkRepair;
  int aError, error, countCollision;
  int goal;
 
  private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  int mouseX, mouseY;
  double x, y;
  Object bg1, bg2, asteroid1, health[5], repair;
  Object gameover, start;
  Entity ship, df, gg;
  Entity explosion;
  int ship_1, explosion_1;
};

#endif //GAME_H
