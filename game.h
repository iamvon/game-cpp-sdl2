#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "object.h"
#include "entity.h"
#include "audio.h"
// #include "explosion.h"

#define WIDTH 580
#define HEIGHT 960
#define FONT_SIZE 28
#define FONT_SIZE_LARGE 50
#define FPS 50
#define IMG_SIZE_W 512
#define IMG_SIZE_H 512
const double SCALE = 0.35;
#define SHIP_SIZE_W IMG_SIZE_W*SCALE
#define SHIP_SIZE_H IMG_SIZE_H*SCALE
#define SHIP_SPEED 190
#define BACKGROUND_SPEED 400
#define ASTEROID_SIZE 380
#define HEALTH_SIZE  30
#define BULLET_BUFF_SIZE  100
#define WORM_HOLE_SIZE  300 

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
  void drawMsgLarge(const char* msg, int x, int y, int r, int g, int b);
  void resetAsteroid(double x, double y, double &xA, double &yA, double aWidth, double aHeight, int &aScale, double &step, bool &checkPos);
  void resetHole(double &xHole, double &yHole);
  void wormHoleTeleportShip(Object &ship, double &x, double &y, int &width, int &height, double xWormHole, double yWormHole);
  void gravityHoleAffect(double &xA, double &yA, double xGravityHole, double yGravityHole, double width, double height);
  bool collision(double x, double y, double xA, double yA, double aWidth, double aHeight);
  bool buffCollision(double x, double y, double xBuff, double yBuff);
  bool shootingCollision(double xFire, double yFire, double fireWidth, double fireHeight, double xA, double yA, double aWidth, double aHeight);
  bool minimalistAsteroidSize(double aWidth, double aHeight);
  double xBg_1, yBg_1, xBg_2, yBg_2, xBulletBuff, yBulletBuff;
  double xA_1, yA_1, xA_2, yA_2, xA_3, yA_3, xA_4, yA_4, step1, step2, step3, step4, xRe, yRe, xE, yE, offset;
  int kmCounter, aScale1, aScale2, aScale3, aScale4, countSpin;
  bool checkLeft, checkRight, checkPos1, checkPos2, checkPos3, checkPos4, loser, play, checkHole, check;
  double aWidth1, aHeight1, aWidth2, aHeight2, aWidth3, aHeight3, aWidth4, aHeight4, reWidth, reHeight, xWormHole, yWormHole, xGravityHole, yGravityHole;
  int healthAmount, fireAmount, countShooting;
  bool checkCollision1, checkCollision2, checkCollision3, checkCollision4, checkRepair, shooting, checkShooting, checkBulletBuff, checkNewPos, winner;
  int aError, error, countCollision1, countCollision2, countCollision3, countCollision4, countShootingConllision;
  int goal, frameCount, healthLast;
  double xFire[27], yFire[27], fireWidth[27], fireHeight[27], fireScale, angle, holeAngle;
  string explosionPath;
  static const double SHIP_VEL = 2.5;
  double xVel, yVel;
  int counter;
  // bool checkHole;

  private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  TTF_Font *fontLarge;
  bool running;
  int timerFPS, lastFrame;
  int mouseX, mouseY, shipWidth, shipHeight;
  int ship_1, explosion_1, blue_1, fire_1[27];
  double x, y, xLast, yLast;
  Object playButton, exitButton, bg1, bg2, asteroid4, asteroid3, asteroid2, asteroid1, health[5], repair, bulletCur, kk;
  Object gameover, start, board, wormHole, gravityHole, bulletBuff, shipLoser, earth;
  Object fire[27];
  // Explosion test;
  // Entity blue;
  Entity explosion, haha, ship, bk, br;

  Audio powerUp, asteroidExplosion, shipExplosion, readyGo, alarm;
};

#endif //GAME_H
