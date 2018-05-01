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
#define BULLET_BUFF_SIZE  100
#define WORM_HOLE_SIZE  200 

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
  void resetAsteroid1(double &xA_1, double &yA_1, int &aScale1, double &step1);
  void resetAsteroid2(double &xA_2, double &yA_2, int &aScale2, double &step2);
  void wormHoleTeleportShip(Object &ship, double &x, double &y, int &width, int &height, double xWormHole, double yWormHole);
  bool collision(double x, double y, double xA, double yA, double aWidth, double aHeight);
  bool buffCollision(double x, double y, double xBuff, double yBuff);
  bool shootingCollision(double xFire, double yFire, double fireWidth, double fireHeight, double xA, double yA, double aWidth, double aHeight);
  double xBg_1, yBg_1, xBg_2, yBg_2, xBulletBuff, yBulletBuff;
  double xA_1, yA_1, xA_2, yA_2, step1, step2, xRe, yRe, xA_1Last, yA_1Last, offset;
  int kmCounter, aScale1, aScale2;
  bool checkLeft, checkRight, checkPos1, checkPos2, loser, play;
  double aWidth1, aHeight1, aWidth2, aHeight2, reWidth, reHeight, xWormHole, yWormHole;
  int healthAmount, fireAmount, countShooting;
  bool checkCollision1, checkCollision2, checkRepair, shooting, checkShooting, checkBulletBuff, checkBulletBuff1;
  int aError, error, countCollision1, countCollision2, countShootingConllision;
  int goal;
  double xFire[27], yFire[27], fireWidth[27], fireHeight[27], fireScale, angle, holeAngle;
  string explosionPath;
  static const double SHIP_VEL = 1.9;
  double xVel, yVel;

  private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  int mouseX, mouseY, shipWidth, shipHeight;
  int ship_1, explosion_1, blue_1, fire_1[27];
  double x, y, xLast, yLast;
  Object bg1, bg2, asteroid1, asteroid2, health[5], repair, bulletCur;
  Object gameover, start, board, kk, wormHole, bulletBuff;
  Object fire[27];
  Entity blue;
  Entity explosion;
  Entity ship, hh;
};

#endif //GAME_H
